/*
 * LimitSwitch.h
 *
 *  Created on: Nov 2, 2017
 *      Author: jonat
 */

#ifndef LIMITSWITCHS_H_
#define LIMITSWITCHS_H_

#include "msp.h"
#include <stdint.h>
#include "StepperMotor.h"

class LimitSwitchs {
public:
    LimitSwitchs(uint8_t xPin,
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
                 StepperMotor * MotorY);

    void static limitHit();

private:
    static uint8_t xPin;
    static uint8_t yPin;
    static uint8_t * xIn;
    static uint8_t * yIn;
    static uint8_t * xIFG;
    static uint8_t * yIFG;
    static StepperMotor * MotorX;
    static StepperMotor * MotorY;
};



#endif /* LIMITSWITCHS_H_ */
