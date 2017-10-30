/*
 * TimerA.h
 *
 *  Created on: Oct 28, 2017
 *      Author: jonat
 */

#ifndef STEPPERMOTORTIMER_H_
#define STEPPERMOTORTIMER_H_

#include "msp.h"
#include "StepperMotor.h"

class StepperMotorTimer {
public:
    /* Constructors */
    StepperMotorTimer(StepperMotor * MotorX, StepperMotor * MotorY, StepperMotor * MotorZ);

    /* High level functions */
    void startTimer();
    void stopTimer();

    /* Interrupt Service Routines */
    void static TA0_0(void);
    void static TA0_N(void);

private:
    /* Motors */
    static StepperMotor * MotorX;
    static StepperMotor * MotorY;
    static StepperMotor * MotorZ;
};

#endif /* STEPPERMOTORTIMER_H_ */
