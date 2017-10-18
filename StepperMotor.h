/*
 * StepperMotor.h
 *
 *  Created on: Oct 17, 2017
 *      Author: jonat
 */

#ifndef STEPPERMOTOR_H_
#define STEPPERMOTOR_H_

#include "msp.h"
#include <stdint.h>

typedef enum {
    FullStep, HalfStep, QuarterStep, EighthStep, SixteenthStep, ThirtysecondStep
} SteppingModes;

class StepperMotor {
public:
    /* Constructor */
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

    /* Methods for changing the motor driver pins */
    void sleep();
    void wakeUp();
    void enable();
    void dissable();
    void setStepMode(SteppingModes mode);
    bool getFaultState();
    void reset();
    void stepToggle();

    void resetEnable();
    void resetDisable();
    void stepEnable();
    void stepDisable();
    void dirSet();
    void dirReset();


private:
    /* Port declarations */
    uint8_t * enableOut;
    uint8_t * dirOut;
    uint8_t * stepOut;
    uint8_t * resetOut;
    uint8_t * sleepOut;
    uint8_t * ms1Out;
    uint8_t * ms2Out;
    uint8_t * ms3Out;

    uint8_t * faultIn;

    /* Port pin declarations */
    uint8_t enablePin;
    uint8_t dirPin;
    uint8_t stepPin;
    uint8_t resetPin;
    uint8_t faultPin;
    uint8_t sleepPin;
    uint8_t ms1Pin;
    uint8_t ms2Pin;
    uint8_t ms3Pin;
};

#endif /* STEPPERMOTOR_H_ */
