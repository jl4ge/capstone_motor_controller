/*
 * uart.h
 *
 *  Created on: Nov 3, 2017
 *      Author: jonat
 */

#ifndef UART_H_
#define UART_H_

#include "msp.h"
#include "TileMover.h"

typedef enum {
    NewCommand, ReadingParameters, GettingNumParameters
} recieveParsingFSM;



void configureUART(TileMover * m);
command getNextCommand();
bool commandReady();

#endif /* UART_H_ */
