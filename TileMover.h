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
#include "ServoMotor.h"

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
    TileMover(StepperMotor * MotorX, StepperMotor * MotorY, StepperMotor * MotorZ, ServoMotor * Flipper, Electromagnet * pickup, Electromagnet * flipperEmag);

    void runCommand(command com);

    /* Functions to call */
    void DoNothing();
    void GetNewTiles(uint8_t num, uint8_t * x, uint8_t * y, uint8_t * handLocation);
    void MakeTileMoves(uint8_t num, uint8_t * x, uint8_t * y, uint8_t * handLocation, uint8_t * rotate);
    void GetNewTile(uint8_t x, uint8_t y, uint8_t hand);
    void MakeTileMove(uint8_t x, uint8_t y, uint8_t handLocation, uint8_t rotate);
    void PickupNewTile(uint8_t x, uint8_t y);
    void PickupHandTile(uint8_t x);
    void PickupBoard(uint8_t x, uint8_t y);
    void PickupRotator();
    void PickupFlipper();
    void DropOffNewTile(uint8_t x, uint8_t y);
    void DropOffHand(uint8_t x);
    void DropOffBoard(uint8_t x, uint8_t y);
    void DropOffRotator();
    void DropOffFlipper();
    void RotateTile();
    void FlipTile();
    void GoZPos(uint8_t z);
    void TurnOnMagnet();
    void TurnOffMagnet();
    bool IsBusy();
private:
    void resetMotors();

    static StepperMotor * MotorX;
    static StepperMotor * MotorY;
    static StepperMotor * MotorZ;
    static ServoMotor * Flipper;
    static Electromagnet * pickup;
    static Electromagnet * flipperEmag;

    static int32_t handX[7];
    static int32_t handY[7];
    static int32_t newTileX[15][7];
    static int32_t newTileY[15][7];
    static int32_t boardX[15][15];
    static int32_t boardY[15][15];
    static int32_t z[6];
//    static int32_t rotatorX;
//    static int32_t rotatorY;
    static int32_t flipperXUp;
    static int32_t flipperYUp;
    static int32_t flipperXDown;
    static int32_t flipperYDown;

    static bool busy;
};


#endif /* TILEMOVER_H_ */
