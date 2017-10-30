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

/* Function prototypes */
void ConfigureClockModule();

void main(void) {
    /* Stops the watchdog timer */
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

	/* Sets the clock to run at 24 MHz. */
	ConfigureClockModule();

	/* Configures the motors with pins. */
	StepperMotor MotorX = StepperMotor((uint8_t *) &P1DIR, //uint8_t * enableDir,
                          (uint8_t *) &P5DIR, //uint8_t * dirDir,
                          (uint8_t *) &P3DIR, //uint8_t * stepDir,
                          (uint8_t *) &P1DIR, //uint8_t * resetDir,
                          (uint8_t *) &P1DIR, //uint8_t * faultDir,
                          (uint8_t *) &P5DIR, //uint8_t * sleepDir,
                          (uint8_t *) &P5DIR, //uint8_t * ms1Dir,
                          (uint8_t *) &P3DIR, //uint8_t * ms2Dir,
                          (uint8_t *) &P2DIR, //uint8_t * ms3Dir,

                          (uint8_t *) &P1OUT, //uint8_t * enableOut,
                          (uint8_t *) &P5OUT, //uint8_t * dirOut,
                          (uint8_t *) &P3OUT, //uint8_t * stepOut,
                          (uint8_t *) &P1OUT, //uint8_t * resetOut,
                          (uint8_t *) &P1OUT, //uint8_t * faultOut,
                          (uint8_t *) &P5OUT, //uint8_t * sleepOut,
                          (uint8_t *) &P5OUT, //uint8_t * ms1Out,
                          (uint8_t *) &P3OUT, //uint8_t * ms2Out,
                          (uint8_t *) &P2OUT, //uint8_t * ms3Out,

                          (uint8_t) BIT6, //uint8_t enablePin,
                          (uint8_t) BIT2, //uint8_t dirPin,
                          (uint8_t) BIT6, //uint8_t stepPin,
                          (uint8_t) BIT7, //uint8_t resetPin,
                          (uint8_t) BIT5, //uint8_t faultPin,
                          (uint8_t) BIT0, //uint8_t sleepPin,
                          (uint8_t) BIT7, //uint8_t ms1Pin,
                          (uint8_t) BIT0, //uint8_t ms2Pin,
                          (uint8_t) BIT5, //uint8_t ms3Pin,

                          (uint8_t *) &P1IN, //uint8_t * faultIn,
                          (uint8_t *) &P1REN); //uint8_t * faultRen);

	StepperMotor MotorY;
	StepperMotor MotorZ;

	/* Sets up the motor driver timer. */
	StepperMotorTimer timer = StepperMotorTimer(&MotorX, &MotorY, &MotorZ);

	/* Enables Interrupts */
	__enable_interrupts();

	/* Has the motor move in a pattern. */
	while (true) {
	    MotorX.goTo(0);

        while (MotorX.isMoving());

        MotorX.goTo(3000);

        while (MotorX.isMoving());

        MotorX.goTo(2000);

        while (MotorX.isMoving());

        MotorX.goTo(2500);

        while (MotorX.isMoving());

        MotorX.goTo(9000);

        while (MotorX.isMoving());
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
