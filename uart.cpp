/*
 * uart.cpp
 *
 *  Created on: Nov 3, 2017
 *      Author: jonat
 */

#include "uart.h"


bool isReady;
recieveParsingFSM parsingFSMState;
command currentCommand;
command nextCommand;
uint8_t paramsRemaining;
uint8_t paramI;
TileMover * mover;

void configureUART(TileMover * m) {
    // Configure UART pins
    P3->SEL0 |= BIT2 | BIT3;                // set 2-UART pin as secondary function

//    P1DIR |= BIT0;
//    P1OUT &= ~BIT0;

    // Configure UART
    EUSCI_A2->CTLW0 |= EUSCI_A_CTLW0_SWRST; // Put eUSCI in reset
    EUSCI_A2->CTLW0 = EUSCI_A_CTLW0_SWRST | // Remain eUSCI in reset
            EUSCI_B_CTLW0_SSEL__SMCLK;      // Configure eUSCI clock source for SMCLK
    // Baud Rate calculation
    // 24000000/(16*9600) = 156.25
    // Fractional portion = 0.25
    // User's Guide Table 21-4: UCBRSx = 0x44
    // UCBRFx = int ( (156.25-156)*16) = 4
    EUSCI_A2->BRW = 156;                     // 24000000/16/9600
    EUSCI_A2->MCTLW = (0x44 << EUSCI_A_MCTLW_BRS_OFS) | // UCBRSx = 0x44
            (4 << EUSCI_A_MCTLW_BRF_OFS) | // UCBRFx = 4
            EUSCI_A_MCTLW_OS16;

    EUSCI_A2->CTLW0 &= ~EUSCI_A_CTLW0_SWRST; // Initialize eUSCI
    EUSCI_A2->IFG &= ~EUSCI_A_IFG_RXIFG;    // Clear eUSCI RX interrupt flag
    EUSCI_A2->IE |= EUSCI_A_IE_RXIE;        // Enable USCI_A0 RX interrupt

    // Enable eUSCIA0 interrupt in NVIC module
    NVIC->ISER[0] = 1 << ((EUSCIA2_IRQn) & 31);

    /* Parsing received command fsm variables */
    isReady = false;
    parsingFSMState = NewCommand;
    mover = m;
}

bool commandReady() {
    return isReady;
}

command getNextCommand() {
    isReady = false;
    return currentCommand;
}

void EUSCIA2_IRQHandler(void) {
    if (EUSCI_A2->IFG & EUSCI_A_IFG_RXIFG) {
        // Check if the TX buffer is empty first
        while(!(EUSCI_A2->IFG & EUSCI_A_IFG_TXIFG));

        switch (parsingFSMState) {
        case NewCommand:
            paramI = 0;
            switch (EUSCI_A2->RXBUF) {
            case 0:
                currentCommand.command = doNothing;
                isReady = true;
                break;
            case 1:
                nextCommand.command = getNewTiles;
                parsingFSMState = GettingNumParameters;
                break;
            case 2:
                nextCommand.command = makeTileMoves;
                parsingFSMState = GettingNumParameters;
                break;
            case 3:
                nextCommand.command = getNewTile;
                parsingFSMState = ReadingParameters;
                paramsRemaining = 3;
                break;
            case 4:
                nextCommand.command = makeTileMove;
                parsingFSMState = ReadingParameters;
                paramsRemaining = 4;
                break;
            case 5:
                nextCommand.command = pickupNewTile;
                parsingFSMState = ReadingParameters;
                paramsRemaining = 2;
                break;
            case 6:
                nextCommand.command = pickupHandTile;
                parsingFSMState = ReadingParameters;
                paramsRemaining = 1;
                break;
            case 7:
                nextCommand.command = pickupBoard;
                parsingFSMState = ReadingParameters;
                paramsRemaining = 2;
                break;
            case 8:
                currentCommand.command = pickupRotator;
                isReady = true;
                break;
            case 9:
                currentCommand.command = pickupFlipper;
                isReady = true;
                break;
            case 10:
                nextCommand.command = dropOffNewTile;
                parsingFSMState = ReadingParameters;
                paramsRemaining = 2;
                break;
            case 11:
                nextCommand.command = dropOffHand;
                parsingFSMState = ReadingParameters;
                paramsRemaining = 1;
                break;
            case 12:
                nextCommand.command = dropOffBoard;
                parsingFSMState = ReadingParameters;
                paramsRemaining = 2;
                break;
            case 13:
                currentCommand.command = dropOffRotator;
                isReady = true;
                break;
            case 14:
                currentCommand.command = dropOffFlipper;
                isReady = true;
                break;
            case 15:
                currentCommand.command = rotateTile;
                isReady = true;
                break;
            case 16:
                currentCommand.command = flipTile;
                isReady = true;
                break;
            case 17:
                nextCommand.command = goZPos;
                parsingFSMState = ReadingParameters;
                paramsRemaining = 1;
                break;
            case 18:
                currentCommand.command = turnOnMagnet;
                isReady = true;
                break;
            case 19:
                currentCommand.command = turnOffMagnet;
                isReady = true;
                break;
            case 20:
                currentCommand.command = isBusy;
                EUSCI_A2->TXBUF = (mover->IsBusy()) ? 1 : 0;
                isReady = false;
                break;
            default:
                break;
            }
            break;
        case ReadingParameters:
            nextCommand.parameters[paramI] = EUSCI_A2->RXBUF;
            paramI++;
            paramsRemaining--;
            if (paramsRemaining == 0) {
                parsingFSMState = NewCommand;
                currentCommand = nextCommand;
                isReady = true;
            }
            break;
        case GettingNumParameters:
            nextCommand.parameters[0] = EUSCI_A2->RXBUF;
            parsingFSMState = ReadingParameters;
            paramI = 1;
            if (nextCommand.command == getNewTiles) {
                paramsRemaining = nextCommand.parameters[0] * 3;
            } else {
                paramsRemaining = nextCommand.parameters[0] * 4;
            }
            break;
        default:
            parsingFSMState = NewCommand;
            break;
        }

//        P1OUT |= BIT0;
//
//        // Echo the received character back
//        EUSCI_A2->TXBUF = EUSCI_A2->RXBUF;
    }
}
