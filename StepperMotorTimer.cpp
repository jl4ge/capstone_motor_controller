/*
 * TimerA.cpp
 *
 *  Created on: Oct 28, 2017
 *      Author: jonat
 */

/* Include statements */
#include "StepperMotorTimer.h"

/* Sets the initial motor pointers to null. */
StepperMotor * StepperMotorTimer::MotorX = 0;
StepperMotor * StepperMotorTimer::MotorY = 0;
StepperMotor * StepperMotorTimer::MotorZ = 0;

/* Initializes the timer with provided motors and starts the timer. */
StepperMotorTimer::StepperMotorTimer(StepperMotor * MotorX, StepperMotor * MotorY, StepperMotor * MotorZ) {
    /* Sets the internal motors to the ones provided and enforces that only one instance exists. */
    if (this->MotorX == 0) {
        this->MotorX = MotorX;
    }
    if (this->MotorY == 0) {
        this->MotorY = MotorY;
    }
    if (this->MotorZ == 0) {
        this->MotorZ = MotorZ;
    }

    /* Enables the timer interrupts */
    NVIC->ISER[0] = 1 << ((TA0_0_IRQn) & 31);
    NVIC->ISER[0] = 1 << ((TA0_N_IRQn) & 31);

    /*
     * Sets TimerA0 to run at with the following settings
     * TASSEL_2 : SMCLK = 24MHz
     * ID_3     : Input divider = 8
     * MC_1     : Up mode - The timer counts up to TA0CCR0
     *
     * So the timer will count up one every 1/3 us.
     */
    TA0CTL = TASSEL_2 | ID_3 | MC_1 | TACLR;

    /* Enables the interrupts on the TACCR0 register */
    TA0CCTL0 |= CCIE;

    /* Sets the timer interrupt to trigger every 1ms. */
    TA0CCR0 = 3000;
}

/* Starts the timer. */
void StepperMotorTimer::startTimer() {
    /* TODO -- Start the timer. */
}

/* Stops the timer. */
void StepperMotorTimer::stopTimer() {
    /* TODO -- Stop the timer. */
}

/* TA0_0 ISR */
void StepperMotorTimer::TA0_0(void) {
    /* Clears the capture control register interrupt flag. */
    TA0CCTL0 &= ~CCIFG;

    /* Steps the motors if they are moving. */
    MotorX->tick();
//    MotorY->tick();
//    MotorZ->tick();
}

/* TA0_N ISR */
void StepperMotorTimer::TA0_N(void) {
    /* TODO -- Maybe add stuff later. */
}

