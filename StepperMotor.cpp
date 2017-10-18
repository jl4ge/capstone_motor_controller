/*
 * StepperMotor.cpp
 *
 *  Created on: Oct 17, 2017
 *      Author: jonat
 */

#include <StepperMotor.h>

/* Initializes the Stepper motor based given the pins and ports. */
StepperMotor::StepperMotor(uint8_t * enableDir,
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
                           uint8_t * faultRen) {

    /* Sets up the ports */
    this->enableOut = enableOut;
    this->dirOut = dirOut;
    this->stepOut = stepOut;
    this->resetOut = resetOut;
    this->sleepOut = sleepOut;
    this->ms1Out = ms1Out;
    this->ms2Out = ms2Out;
    this->ms3Out = ms3Out;

    this->faultIn = faultIn;

    /* Sets up the pins */
    this->enablePin = enablePin;
    this->dirPin = dirPin;
    this->stepPin = stepPin;
    this->resetPin = resetPin;
    this->faultPin = faultPin;
    this->sleepPin = sleepPin;
    this->ms1Pin = ms1Pin;
    this->ms2Pin = ms2Pin;
    this->ms3Pin = ms3Pin;

    /* Sets the direction of each port pin as an output. */
    *enableDir = *enableDir | this->enablePin;
    *dirDir = *dirDir | this->dirPin;
    *stepDir = *stepDir | this->stepPin;
    *resetDir = *resetDir | this->resetPin;
    *sleepDir = *sleepDir | this->sleepPin;
    *ms1Dir = *ms1Dir | this->ms1Pin;
    *ms2Dir = *ms2Dir | this->ms2Pin;
    *ms3Dir = *ms3Dir | this->ms3Pin;

    /* Sets the fault pin as an input with no pull up resistors. */
    *faultDir = *faultDir & ~this->faultPin;
    *faultOut = *faultOut & ~this->faultPin;
    *faultRen = *faultRen & ~this->faultPin;

    /* Gives the motors initial conditions. */
    wakeUp();
    dissable();
    resetDisable();
    setStepMode(QuarterStep);

}

/* Wakes the motor driver up from sleep. */
void StepperMotor::wakeUp() {
    *sleepOut = *sleepOut | sleepPin;
}

/* Puts the motor driver to sleep. */
void StepperMotor::sleep() {
    *sleepOut = *sleepOut & ~sleepPin;
}

/* Enables the motor driver. */
void StepperMotor::enable() {
    *enableOut = *enableOut | enablePin;
}

/* Disables the motor driver. */
void StepperMotor::dissable() {
    *enableOut = *enableOut & ~enablePin;
}

/* Enables the reset pin on the motor driver. */
void StepperMotor::resetEnable() {
    *resetOut = *resetOut & ~resetPin;
}

/* Disables the reset pin on the motor driver. */
void StepperMotor::resetDisable() {
    *resetOut = *resetOut | resetPin;
}

/* Changes the motor driver stepping mode. */
void StepperMotor::setStepMode(SteppingModes mode) {
    /* Sets the MS1 pins to correspond to stepping mode. */
    switch (mode) {
        case FullStep:
            *ms1Out = *ms1Out & ~ms1Pin;
            *ms2Out = *ms2Out & ~ms2Pin;
            *ms3Out = *ms3Out & ~ms3Pin;
            break;
        case HalfStep:
            *ms1Out = *ms1Out | ms1Pin;
            *ms2Out = *ms2Out & ~ms2Pin;
            *ms3Out = *ms3Out & ~ms3Pin;
            break;
        case QuarterStep:
            *ms1Out = *ms1Out & ~ms1Pin;
            *ms2Out = *ms2Out | ms2Pin;
            *ms3Out = *ms3Out | ms3Pin;
            break;
        case EighthStep:
            *ms1Out = *ms1Out | ms1Pin;
            *ms2Out = *ms2Out | ms2Pin;
            *ms3Out = *ms3Out | ms3Pin;
            break;
        case SixteenthStep:
            *ms1Out = *ms1Out & ~ms1Pin;
            *ms2Out = *ms2Out | ms2Pin;
            *ms3Out = *ms3Out & ~ms3Pin;
            break;
        case ThirtysecondStep:
            *ms1Out = *ms1Out | ms1Pin;
            *ms2Out = *ms2Out | ms2Pin;
            *ms3Out = *ms3Out & ~ms3Pin;
            break;
        default:
            /* Defaults to quarter step */
            *ms1Out = *ms1Out & ~ms1Pin;
            *ms2Out = *ms2Out | ms2Pin;
            *ms3Out = *ms3Out | ms3Pin;
            break;
    }
}

/* Gets the fault state */
bool StepperMotor::getFaultState() {
    return *faultIn & faultPin;
}

/* Enables the step pin */
void StepperMotor::stepEnable() {
    *stepOut = *stepOut | stepPin;
}

/* Disables the step pin */
void StepperMotor::stepDisable() {
    *stepOut = *stepOut & ~stepPin;
}

/* Enables the dir pin */
void StepperMotor::dirSet() {
    *dirOut = *dirOut | dirPin;
}

/* Disables the dir pin */
void StepperMotor::dirReset() {
    *dirOut = *dirOut & ~dirPin;
}
