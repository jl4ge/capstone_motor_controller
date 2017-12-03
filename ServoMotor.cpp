/*
 * ServoMotor.cpp
 *
 *  Created on: Nov 19, 2017
 *      Author: jonat
 */

#include "ServoMotor.h"

ServoMotor::ServoMotor(uint8_t * motorDir, uint8_t * motorOut, uint8_t motorPin) {
    /* Stores motor information in memory */
    this->motorOut = motorOut;
    this->motorPin = motorPin;

    /* Sets the direction of the motor to be out */
    *motorDir |= motorPin;
    *motorOut &= ~motorPin;

    motorState = Motionless;
}

void ServoMotor::spin(bool dir) {
    if (dir) {
        *motorOut |= motorPin;
        motorState = MovingClockwise;
    } else {
        *motorOut &= ~motorPin;
        motorState = MovingCounterClockwise;
    }
}

void ServoMotor::stop() {
    motorState = Motionless;
}

bool ServoMotor::isMoving() {
    return motorState != Motionless;
}

void ServoMotor::tick() {
    switch(motorState) {
    case Motionless:
        break;
    default:
        *motorOut ^= motorPin;
        break;
    }
}
