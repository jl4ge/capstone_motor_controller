/*
 * TileMover.cpp
 *
 *  Created on: Oct 30, 2017
 *      Author: jonat
 */

#include "uart.h"
#include "TileMover.h"

StepperMotor * TileMover::MotorX = 0;
StepperMotor * TileMover::MotorY = 0;
StepperMotor * TileMover::MotorZ = 0;
ServoMotor * TileMover::Flipper = 0;
Electromagnet * TileMover::pickup = 0;
Electromagnet * TileMover::flipperEmag = 0;

int32_t TileMover::handX[7] = {3860, 4190, 4510, 4830, 5160, 5460, 5800};
int32_t TileMover::handY[7] = {2518, 2518, 2518, 2518, 2518, 2518, 2518};
int32_t TileMover::newTileX[7][15] = {
    5903,5580,5256,4932,4608,4284,3960,3636,3312,2988,2664,2340,2016,1693,1369,
    5903,5580,5256,4932,4608,4284,3960,3636,3312,2988,2664,2340,2016,1693,1369,
    5903,5580,5256,4932,4608,4284,3960,3636,3312,2988,2664,2340,2016,1693,1369,
    5903,5580,5256,4932,4608,4284,3960,3636,3312,2988,2664,2340,2016,1693,1369,
    5903,5580,5256,4932,4608,4284,3960,3636,3312,2988,2664,2340,2016,1693,1369,
    5903,5580,5256,4932,4608,4284,3960,3636,3312,2988,2664,2340,2016,1693,1369,
    5903,5580,5256,4932,4608,4284,3960,3636,3312,2988,2664,2340,2016,1693,1369,
};
int32_t TileMover::newTileY[7][15] = {
    3286,3287,3287,3288,3289,3290,3291,3292,3292,3293,3294,3295,3296,3297,3297,
    3640,3640,3640,3640,3640,3640,3640,3640,3640,3640,3640,3640,3640,3640,3640,
    4012,4012,4012,4012,4012,4012,4012,4012,4012,4012,4012,4012,4012,4012,4012,
    4375,4375,4375,4375,4375,4375,4375,4375,4375,4375,4375,4375,4375,4375,4375,
    4737,4737,4737,4737,4737,4737,4737,4737,4737,4737,4737,4737,4737,4737,4737,
    5100,5100,5100,5100,5100,5100,5100,5100,5100,5100,5100,5100,5100,5100,5100,
    5462,5462,5462,5462,5462,5462,5462,5462,5462,5462,5462,5462,5462,5462,5462,
};
int32_t TileMover::boardX[15][15] = {
    11180,10922,10614,10306,9998,9690,9382,9075,8767,8459,8151,7843,7535,7227,6920,
    11180,10922,10614,10306,9998,9690,9382,9075,8767,8459,8151,7843,7535,7227,6920,
    11180,10922,10614,10306,9998,9690,9382,9075,8767,8459,8151,7843,7535,7227,6920,
    11180,10922,10614,10306,9998,9690,9382,9075,8767,8459,8151,7843,7535,7227,6920,
    11180,10922,10614,10306,9998,9690,9382,9075,8767,8459,8151,7843,7535,7227,6920,
    11180,10922,10614,10306,9998,9690,9382,9075,8767,8459,8151,7843,7535,7227,6920,
    11180,10922,10614,10306,9998,9690,9382,9075,8767,8459,8151,7843,7535,7227,6920,
    11180,10922,10614,10306,9998,9690,9382,9075,8767,8459,8151,7843,7535,7227,6920,
    11180,10922,10614,10306,9998,9690,9382,9075,8767,8459,8151,7843,7535,7227,6920,
    11180,10922,10614,10306,9998,9690,9382,9075,8767,8459,8151,7843,7535,7227,6920,
    11180,10922,10614,10306,9998,9690,9382,9075,8767,8459,8151,7843,7535,7227,6920,
    11180,10922,10614,10306,9998,9690,9382,9075,8767,8459,8151,7843,7535,7227,6920,
    11180,10922,10614,10306,9998,9690,9382,9075,8767,8459,8151,7843,7535,7227,6920,
    11180,10922,10614,10306,9998,9690,9382,9075,8767,8459,8151,7843,7535,7227,6920,
    11180,10922,10614,10306,9998,9690,9382,9075,8767,8459,8151,7843,7535,7227,6920
};
int32_t TileMover::boardY[15][15] = {
    590,590,590,590,590,590,590,590,590,590,590,590,590,590,590,
    919,919,919,919,919,919,919,919,919,919,919,919,919,919,919,
    1248,1248,1248,1248,1248,1248,1248,1248,1248,1248,1248,1248,1248,1248,1248,
    1577,1577,1577,1577,1577,1577,1577,1577,1577,1577,1577,1577,1577,1577,1577,
    1907,1907,1907,1907,1907,1907,1907,1907,1907,1907,1907,1907,1907,1907,1907,
    2236,2236,2236,2236,2236,2236,2236,2236,2236,2236,2236,2236,2236,2236,2236,
    2565,2565,2565,2565,2565,2565,2565,2565,2565,2565,2565,2565,2565,2565,2565,
    2895,2895,2895,2895,2895,2895,2895,2895,2895,2895,2895,2895,2895,2895,2895,
    3224,3224,3224,3224,3224,3224,3224,3224,3224,3224,3224,3224,3224,3224,3224,
    3553,3553,3553,3553,3553,3553,3553,3553,3553,3553,3553,3553,3553,3553,3553,
    3882,3882,3882,3882,3882,3882,3882,3882,3882,3882,3882,3882,3882,3882,3882,
    4212,4212,4212,4212,4212,4212,4212,4212,4212,4212,4212,4212,4212,4212,4212,
    4541,4541,4541,4541,4541,4541,4541,4541,4541,4541,4541,4541,4541,4541,4541,
    4870,4870,4870,4870,4870,4870,4870,4870,4870,4870,4870,4870,4870,4870,4870,
    5200,5200,5200,5200,5200,5200,5200,5200,5200,5200,5200,5200,5200,5200,5200
};
int32_t TileMover::z[6] = {3600 /* New Tiles */, 3400 /* hand */, 3900 /* flipper DOWN */, 3400 /* board */, 2250 /* flipper UP */, 4400};
//int32_t TileMover::rotatorX = 1000;
//int32_t TileMover::rotatorY = 2000;
int32_t TileMover::flipperXDown = 1600;
int32_t TileMover::flipperYDown = 2400;
int32_t TileMover::flipperXUp = 240;
int32_t TileMover::flipperYUp = 2440;
bool TileMover::busy = false;

