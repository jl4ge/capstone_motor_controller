/*
 * Electromagnet.cpp
 *
 *  Created on: Oct 28, 2017
 *      Author: jonat
 */

/* Include statements */
#include "Electromagnet.h"

/* Initializes the electromagnet. */
Electromagnet::Electromagnet(uint8_t * ctlDir, uint8_t * ctlOut, uint8_t ctlPin) {
    /* Loads the information to the pins */
    this->ctlDir = ctlDir;
    this->ctlOut = ctlOut;
    this->ctlPin = ctlPin;

    /* Sets the control pin to be an output */
    *ctlDir = *ctlDir | ctlPin;

    /* Sets the pin to be on and the electromagnet to off. */
    *ctlOut = *ctlOut | ctlPin;
}

/* Turns on the electromagnet */
void Electromagnet::TurnOn() {
    *ctlOut = *ctlOut & ~ctlPin;
}

/* Turns off the electromagnet */
void Electromagnet::TurnOff() {
    *ctlOut = *ctlOut | ctlPin;
}
