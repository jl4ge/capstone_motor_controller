/*
 * Electromagnet.h
 *
 *  Created on: Oct 28, 2017
 *      Author: jonat
 */

#ifndef ELECTROMAGNET_H_
#define ELECTROMAGNET_H_

/* Include statements */
#include "msp.h"
#include <stdint.h>

class Electromagnet {
public:
    /* Constructor */
    Electromagnet(uint8_t * ctlDir, uint8_t * ctlOut, uint8_t ctlPin);

    /* High level Functions */
    void TurnOn();
    void TurnOff();
private:
    uint8_t * ctlDir;
    uint8_t * ctlOut;
    uint8_t ctlPin;
};


#endif /* ELECTROMAGNET_H_ */
