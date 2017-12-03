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

    void spin(bool dir);
    void stop();
    void tick();
    bool isMoving();
private:
    uint8_t * motorOut;
    uint8_t motorPin;
    ServoMotorState motorState;
};

#endif /* SERVOMOTOR_H_ */
