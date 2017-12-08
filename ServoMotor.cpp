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

void ServoMotor::spin(bool dir, int32_t length) {
    if (dir) {
        *motorOut |= motorPin;
        motorState = MovingClockwise;
        TA1CCR0 = 8000;
//        TA1CCR1 = 2250;
    } else {
        *motorOut |= motorPin;
        motorState = MovingCounterClockwise;
        TA1CCR0 = 1000;
//        TA1CCR1 = 1050;
    }

    this->length = length;
    turns = 0;
}

void ServoMotor::stop() {
    motorState = Motionless;
}

bool ServoMotor::isMoving() {
    return motorState != Motionless;
}

void ServoMotor::tickOn() {
    switch(motorState) {
    case Motionless:
        break;
    default:
        turns += 1;
        if (turns >= length) {
            stop();
        }
        *motorOut ^= motorPin;
        break;
    }
}

void ServoMotor::tickOff() {
    switch(motorState) {
    case Motionless:
        break;
    default:
        turns += 1;
        if (turns >= length) {
            stop();
        }
        *motorOut &= ~motorPin;
        break;
    }
}