TileMover::TileMover(StepperMotor * MotorX, StepperMotor * MotorY, StepperMotor * MotorZ, ServoMotor * Flipper, Electromagnet * pickup, Electromagnet * flipperEmag) {
    if (this->MotorX == 0) {
        this->MotorX = MotorX;
    }

    if (this->MotorY == 0) {
        this->MotorY = MotorY;
    }

    if (this->MotorZ == 0) {
        this->MotorZ = MotorZ;
    }

    if (this->pickup == 0) {
        this->pickup = pickup;
    }

    if (this->Flipper == 0) {
        this->Flipper = Flipper;
    }

    if (this->flipperEmag == 0) {
        this->flipperEmag = flipperEmag;
    }

    /* Moves the motor a little bit away from the limit. */
    resetMotors();
}

void TileMover::resetMotors() {
    MotorX->resetLimits();
    MotorY->resetLimits();
    MotorZ->resetLimits();

    while(MotorX->isMoving() || MotorY->isMoving() || MotorZ->isMoving());

    MotorX->goTo(100);
    MotorY->goTo(100);
    MotorZ->goTo(Z_REST);

    while(MotorX->isMoving() || MotorY->isMoving() || MotorZ->isMoving());
}

void TileMover::runCommand(command com) {
    busy = true;

    switch (com.command) {
    case doNothing:
        DoNothing();
        break;
    case getNewTiles:
        GetNewTiles(com.parameters[0], &com.parameters[1], &com.parameters[com.parameters[0] + 1], &com.parameters[2*com.parameters[0] + 1]);
        break;
    case makeTileMoves:
        MakeTileMoves(com.parameters[0], &com.parameters[1], &com.parameters[com.parameters[0] + 1], &com.parameters[2*com.parameters[0] + 1], &com.parameters[3*com.parameters[0] + 1]);
        break;
    case getNewTile:
        GetNewTile(com.parameters[0], com.parameters[1], com.parameters[2]);
        break;
    case makeTileMove:
        MakeTileMove(com.parameters[0], com.parameters[1], com.parameters[2], com.parameters[3]);
        break;
    case pickupNewTile:
        PickupNewTile(com.parameters[0], com.parameters[1]);
        break;
    case pickupHandTile:
        PickupHandTile(com.parameters[0]);
        break;
    case pickupBoard:
        PickupBoard(com.parameters[0], com.parameters[1]);
        break;
    case pickupRotator:
        /* TODO -- write */
        break;
    case pickupFlipper:
        PickupFlipper();
        break;
    case dropOffNewTile:
        DropOffNewTile(com.parameters[0], com.parameters[1]);
        break;
    case dropOffHand:
        PickupHandTile(com.parameters[0]);
        break;
    case dropOffBoard:
        DropOffBoard(com.parameters[0], com.parameters[1]);
        break;
    case dropOffRotator:
        /* TODO -- write */
        break;
    case dropOffFlipper:
        DropOffFlipper();
        break;
    case rotateTile:
        /* TODO -- write */
        break;
    case flipTile:
        /* TODO -- write */
        break;
    case goZPos:
        /* TODO -- write */
//        MotorZ->goTo(this->z[com.parameters[0]]);
        break;
    case turnOnMagnet:
        pickup->TurnOn();
        break;
    case turnOffMagnet:
        pickup->TurnOff();
        break;
    case isBusy:
        /* TODO -- FIX later */
        EUSCI_A2->TXBUF = 1; // m.IsBusy();
        break;
    default:
        break;
    }

    busy = false;
}

