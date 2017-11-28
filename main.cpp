/*
 * main.cpp
 *
 *  Created on: Oct 17, 2017
 *      Author: jonat
 */

/* Include statements */
#include "msp.h"
#include "StepperMotor.h"
#include "StepperMotorTimer.h"
#include "Electromagnet.h"
#include "LimitSwitchs.h"
#include "uart.h"
#include "TileMover.h"
#include "ServoMotor.h"
#include "ServoMotorTimer.h"

/* Function prototypes */
void ConfigureClockModule();

void main(void) {
    /* Stops the watchdog timer */
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

	/* Sets the clock to run at 24 MHz. */
	ConfigureClockModule();

	/* Configures the motors with pins. */
	StepperMotor MotorX = StepperMotor((uint8_t *) &P7DIR, //uint8_t * enableDir,
	                                        (uint8_t *) &P7DIR, //uint8_t * dirDir,
	                                        (uint8_t *) &P9DIR, //uint8_t * stepDir,
	                                        (uint8_t *) &P9DIR, //uint8_t * resetDir,
	                                        (uint8_t *) &P6DIR, //uint8_t * faultDir,
	                                        (uint8_t *) &P9DIR, //uint8_t * sleepDir,
	                                        (uint8_t *) &P7DIR, //uint8_t * ms1Dir,
	                                        (uint8_t *) &P8DIR, //uint8_t * ms2Dir,
	                                        (uint8_t *) &P9DIR, //uint8_t * ms3Dir,

	                                        (uint8_t *) &P7OUT, //uint8_t * enableOut,
	                                        (uint8_t *) &P7OUT, //uint8_t * dirOut,
	                                        (uint8_t *) &P9OUT, //uint8_t * stepOut,
	                                        (uint8_t *) &P9OUT, //uint8_t * resetOut,
	                                        (uint8_t *) &P6OUT, //uint8_t * faultOut,
	                                        (uint8_t *) &P9OUT, //uint8_t * sleepOut,
	                                        (uint8_t *) &P7OUT, //uint8_t * ms1Out,
	                                        (uint8_t *) &P8OUT, //uint8_t * ms2Out,
	                                        (uint8_t *) &P9OUT, //uint8_t * ms3Out,

	                                        (uint8_t) BIT4, //uint8_t enablePin,
	                                        (uint8_t) BIT0, //uint8_t dirPin,
	                                        (uint8_t) BIT4, //uint8_t stepPin,
	                                        (uint8_t) BIT7, //uint8_t resetPin,
	                                        (uint8_t) BIT2, //uint8_t faultPin,
	                                        (uint8_t) BIT6, //uint8_t sleepPin,
	                                        (uint8_t) BIT5, //uint8_t ms1Pin,
	                                        (uint8_t) BIT0, //uint8_t ms2Pin,
	                                        (uint8_t) BIT5, //uint8_t ms3Pin,

	                                        (uint8_t *) &P6IN, //uint8_t * faultIn,
	                                        (uint8_t *) &P6REN); //uint8_t * faultRen);

	StepperMotor MotorY = StepperMotor((uint8_t *) &P9DIR, //uint8_t * enableDir,
                          (uint8_t *) &P8DIR, //uint8_t * dirDir,
                          (uint8_t *) &P9DIR, //uint8_t * stepDir,
                          (uint8_t *) &P9DIR, //uint8_t * resetDir,
                          (uint8_t *) &P6DIR, //uint8_t * faultDir,
                          (uint8_t *) &P8DIR, //uint8_t * sleepDir,
                          (uint8_t *) &P8DIR, //uint8_t * ms1Dir,
                          (uint8_t *) &P8DIR, //uint8_t * ms2Dir,
                          (uint8_t *) &P8DIR, //uint8_t * ms3Dir,

                          (uint8_t *) &P9OUT, //uint8_t * enableOut,
                          (uint8_t *) &P8OUT, //uint8_t * dirOut,
                          (uint8_t *) &P9OUT, //uint8_t * stepOut,
                          (uint8_t *) &P9OUT, //uint8_t * resetOut,
                          (uint8_t *) &P6OUT, //uint8_t * faultOut,
                          (uint8_t *) &P8OUT, //uint8_t * sleepOut,
                          (uint8_t *) &P8OUT, //uint8_t * ms1Out,
                          (uint8_t *) &P8OUT, //uint8_t * ms2Out,
                          (uint8_t *) &P8OUT, //uint8_t * ms3Out,

                          (uint8_t) BIT2, //uint8_t enablePin,
                          (uint8_t) BIT6, //uint8_t dirPin,
                          (uint8_t) BIT0, //uint8_t stepPin,
                          (uint8_t) BIT1, //uint8_t resetPin,
                          (uint8_t) BIT3, //uint8_t faultPin,
                          (uint8_t) BIT4, //uint8_t sleepPin,
                          (uint8_t) BIT3, //uint8_t ms1Pin,
                          (uint8_t) BIT2, //uint8_t ms2Pin,
                          (uint8_t) BIT7, //uint8_t ms3Pin,

                          (uint8_t *) &P6IN, //uint8_t * faultIn,
                          (uint8_t *) &P6REN); //uint8_t * faultRen);

	StepperMotor MotorZ = StepperMotor((uint8_t *) &P10DIR, //uint8_t * enableDir,
                          (uint8_t *) &P7DIR, //uint8_t * dirDir,
                          (uint8_t *) &P7DIR, //uint8_t * stepDir,
                          (uint8_t *) &P10DIR, //uint8_t * resetDir,
                          (uint8_t *) &P5DIR, //uint8_t * faultDir,
                          (uint8_t *) &P10DIR, //uint8_t * sleepDir,
                          (uint8_t *) &P10DIR, //uint8_t * ms1Dir,
                          (uint8_t *) &P10DIR, //uint8_t * ms2Dir,
                          (uint8_t *) &P10DIR, //uint8_t * ms3Dir,

                          (uint8_t *) &P10OUT, //uint8_t * enableOut,
                          (uint8_t *) &P7OUT, //uint8_t * dirOut,
                          (uint8_t *) &P7OUT, //uint8_t * stepOut,
                          (uint8_t *) &P10OUT, //uint8_t * resetOut,
                          (uint8_t *) &P5OUT, //uint8_t * faultOut,
                          (uint8_t *) &P10OUT, //uint8_t * sleepOut,
                          (uint8_t *) &P10OUT, //uint8_t * ms1Out,
                          (uint8_t *) &P10OUT, //uint8_t * ms2Out,
                          (uint8_t *) &P10OUT, //uint8_t * ms3Out,

                          (uint8_t) BIT4, //uint8_t enablePin,
                          (uint8_t) BIT7, //uint8_t dirPin,
                          (uint8_t) BIT6, //uint8_t stepPin,
                          (uint8_t) BIT3, //uint8_t resetPin,
                          (uint8_t) BIT3, //uint8_t faultPin,
                          (uint8_t) BIT0, //uint8_t sleepPin,
                          (uint8_t) BIT5, //uint8_t ms1Pin,
                          (uint8_t) BIT2, //uint8_t ms2Pin,
                          (uint8_t) BIT1, //uint8_t ms3Pin,

                          (uint8_t *) &P5IN, //uint8_t * faultIn,
                          (uint8_t *) &P5REN); //uint8_t * faultRen);

	LimitSwitchs switches = LimitSwitchs((uint8_t) BIT0, // uint8_t xPin,
	                                     (uint8_t) BIT1, // uint8_t yPin,
	                                     (uint8_t) BIT2, // uint8_t zPin,
	                                     (uint8_t *) &P5DIR, // uint8_t * xDir,
	                                     (uint8_t *) &P5DIR, // uint8_t * yDir,
	                                     (uint8_t *) &P5DIR, // uint8_t * zDir,
	                                     (uint8_t *) &P5IN, // uint8_t * xIn,
	                                     (uint8_t *) &P5IN, // uint8_t * yIn,
	                                     (uint8_t *) &P5IN, // uint8_t * zIn,
	                                     (uint8_t *) &P5IE, // uint8_t * xIE,
	                                     (uint8_t *) &P5IE, // uint8_t * yIE,
	                                     (uint8_t *) &P5IE, // uint8_t * zIE,
	                                     (uint8_t *) &P5IFG, // uint8_t * xIFG,
	                                     (uint8_t *) &P5IFG, // uint8_t * yIFG,
	                                     (uint8_t *) &P5IFG, // uint8_t * zIFG,
	                                     &MotorX,
	                                     &MotorY,
	                                     &MotorZ);

	Electromagnet emag = Electromagnet((uint8_t *) &P5DIR, // uint8_t * ctlDir,
	                                   (uint8_t *) &P5OUT, // uint8_t * ctlOut,
	                                   (uint8_t) BIT6); // uint8_t ctlPin);

	/* Sets up the motor driver timer. */
	StepperMotorTimer stepperTimer = StepperMotorTimer(&MotorX, &MotorY, &MotorZ);

	/* Sets up the servo motors with their timer. */
	ServoMotor flipper = ServoMotor((uint8_t *) &P2DIR, (uint8_t *) &P2OUT, BIT6);
	ServoMotor rotator = ServoMotor((uint8_t *) &P2DIR, (uint8_t *) &P2OUT, BIT7);
	ServoMotorTimer servoTimer = ServoMotorTimer(&flipper, &rotator);

	TileMover mover = TileMover(&MotorX, &MotorY, &MotorZ, &emag);

	emag.TurnOn();

	configureUART(&mover);

	/* Enables Interrupts */
	__enable_interrupts();

	command currentCommand;

	rotator.spin(true);
	flipper.spin(false);

	/* Waits until the motor reaches the limit. */
	while (MotorX.isMoving() || MotorY.isMoving() || MotorZ.isMoving());

	/* Moves the motor a little bit away from the limit. */
    MotorX.goTo(100);
    MotorY.goTo(100);
    MotorZ.goTo(100);
    while (MotorX.isMoving() || MotorY.isMoving() || MotorZ.isMoving());

//	while (true) {
//	    /* TODO -- Wait for current command to finish */
//	    while (!commandReady() || mover.IsBusy());
//	    currentCommand = getNextCommand();
//
//	    mover.runCommand(currentCommand);
//	}

	/* Has the motor move in a pattern. */

    command c;
    c.command = dropOffNewTile;
    c.parameters[0] = 1;
    c.parameters[1] = 2;
	while (true) {

	    while (MotorX.isMoving() || MotorY.isMoving() || MotorZ.isMoving());

	    c.parameters[0] = 1;
	    c.parameters[1] = 2;
	    mover.runCommand(c);

        while (MotorX.isMoving() || MotorY.isMoving() || MotorZ.isMoving());

        c.parameters[0] = 10;
        c.parameters[1] = 13;
        mover.runCommand(c);

        while (MotorX.isMoving() || MotorY.isMoving() || MotorZ.isMoving());

        c.parameters[0] = 3;
        c.parameters[1] = 7;
        mover.runCommand(c);

        while (MotorX.isMoving() || MotorY.isMoving() || MotorZ.isMoving());

        c.parameters[0] = 7;
        c.parameters[1] = 3;
        mover.runCommand(c);

        while (MotorX.isMoving() || MotorY.isMoving() || MotorZ.isMoving());

        c.parameters[0] = 0;
        c.parameters[1] = 0;
        mover.runCommand(c);

        while (MotorX.isMoving() || MotorY.isMoving() || MotorZ.isMoving());

        c.parameters[0] = 14;
        c.parameters[1] = 14;
        mover.runCommand(c);

        while (MotorX.isMoving() || MotorY.isMoving() || MotorZ.isMoving());

        c.parameters[0] = 4;
        c.parameters[1] = 12;
        mover.runCommand(c);
	}
}

/* Configures the digitally controlled oscillator to run at 24 MHz. */
void ConfigureClockModule(void) {
    CS->KEY = CS_KEY_VAL;
    CS->CTL0 = 0;
    CS->CTL0 = CS_CTL0_DCORSEL_4;
    CS->CTL1 = CS_CTL1_SELA_2 | CS_CTL1_SELS_3 | CS_CTL1_SELM_3;
    CS->KEY = 0;
}
