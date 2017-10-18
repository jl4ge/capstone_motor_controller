#include "msp.h"
#include "StepperMotor.h"

/**
 * main.c
 */
void main(void)
{

	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	StepperMotor MotorX = StepperMotor(uint8_t * enableDir,
	                                   uint8_t * dirDir,
	                                   uint8_t * stepDir,
	                                   uint8_t * resetDir,
	                                   uint8_t * faultDir,
	                                   uint8_t * sleepDir,
	                                   uint8_t * ms1Dir,
	                                   uint8_t * ms2Dir,
	                                   uint8_t * ms3Dir,

	                                   uint8_t * enableOut,
	                                   uint8_t * dirOut,
	                                   uint8_t * stepOut,
	                                   uint8_t * resetOut,
	                                   uint8_t * sleepOut,
	                                   uint8_t * ms1Out,
	                                   uint8_t * ms2Out,
	                                   uint8_t * ms3Out,

	                                   uint8_t enablePin,
	                                   uint8_t dirPin,
	                                   uint8_t stepPin,
	                                   uint8_t resetPin,
	                                   uint8_t faultPin,
	                                   uint8_t sleepPin,
	                                   uint8_t ms1Pin,
	                                   uint8_t ms2Pin,
	                                   uint8_t ms3Pin,

	                                   uint8_t * faultIn);


	while (1) {

	}
}
