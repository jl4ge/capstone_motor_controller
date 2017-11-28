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
uint8_t LimitSwitchs::zPin = 0;
uint8_t * LimitSwitchs::xIn = 0;
uint8_t * LimitSwitchs::yIn = 0;
uint8_t * LimitSwitchs::zIn = 0;
uint8_t * LimitSwitchs::xIFG = 0;
uint8_t * LimitSwitchs::yIFG = 0;
uint8_t * LimitSwitchs::zIFG = 0;
StepperMotor * LimitSwitchs::MotorX = 0;
StepperMotor * LimitSwitchs::MotorY = 0;
StepperMotor * LimitSwitchs::MotorZ = 0;

LimitSwitchs::LimitSwitchs(uint8_t xPin,
                           uint8_t yPin,
                           uint8_t zPin,
                           uint8_t * xDir,
                           uint8_t * yDir,
                           uint8_t * zDir,
                           uint8_t * xIn,
                           uint8_t * yIn,
                           uint8_t * zIn,
                           uint8_t * xIE,
                           uint8_t * yIE,
                           uint8_t * zIE,
                           uint8_t * xIFG,
                           uint8_t * yIFG,
                           uint8_t * zIFG,
                           StepperMotor * MotorX,
                           StepperMotor * MotorY,
                           StepperMotor * MotorZ) {

    /* Sets internal variables */
    this->xPin = xPin;
    this->yPin = yPin;
    this->zPin = zPin;
    this->xIn = xIn;
    this->yIn = yIn;
    this->zIn = zIn;
    this->xIFG = xIFG;
    this->yIFG = yIFG;
    this->zIFG = zIFG;
    this->MotorX = MotorX;
    this->MotorY = MotorY;
    this->MotorZ = MotorZ;

    /* Enables interrupts on port 4 */
    NVIC->ISER[1] = 1 << ((PORT5_IRQn) & 31);

    /* Enables interrupts on the xPin and sets it as an input */
    P5IES |= xPin | yPin | zPin;
    *xDir &= ~xPin;
    *yDir &= ~yPin;
    *zDir &= ~zPin;
    *xIE |= xPin;
    *yIE |= yPin;
    *zIE |= zPin;
    *xIFG &= ~xPin;
    *yIFG &= ~yPin;
    *zIFG &= ~zPin;
}

void LimitSwitchs::limitHit() {
    *xIFG &= ~xPin;
    *yIFG &= ~yPin;
    *zIFG &= ~zPin;

    if (~*xIn & xPin) {
        MotorX->hitLimit();
    }

    if (~*yIn & yPin) {
        MotorY->hitLimit();
    }

    if (~*zIn & zPin) {
        MotorZ->hitLimit();
    }
}
