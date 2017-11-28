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

typedef enum {
    doNothing, getNewTiles, makeTileMoves, getNewTile, makeTileMove, pickupNewTile, pickupHandTile, pickupBoard, pickupRotator, pickupFlipper, dropOffNewTile, dropOffHand, dropOffBoard, dropOffRotator, dropOffFlipper, rotateTile, flipTile, goZPos, turnOnMagnet, turnOffMagnet, isBusy
} commandType;

typedef struct {
    commandType command;
    uint8_t parameters [29];
} command;

class TileMover {
public:
    /* Constructors */
    TileMover();
    TileMover(StepperMotor * MotorX, StepperMotor * MotorY, StepperMotor * MotorZ, Electromagnet * Emag);

    void runCommand(command com);

//    /* Functions to call */
//    void doNothing();
//    void getNewTiles(uint8_t num, uint8_t * x, uint8_t * y, uint8_t * handLocation);
//    void makeTileMoves(uint8_t num, uint8_t * x, uint8_t * y, uint8_t * handLocation, uint8_t * rotate);
//    void getNewTile(uint8_t x, uint8_t y);
//    void makeTileMove(uint8_t x, uint8_t y, uint8_t handLocation, uint8_t rotate);
//    void pickupNewTile(uint8_t x, uint8_t y);
//    void pickupHandTile(uint8_t x);
//    void pickupBoard(uint8_t x, uint8_t y);
//    void pickupRotator();
//    void pickupFlipper();
//    void dropOffNewTile(uint8_t x, uint8_t y);
//    void dropOffHand(uint8_t x);
//    void dropOffBoard(uint8_t x, uint8_t y);
//    void dropOffRotator();
//    void dropOffFlipper();
//    void rotateTile();
//    void flipTile();
//    void goZPos(uint8_t z);
//    void turnOnMagnet();
//    void turnOffMagnet();
    bool IsBusy();
private:
    static StepperMotor * MotorX;
    static StepperMotor * MotorY;
    static StepperMotor * MotorZ;
    static Electromagnet * Emag;

    static int32_t handX[6];
    static int32_t handY[6];
    static int32_t newTileX[15][15];
    static int32_t newTileY[15][15];
    static int32_t boardX[15][15];
    static int32_t boardY[15][15];
    static int32_t z[6];
    static int32_t rotatorX;
    static int32_t rotatorY;
    static int32_t flipperX;
    static int32_t flipperY;
};


#endif /* TILEMOVER_H_ */
