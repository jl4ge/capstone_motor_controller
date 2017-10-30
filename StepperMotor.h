/*
 * StepperMotor.h
 *
 *  Created on: Oct 17, 2017
 *      Author: jonat
 */

#ifndef STEPPERMOTOR_H_
#define STEPPERMOTOR_H_

/* Include statements */
#include "msp.h"
#include <stdint.h>

typedef enum {
    A5984, A4988
} MotorDriver;

#define MOTOR_DRIVER A4988

#if MOTOR_DRIVER == A5984

typedef enum {
    FullStep, HalfStep, QuarterStep, EighthStep, SixteenthStep, ThirtysecondStep
} SteppingModes;

#elif MOTOR_DRIVER == A4988

typedef enum {
    FullStep, HalfStep, QuarterStep, EighthStep, SixteenthStep
} SteppingModes;

#endif

typedef enum {
    Stopped, Resetting, MovingForward, MovingBackward
} StepperMotorStates;

class StepperMotor {
public:
    /* Constructors */
    StepperMotor();
    StepperMotor(uint8_t * enableDir,
                 uint8_t * dirDir,
                 uint8_t * stepDir,
                 uint8_t * resetDir,
                 uint8_t * faultDir,
                 uint8_t * sleepDir,
                 uint8_t * ms1Dir,
                 uint8_t * ms2Dir,
                 uint8_t * ms3Dir,

                 uint8_t * enableOut,
                 uint8_t * dirOut,
                 uint8_t * stepOut,
                 uint8_t * resetOut,
                 uint8_t * faultOut,
                 uint8_t * sleepOut,
                 uint8_t * ms1Out,
                 uint8_t * ms2Out,
                 uint8_t * ms3Out,

                 uint8_t enablePin,
                 uint8_t dirPin,
                 uint8_t stepPin,
                 uint8_t resetPin,
                 uint8_t faultPin,
                 uint8_t sleepPin,
                 uint8_t ms1Pin,
                 uint8_t ms2Pin,
                 uint8_t ms3Pin,

                 uint8_t * faultIn,
                 uint8_t * faultRen);

    /* High level functions */
    void sleep();
    void wakeUp();
    void enable();
    void dissable();
    void setStepMode(SteppingModes mode);
    bool getFaultState();
    bool isMoving();
    StepperMotorStates getState();

    /* Methods for moving the motor. */
    void resetLimits();
    void goTo(int32_t coordinate);
    void go(int32_t);

    /* Methods for changing the motor driver pins */
    void resetEnable();
    void resetDisable();
    void stepEnable();
    void stepDisable();
    void stepToggle();
    void dirSet();
    void dirReset();
    void dirToggle();

    /* Function for when the limit has been hit. */
    void hitLimit();

    /* Timer Interrupt tick function */
    void tick();

private:
    /* Port attributes */
    uint8_t * enableOut;
    uint8_t * dirOut;
    uint8_t * stepOut;
    uint8_t * resetOut;
    uint8_t * sleepOut;
    uint8_t * ms1Out;
    uint8_t * ms2Out;
    uint8_t * ms3Out;

    uint8_t * faultIn;

    /* Port pin attributes */
    uint8_t enablePin;
    uint8_t dirPin;
    uint8_t stepPin;
    uint8_t resetPin;
    uint8_t faultPin;
    uint8_t sleepPin;
    uint8_t ms1Pin;
    uint8_t ms2Pin;
    uint8_t ms3Pin;

    /* Motor motion attributes */
    int32_t position;
    int32_t destination;
    int32_t max;
    StepperMotorStates state;
};

#endif /* STEPPERMOTOR_H_ */
