/*
 * TileMover.h
 *
 *  Created on: Oct 30, 2017
 *      Author: jonat
 */

#ifndef TILEMOVER_H_
#define TILEMOVER_H_

/* Include statements */
#include "msp.h"
#include <stdint.h>
#include "Electromagnet.h"
#include "StepperMotor.h"
#include "StepperMotorTimer.h"

class TileMover {
public:
    /* Constructors */
    TileMover();
    TileMover(StepperMotor MotorX, StepperMotor MotorY, StepperMotor MotorZ);

    /* Functions to call */
    void doNothing();
    void pickupNewTile(uint8_t x, uint8_t y);
    void pickupHandTile(uint8_t x);
    void pickupBoard(uint8_t x, uint8_t y);
    void pickupRotator();
    void pickupFlipper();
    void dropOffHand(uint8_t x);
    void dropOffBoard(uint8_t x, uint8_t y);
    void dropOffRotator();
    void dropOffFlipper();
    void getNewTile(uint8_t x, uint8_t y);
    void makeTileMove(uint8_t x, uint8_t y, uint8_t handLocation, uint8_t rotate);
    void getNewTiles(uint8_t num, uint8_t * x, uint8_t * y);
    void makeTileMoves(uint8_t num, uint8_t * x, uint8_t * y, uint8_t * handLocation, uint8_t * rotate);
    void rotateTile();
    void flipTile();
    void goDown(uint8_t z);
    void goUp(uint8_t z);
    void turnOnMagnet();
    void turnOffMagnet();
    bool isBusy();
private:
    StepperMotor MotorX;
    StepperMotor MotorY;
    StepperMotor MotorZ;
};


#endif /* TILEMOVER_H_ */
