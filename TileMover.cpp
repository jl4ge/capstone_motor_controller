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

int32_t TileMover::handX[7] = {6000, 6200, 6400, 6600, 6800, 7000, 7200};
int32_t TileMover::handY[7] = {3000, 3000, 3000, 3000, 3000, 3000, 3000};
int32_t TileMover::newTileX[15][7] = {
    6000, 6400, 6800, 7200, 7600, 8000, 8400, 8800, 9200, 9600, 10000, 10400, 10800, 11200, 11600,
    6000, 6400, 6800, 7200, 7600, 8000, 8400, 8800, 9200, 9600, 10000, 10400, 10800, 11200, 11600,
    6000, 6400, 6800, 7200, 7600, 8000, 8400, 8800, 9200, 9600, 10000, 10400, 10800, 11200, 11600,
    6000, 6400, 6800, 7200, 7600, 8000, 8400, 8800, 9200, 9600, 10000, 10400, 10800, 11200, 11600,
    6000, 6400, 6800, 7200, 7600, 8000, 8400, 8800, 9200, 9600, 10000, 10400, 10800, 11200, 11600,
    6000, 6400, 6800, 7200, 7600, 8000, 8400, 8800, 9200, 9600, 10000, 10400, 10800, 11200, 11600,
    6000, 6400, 6800, 7200, 7600, 8000, 8400, 8800, 9200, 9600, 10000, 10400, 10800, 11200, 11600
};
int32_t TileMover::newTileY[15][7] = {
    3500, 3500, 3500, 3500, 3500, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000,
    3200, 3200, 3200, 3200, 3200, 3200, 3200, 3200, 3200, 3200, 3200, 3200, 3200, 3200, 3200,
    3400, 3400, 3400, 3400, 3400, 3400, 3400, 3400, 3400, 3400, 3400, 3400, 3400, 3400, 3400,
    3600, 3600, 3600, 3600, 3600, 3600, 3600, 3600, 3600, 3600, 3600, 3600, 3600, 3600, 3600,
    3800, 3800, 3800, 3800, 3800, 3800, 3800, 3800, 3800, 3800, 3800, 3800, 3800, 3800, 3800,
    4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000,
    4200, 4200, 4200, 4200, 4200, 4200, 4200, 4200, 4200, 4200, 4200, 4200, 4200, 4200, 4200
};
int32_t TileMover::boardX[15][15] = {
    1000, 1200, 1400, 1600, 1800, 2000, 2200, 2400, 2600, 2800, 3000, 3200, 3400, 3600, 3800,
    1000, 1200, 1400, 1600, 1800, 2000, 2200, 2400, 2600, 2800, 3000, 3200, 3400, 3600, 3800,
    1000, 1200, 1400, 1600, 1800, 2000, 2200, 2400, 2600, 2800, 3000, 3200, 3400, 3600, 3800,
    1000, 1200, 1400, 1600, 1800, 2000, 2200, 2400, 2600, 2800, 3000, 3200, 3400, 3600, 3800,
    1000, 1200, 1400, 1600, 1800, 2000, 2200, 2400, 2600, 2800, 3000, 3200, 3400, 3600, 3800,
    1000, 1200, 1400, 1600, 1800, 2000, 2200, 2400, 2600, 2800, 3000, 3200, 3400, 3600, 3800,
    1000, 1200, 1400, 1600, 1800, 2000, 2200, 2400, 2600, 2800, 3000, 3200, 3400, 3600, 3800,
    1000, 1200, 1400, 1600, 1800, 2000, 2200, 2400, 2600, 2800, 3000, 3200, 3400, 3600, 3800,
    1000, 1200, 1400, 1600, 1800, 2000, 2200, 2400, 2600, 2800, 3000, 3200, 3400, 3600, 3800,
    1000, 1200, 1400, 1600, 1800, 2000, 2200, 2400, 2600, 2800, 3000, 3200, 3400, 3600, 3800,
    1000, 1200, 1400, 1600, 1800, 2000, 2200, 2400, 2600, 2800, 3000, 3200, 3400, 3600, 3800,
    1000, 1200, 1400, 1600, 1800, 2000, 2200, 2400, 2600, 2800, 3000, 3200, 3400, 3600, 3800,
    1000, 1200, 1400, 1600, 1800, 2000, 2200, 2400, 2600, 2800, 3000, 3200, 3400, 3600, 3800,
    1000, 1200, 1400, 1600, 1800, 2000, 2200, 2400, 2600, 2800, 3000, 3200, 3400, 3600, 3800,
    1000, 1200, 1400, 1600, 1800, 2000, 2200, 2400, 2600, 2800, 3000, 3200, 3400, 3600, 3800
};
int32_t TileMover::boardY[15][15] = {
    1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
    1200, 1200, 1200, 1200, 1200, 1200, 1200, 1200, 1200, 1200, 1200, 1200, 1200, 1200, 1200,
    1400, 1400, 1400, 1400, 1400, 1400, 1400, 1400, 1400, 1400, 1400, 1400, 1400, 1400, 1400,
    1600, 1600, 1600, 1600, 1600, 1600, 1600, 1600, 1600, 1600, 1600, 1600, 1600, 1600, 1600,
    1800, 1800, 1800, 1800, 1800, 1800, 1800, 1800, 1800, 1800, 1800, 1800, 1800, 1800, 1800,
    2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    2200, 2200, 2200, 2200, 2200, 2200, 2200, 2200, 2200, 2200, 2200, 2200, 2200, 2200, 2200,
    2400, 2400, 2400, 2400, 2400, 2400, 2400, 2400, 2400, 2400, 2400, 2400, 2400, 2400, 2400,
    2600, 2600, 2600, 2600, 2600, 2600, 2600, 2600, 2600, 2600, 2600, 2600, 2600, 2600, 2600,
    2800, 2800, 2800, 2800, 2800, 2800, 2800, 2800, 2800, 2800, 2800, 2800, 2800, 2800, 2800,
    3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000,
    3200, 3200, 3200, 3200, 3200, 3200, 3200, 3200, 3200, 3200, 3200, 3200, 3200, 3200, 3200,
    3400, 3400, 3400, 3400, 3400, 3400, 3400, 3400, 3400, 3400, 3400, 3400, 3400, 3400, 3400,
    3600, 3600, 3600, 3600, 3600, 3600, 3600, 3600, 3600, 3600, 3600, 3600, 3600, 3600, 3600,
    3800, 3800, 3800, 3800, 3800, 3800, 3800, 3800, 3800, 3800, 3800, 3800, 3800, 3800, 3800
};
int32_t TileMover::z[6] = {500 /* New Tiles */, 500 /* hand */, 500 /* flipper */, 500 /* board */, 230, 300};
//int32_t TileMover::rotatorX = 1000;
//int32_t TileMover::rotatorY = 2000;
int32_t TileMover::flipperXDown = 5000;
int32_t TileMover::flipperYDown = 5000;
int32_t TileMover::flipperXUp = 5500;
int32_t TileMover::flipperYUp = 5000;
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
    MotorZ->goTo(100);

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
    MotorZ->goTo(100);
    while(MotorX->isMoving() || MotorY->isMoving() || MotorZ->isMoving());
}

