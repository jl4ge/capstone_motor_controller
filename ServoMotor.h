/*
 * ServoMotor.h
 *
 *  Created on: Nov 19, 2017
 *      Author: jonat
 */

#ifndef SERVOMOTOR_H_
#define SERVOMOTOR_H_

#include "msp.h"
#include <stdint.h>

typedef enum {
    Motionless, MovingClockwise, MovingCounterClockwise
} ServoMotorState;

class ServoMotor {
public:
    ServoMotor(uint8_t * motorDir, uint8_t * motorOut, uint8_t motorPin);

    void spin(bool dir, int32_t length);
    void stop();
    void tickOn();
    void tickOff();
    bool isMoving();
private:
    uint8_t * motorOut;
    uint8_t motorPin;
    ServoMotorState motorState;
    int32_t length;
    int32_t turns;
};

#endif /* SERVOMOTOR_H_ */
