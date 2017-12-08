/*
 * ServoMotorTimer.cpp
 *
 *  Created on: Nov 19, 2017
 *      Author: jonat
 */


/* Include statements */
#include "ServoMotorTimer.h"

/* Sets the initial motor pointers to null. */
ServoMotor * ServoMotorTimer::Flipper = 0;
//ServoMotor * ServoMotorTimer::Rotator = 0;

/* Initializes the timer with provided motors and starts the timer. */
ServoMotorTimer::ServoMotorTimer(ServoMotor * Flipper) {
    /* Sets the internal motors to the ones provided and enforces that only one instance exists. */
    if (this->Flipper == 0) {
        this->Flipper = Flipper;
    }
//    if (this->Rotator == 0) {
//        this->Rotator = Rotator;
//    }

    /* Enables the timer interrupts */
    NVIC->ISER[0] = 1 << ((TA1_0_IRQn) & 31);
    NVIC->ISER[0] = 1 << ((TA1_N_IRQn) & 31);

    /*
     * Sets TimerA0 to run at with the following settings
     * TASSEL_2 : SMCLK = 24MHz
     * ID_3     : Input divider = 8
     * MC_1     : Up mode - The timer counts up to TA0CCR0
     *
     * So the timer will count up one every 1/3 us.
     */
    TA1CTL = TASSEL_2 | ID_3 | MC_1 | TACLR;

    /* Enables the interrupts on the TACCR0 register */
    TA1CCTL0 |= CCIE;
//    TA1CCTL1 |= CCIE;

    /* Sets the timer interrupt to trigger every 2000us. */
    TA1CCR0 = 4500;
//    TA1CCR1 = 2250;
}

/* Starts the timer. */
void ServoMotorTimer::startTimer() {
    /* TODO -- Start the timer. */
}

/* Stops the timer. */
void ServoMotorTimer::stopTimer() {
    /* TODO -- Stop the timer. */
}

/* TA1_0 ISR */
void ServoMotorTimer::TA1_0(void) {
    /* Clears the capture control register interrupt flag. */
    TA1CCTL0 &= ~CCIFG;

    /* Steps the motors if they are moving. */
    Flipper->tickOn();
}

/* TA0_N ISR */
void ServoMotorTimer::TA1_N(void) {
//    /* Clears the capture control register interrupt flag. */
//    TA1CCTL1 &= ~CCIFG;
//
//    /* Steps the motors if they are moving. */
//    Flipper->tickOff();
}