void TileMover::MakeTileMoves(uint8_t num, uint8_t * x, uint8_t * y, uint8_t * handLocation, uint8_t * rotate) {
    resetMotors();

    for (int i = 0; i < num; i++) {
        MakeTileMove(x[i], y[i], handLocation[i], rotate[i]);
    }

    MotorX->goTo(100);
    MotorY->goTo(100);
    MotorZ->goTo(100);
    while(MotorX->isMoving() || MotorY->isMoving() || MotorZ->isMoving());
}

void TileMover::MakeTileMove(uint8_t x, uint8_t y, uint8_t handLocation, uint8_t rotate) {
    PickupHandTile(handLocation);
    DropOffFlipper();
    FlipTile();
    PickupFlipper();
    /* TODO -- Maybe rotate. */
    DropOffBoard(x, y);
}

void TileMover::FlipTile() {

}

void TileMover::PickupNewTile(uint8_t x, uint8_t y) {
    int32_t x1 = newTileX[x][y];
    int32_t y1 = newTileY[x][y];
    MotorX->goTo(x1);
    MotorY->goTo(y1);
    while(MotorX->isMoving() || MotorY->isMoving());
    MotorZ->goTo(z[0]);
    while(MotorZ->isMoving());
    pickup->TurnOn();
    MotorZ->goTo(100);
    while(MotorZ->isMoving());
}

void TileMover::DropOffNewTile(uint8_t x, uint8_t y) {
    int32_t x1 = newTileX[x][y];
    int32_t y1 = newTileY[x][y];
    MotorX->goTo(x1);
    MotorY->goTo(y1);
    while(MotorX->isMoving() || MotorY->isMoving());
    MotorZ->goTo(z[0]);
    while(MotorZ->isMoving());
    pickup->TurnOff();
    MotorZ->goTo(100);
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
    MotorZ->goTo(100);
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
    MotorZ->goTo(100);
    while(MotorZ->isMoving());
}

void TileMover::DropOffFlipper() {
    MotorX->goTo(flipperXDown);
    MotorY->goTo(flipperYDown);
    while(MotorX->isMoving() || MotorY->isMoving());
    MotorZ->goTo(z[2]);
    while(MotorZ->isMoving());
    pickup->TurnOff();
    MotorZ->goTo(100);
    while(MotorZ->isMoving());
}

void TileMover::PickupFlipper() {
    MotorX->goTo(flipperXUp);
    MotorY->goTo(flipperYUp);
    while(MotorX->isMoving() || MotorY->isMoving());
    MotorZ->goTo(z[2]);
    while(MotorZ->isMoving());
    pickup->TurnOn();
    MotorZ->goTo(100);
    while(MotorZ->isMoving());
}

void TileMover::PickupBoard(uint8_t x, uint8_t y) {
    int32_t x1 = boardX[x][y];
    int32_t y1 = boardY[x][y];
    MotorX->goTo(x1);
    MotorY->goTo(y1);
    while(MotorX->isMoving() || MotorY->isMoving());
    MotorZ->goTo(z[3]);
    while(MotorZ->isMoving());
    pickup->TurnOn();
    MotorZ->goTo(100);
    while(MotorZ->isMoving());
}

void TileMover::DropOffBoard(uint8_t x, uint8_t y) {
    int32_t x1 = boardX[x][y];
    int32_t y1 = boardY[x][y];
    MotorX->goTo(x1);
    MotorY->goTo(y1);
    while(MotorX->isMoving() || MotorY->isMoving());
    MotorZ->goTo(z[3]);
    while(MotorZ->isMoving());
    pickup->TurnOff();
    MotorZ->goTo(100);
    while(MotorZ->isMoving());
}

void TileMover::GetNewTile(uint8_t x, uint8_t y, uint8_t hand) {
    PickupNewTile(x, y);
    DropOffHand(hand);
}

bool TileMover::IsBusy() {
    return busy;
}
