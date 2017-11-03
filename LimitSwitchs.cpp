/*
 * LimitSwitch.cpp
 *
 *  Created on: Nov 2, 2017
 *      Author: jonat
 */

#include "LimitSwitchs.h"

/* Sets default values for the static variables */
uint8_t LimitSwitchs::xPin = 0;
uint8_t LimitSwitchs::yPin = 0;
uint8_t * LimitSwitchs::xIn = 0;
uint8_t * LimitSwitchs::yIn = 0;
uint8_t * LimitSwitchs::xIFG = 0;
uint8_t * LimitSwitchs::yIFG = 0;
StepperMotor * LimitSwitchs::MotorX = 0;
StepperMotor * LimitSwitchs::MotorY = 0;

LimitSwitchs::LimitSwitchs(uint8_t xPin,
                           uint8_t yPin,
                           uint8_t * xDir,
                           uint8_t * yDir,
                           uint8_t * xIn,
                           uint8_t * yIn,
                           uint8_t * xIE,
                           uint8_t * yIE,
                           uint8_t * xIFG,
                           uint8_t * yIFG,
                           StepperMotor * MotorX,
                           StepperMotor * MotorY) {

    /* Sets internal variables */
    this->xPin = xPin;
    this->yPin = yPin;
    this->xIn = xIn;
    this->yIn = yIn;
    this->xIFG = xIFG;
    this->yIFG = yIFG;
    this->MotorX = MotorX;
    this->MotorY = MotorY;

    /* Enables interrupts on port 4 */
    NVIC->ISER[1] = 1 << ((PORT4_IRQn) & 31);

    /* Enables interrupts on the xPin and sets it as an input */
    P4IES |= xPin; // | yPin
    *xDir &= ~xPin;
//    *yDir &= ~yPin;
    *xIE |= xPin;
//    *yIE |= yPin;
    *xIFG &= ~xPin;
//    *yIFG &= ~yPin;
}

void LimitSwitchs::limitHit() {
    *xIFG &= ~xPin;
//    *yIFG &= ~yPin;

    if (~*xIn & xPin) {
        MotorX->hitLimit();
    }

//    if (~*yIn & yPin) {
//        MotorY->hitLimit();
//    }
}
