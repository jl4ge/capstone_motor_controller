/*
 * StepperMotor.cpp
 *
 *  Created on: Oct 17, 2017
 *      Author: jonat
 */

/* Include statements */
#include <StepperMotor.h>

StepperMotor::StepperMotor() {
    /* Loads the ports to be zero by default */
    enableOut = 0;
    dirOut = 0;
    stepOut = 0;
    resetOut = 0;
    sleepOut = 0;
    ms1Out = 0;
    ms2Out = 0;
    ms3Out = 0;
    faultIn = 0;
    enablePin = 0;
    dirPin = 0;
    stepPin = 0;
    resetPin = 0;
    faultPin = 0;
    sleepPin = 0;
    ms1Pin = 0;
    ms2Pin = 0;
    ms3Pin = 0;
}

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

    /* Loads the ports */
    this->enableOut = enableOut;
    this->dirOut = dirOut;
    this->stepOut = stepOut;
    this->resetOut = resetOut;
    this->sleepOut = sleepOut;
    this->ms1Out = ms1Out;
    this->ms2Out = ms2Out;
    this->ms3Out = ms3Out;

    this->faultIn = faultIn;

    /* Loads the pins */
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
    enable();
    resetDisable();
    setStepMode(EighthStep);
    time = 0;


    /* Resets the location to be zeroed. */
    // TODO -- Fix later
    resetLimits();
//    while(isMoving());

//    setStepMode(HalfStep);

    /* TODO -- Remove after reset with limits is added. */
//    position = 0;
//    state = Stopped;
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
    /* Pin is active low */
    *enableOut = *enableOut & ~enablePin;
}

/* Disables the motor driver. */
void StepperMotor::dissable() {
    /* Pin is active low */
    *enableOut = *enableOut | enablePin;
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
    #if MOTOR_DRIVER == A5984

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

    #elif MOTOR_DRIVER == A4988

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
            *ms3Out = *ms3Out & ~ms3Pin;
            break;
        case EighthStep:
            *ms1Out = *ms1Out | ms1Pin;
            *ms2Out = *ms2Out | ms2Pin;
            *ms3Out = *ms3Out & ~ms3Pin;
            break;
        case SixteenthStep:
            *ms1Out = *ms1Out | ms1Pin;
            *ms2Out = *ms2Out | ms2Pin;
            *ms3Out = *ms3Out | ms3Pin;
            break;
        default:
            /* Defaults to quarter step */
            *ms1Out = *ms1Out & ~ms1Pin;
            *ms2Out = *ms2Out | ms2Pin;
            *ms3Out = *ms3Out & ~ms3Pin;
            break;
    }

    #endif
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

/* Toggles the dir pin */
void StepperMotor::dirToggle() {
    *dirOut = *dirOut ^ dirPin;
}

/* Gets the motor to go to its limits. */
void StepperMotor::resetLimits() {
    setStepMode(EighthStep);
    state = Resetting;
}

/* This function is called when the limit switch has been hit. */
void StepperMotor::hitLimit() {
    state = Stopped;
    position = 0;
    setStepMode(HalfStep);
    resetEnable();
    resetDisable();
}

/* Goes to a location. */
void StepperMotor::goTo(int32_t coordinate) {
    /* TODO -- Add checking to make sure the motor does not exceed limits. */
    start = position;
    if (coordinate < position) {
        destination = coordinate;
        state = MovingBackward;
    } else {
        destination = coordinate;
        state = MovingForward;
    }
}

/* Goes a relative distance from the current location. */
void StepperMotor::go(int32_t increment) {
    /* TODO -- Add checking to make sure the motor does not exceed limits. */
    start = position;
    if (increment < 0) {
        destination = destination + increment;
        state = MovingBackward;
    } else {
        destination = destination + increment;
        state = MovingForward;
    }
}

/* Timer Interrupt function */
void StepperMotor::tick() {
    switch (state) {
    case Stopped:
        /* Do nothing if it is stopped. */
        break;
    case Resetting:
        /* Moves backward until the limit switch is triggered. */
        time++;
        if (time >= 10) {
            time = 0;
            dirReset();
            stepEnable();
            stepDisable();
        }
        break;
    case MovingForward:
        /* Move forward until the you reach the destination. */
        if (position == destination) {
            state = Stopped;
        } else {
            /* Determines the distance from the destination and start. */
            uint32_t endDest = destination - position;
            uint32_t startDest = position - start;

            /* Runs the motor with acceleration so it does not jerk around. */
            if (endDest < STEP_ACCEL_DIST && startDest >= STEP_ACCEL_DIST) {
                time++;
                if (time >= (STEP_ACCEL_SPEED - endDest/MAX_STEP_SPEED)) {
                    time = 0;
                    dirSet();
                    stepEnable();
                    stepDisable();
                    position += 1;
                }

            } else if (endDest >= STEP_ACCEL_DIST && startDest < STEP_ACCEL_DIST) {
                time++;
                if (time >= (STEP_ACCEL_SPEED - startDest/MAX_STEP_SPEED)) {
                    time = 0;
                    dirSet();
                    stepEnable();
                    stepDisable();
                    position += 1;
                }
            } else if (endDest <= STEP_ACCEL_DIST && startDest < STEP_ACCEL_DIST) {
                uint32_t smallest = (endDest < startDest) ? endDest : startDest;
                time++;
                if (time >= (STEP_ACCEL_SPEED - smallest/MAX_STEP_SPEED)) {
                    time = 0;
                    dirSet();
                    stepEnable();
                    stepDisable();
                    position += 1;
                }
            } else {
                time++;
                if (time >= MAX_STEP_SPEED) {
                    time = 0;
                    dirSet();
                    stepEnable();
                    stepDisable();
                    position += 1;
                }
            }
        }
        break;
    case MovingBackward:
        /* Move backward until the you reach the destination. */
        if (position == destination) {
            state = Stopped;
        } else {
            /* Determines the distance from the destination and start. */
            uint32_t endDest = position - destination;
            uint32_t startDest = start - position;

            /* Runs the motor with acceleration so it does not jerk around. */
            if (endDest < STEP_ACCEL_DIST && startDest >= STEP_ACCEL_DIST) {
                time++;
                if (time >= (STEP_ACCEL_SPEED - endDest/MAX_STEP_SPEED)) {
                    time = 0;
                    dirReset();
                    stepEnable();
                    stepDisable();
                    position -= 1;
                }

            } else if (endDest >= STEP_ACCEL_DIST && startDest < STEP_ACCEL_DIST) {
                time++;
                if (time >= (STEP_ACCEL_SPEED - startDest/MAX_STEP_SPEED)) {
                    time = 0;
                    dirReset();
                    stepEnable();
                    stepDisable();
                    position -= 1;
                }
            } else if (endDest <= STEP_ACCEL_DIST && startDest < STEP_ACCEL_DIST) {
                uint32_t smallest = (endDest < startDest) ? endDest : startDest;
                time++;
                if (time >= (STEP_ACCEL_SPEED - smallest/MAX_STEP_SPEED)) {
                    time = 0;
                    dirReset();
                    stepEnable();
                    stepDisable();
                    position -= 1;
                }
            } else {
                time++;
                if (time >= MAX_STEP_SPEED) {
                    time = 0;
                    dirReset();
                    stepEnable();
                    stepDisable();
                    position -= 1;
                }
            }
        }
        break;
    default:
        state = Stopped;
        break;
    }
}

/* Returns the motor state. */
StepperMotorStates StepperMotor::getState() {
    return state;
}

/* Returns whether or not the motor is moving. */
bool StepperMotor::isMoving() {
    return state != Stopped;
}