void TileMover::GetNewTiles(uint8_t num, uint8_t * x, uint8_t * y, uint8_t * handLocation) {
    resetMotors();

    for (int i = 0; i < num; i++) {
        GetNewTile(x[i], y[i], handLocation[i]);
    }

    MotorX->goTo(100);
    MotorY->goTo(100);
    MotorZ->goTo(Z_REST);
    while(MotorX->isMoving() || MotorY->isMoving() || MotorZ->isMoving());
}

void TileMover::MakeTileMoves(uint8_t num, uint8_t * x, uint8_t * y, uint8_t * handLocation, uint8_t * rotate) {
    resetMotors();

    for (int i = 0; i < num; i++) {
        MakeTileMove(x[i], y[i], handLocation[i], rotate[i]);
    }

    MotorX->goTo(100);
    MotorY->goTo(100);
    MotorZ->goTo(Z_REST);
    while(MotorX->isMoving() || MotorY->isMoving() || MotorZ->isMoving());
}

void TileMover::MakeTileMove(uint8_t x, uint8_t y, uint8_t handLocation, uint8_t rotate) {
    PickupHandTile(handLocation);
    DropOffFlipper();
    MotorY->goTo(1600);
    while(MotorY->isMoving());
    FlipTile();
    PickupFlipper();
    /* TODO -- Maybe rotate. */
    DropOffBoard(x, y);
}

void TileMover::FlipTile() {
    Flipper->spin(true, 700);
    while(Flipper->isMoving());
    while(Flipper->isMoving());

    flipperEmag->TurnOn();

    Flipper->spin(false, 5000);
    while(Flipper->isMoving());
    while(Flipper->isMoving());
}

