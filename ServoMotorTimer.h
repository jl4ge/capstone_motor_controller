/*
 * ServoMotorTimer.h
 *
 *  Created on: Nov 19, 2017
 *      Author: jonat
 */

#ifndef SERVOMOTORTIMER_H_
#define SERVOMOTORTIMER_H_

#include "msp.h"
#include "ServoMotor.h"

class ServoMotorTimer {
public:
    /* Constructors */
    ServoMotorTimer(ServoMotor * Flipper);

    /* High level functions */
    void startTimer();
    void stopTimer();

    /* Interrupt Service Routines */
    void static TA1_0(void);
    void static TA1_N(void);

private:
    /* Motors */
    static ServoMotor * Flipper;
//    static ServoMotor * Rotator;
};

#endif /* SERVOMOTORTIMER_H_ */