void TileMover::PickupNewTile(uint8_t x, uint8_t y) {
    int32_t x1 = newTileX[y][x];
    int32_t y1 = newTileY[y][x];
    MotorX->goTo(x1);
    MotorY->goTo(y1);
    while(MotorX->isMoving() || MotorY->isMoving());
    MotorZ->goTo(z[0]);
    while(MotorZ->isMoving());
    pickup->TurnOn();
    MotorZ->goTo(Z_REST);
    while(MotorZ->isMoving());
}

void TileMover::DropOffNewTile(uint8_t x, uint8_t y) {
    int32_t x1 = newTileX[y][x];
    int32_t y1 = newTileY[y][x];
    MotorX->goTo(x1);
    MotorY->goTo(y1);
    while(MotorX->isMoving() || MotorY->isMoving());
    MotorZ->goTo(z[0]);
    while(MotorZ->isMoving());
    pickup->TurnOff();
    MotorZ->goTo(Z_REST);
    while(MotorZ->isMoving());
}

void TileMover::DoNothing() {
    return;
}

void TileMover::PickupHandTile(uint8_t x) {
    int32_t x1 = handX[x];
    int32_t y1 = handY[x];
    MotorX->goTo(x1);
    MotorY->goTo(y1);
    while(MotorX->isMoving() || MotorY->isMoving());
    MotorZ->goTo(z[1]);
    while(MotorZ->isMoving());
    pickup->TurnOn();
    MotorZ->goTo(Z_REST);
    while(MotorZ->isMoving());
}

void TileMover::DropOffHand(uint8_t x) {
    int32_t x1 = handX[x];
    int32_t y1 = handY[x];
    MotorX->goTo(x1);
    MotorY->goTo(y1);
    while(MotorX->isMoving() || MotorY->isMoving());
    MotorZ->goTo(z[1]);
    while(MotorZ->isMoving());
    pickup->TurnOff();
    MotorZ->goTo(Z_REST);
    while(MotorZ->isMoving());
}

void TileMover::DropOffFlipper() {
    MotorX->goTo(flipperXDown);
    MotorY->goTo(flipperYDown);
    while(MotorX->isMoving() || MotorY->isMoving());
    MotorZ->goTo(z[2]);
    while(MotorZ->isMoving());
    MotorX->goTo(flipperXDown - 150);
    MotorY->goTo(flipperYDown - 200);
    while(MotorX->isMoving() || MotorY->isMoving());
    pickup->TurnOff();
    MotorZ->goTo(Z_REST);
    while(MotorZ->isMoving());
}

void TileMover::PickupFlipper() {
    MotorX->goTo(flipperXUp);
    MotorY->goTo(flipperYUp);
    while(MotorX->isMoving() || MotorY->isMoving());
    MotorZ->goTo(z[4]);
    while(MotorZ->isMoving());
    pickup->TurnOn();
    flipperEmag->TurnOff();
    MotorZ->goTo(Z_REST);
    while(MotorZ->isMoving());
}

void TileMover::PickupBoard(uint8_t x, uint8_t y) {
    int32_t x1 = boardX[y][x];
    int32_t y1 = boardY[y][x];
    MotorX->goTo(x1);
    MotorY->goTo(y1);
    while(MotorX->isMoving() || MotorY->isMoving());
    MotorZ->goTo(z[3]);
    while(MotorZ->isMoving());
    pickup->TurnOn();
    MotorZ->goTo(Z_REST);
    while(MotorZ->isMoving());
}

void TileMover::DropOffBoard(uint8_t x, uint8_t y) {
    int32_t x1 = boardX[y][x];
    int32_t y1 = boardY[y][x];
    MotorX->goTo(x1);
    MotorY->goTo(y1);
    while(MotorX->isMoving() || MotorY->isMoving());
    MotorZ->goTo(z[3]);
    while(MotorZ->isMoving());
    pickup->TurnOff();
    MotorZ->goTo(Z_REST);
    while(MotorZ->isMoving());
}

void TileMover::GetNewTile(uint8_t x, uint8_t y, uint8_t hand) {
    PickupNewTile(x, y);
    DropOffHand(hand);
}

bool TileMover::IsBusy() {
    return busy;
}
