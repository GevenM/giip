



// Basic MSP430 and driverLib #includes
#include "msp430.h"
#include "driverlib/MSP430F5xx_6xx/wdt_a.h"
#include "driverlib/MSP430F5xx_6xx/ucs.h"
#include "driverlib/MSP430F5xx_6xx/pmm.h"
#include "driverlib/MSP430F5xx_6xx/sfr.h"


#include "inc/hw_memmap.h"
#include "grlib.h"
#include "LcdDriver/Sharp96x96.h"
#include "driverlib.h"
#include <stdint.h>
#include <stdbool.h>

#include "hardware.h" // File that contains information regarding hardware and its initializations
#include "MonitoredVariables.h"
#include "DisplayOut.h"

#include "UpdateOperation.h"
#include "CreateBasalProfile.h"
#include "RemoveBasalProfile.h"
#include "ActivateBasalProfile.h"
#include "DeactivateBasalProfile.h"
#include "ActivateTemporaryBasal.h"
#include "DeactivateTemporaryBasal.h"
#include "CreateBolusPreset.h"
#include "RemoveBolusPreset.h"
#include "ActivateBolus.h"
#include "RTC.h"
#include "CreateReminder.h"
#include "RemoveReminder.h"

void InputEvents();
void InitBuzzer();
void ToggleBuzzer();
void ResetBuzzer();


#include "BasalProfiles.h"
#include "Flash.h"


void main(void){



    // Stop WDT
    WDT_A_hold(WDT_A_BASE);

    // Basic GPIO initialization
    boardInit();
    //timerInit();
    ledInit();
    buttonInit();

    clockInit(8000000);   // Config clocks. MCLK=SMCLK=FLL=8MHz; ACLK=REFO=32kHz

    InitRTC();
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN5);

    TIMER_A_generatePWM( TIMER_A2_BASE, TIMER_A_CLOCKSOURCE_ACLK, TIMER_A_CLOCKSOURCE_DIVIDER_8, 64, TIMER_A_CAPTURECOMPARE_REGISTER_2, TIMER_A_OUTPUTMODE_RESET_SET, 32 );




    // Set up the LCD
    Sharp96x96_LCDInit();

    InitDisplayContext ();



  	InitMonitoredVariables();
  	c_pwrStatus = e_pwrStatus_ready;
  	PrintScreen();

  	int prevMin;
  	int currentSec = 0;
  	int prevSec = 0;


	while(1){

		InputEvents();
		UpdateMonitoredVariables();

		DisplayOut();

		UpdateOperation();

		// Call Function Table functions
		CreateBasalProfile();
		RemoveBasalProfile();
		ActivateBasalProfile();
		DeactivateBasalProfile();
		ActivateTemporaryBasal();
		DeactivateTemporaryBasal();
		CreateBolusPreset();
		RemoveBolusPreset();
		ActivateBolus();
		CreateReminder();
		RemoveReminder();





		// If temporary basal is active we need to check how much is left. Decrement the duration every minute. If the duration is 0, stop the temp basal
		if( TemporaryBasalIsActive() ){
			if ( prevMin != GetCurrentMin() ) f_activeTmpBasal.Duration = f_activeTmpBasal.Duration - 1;
			if ( f_activeTmpBasal.Duration == 0 ) StopTemporaryBasal();
			prevMin = GetCurrentMin(); // Update minute roll over
			updateScreen = true;
		}

		// bolus is active, check if it's all delivered and stop bolus if it is
		if ( BolusIsActive() ){
			if ( f_activeBolus.Amount == 0 ) {
				CopyBolusPreset( &k_emptyBol, &f_activeBolus);
				updateScreen = true;
			}
		}

		// update screen every second
		currentSec = GetCurrentSec ();
		if ( currentSec != prevSec ){
			updateScreen = true;
			prevSec = currentSec;

			//ToggleBuzzer();
		}



		if(c_menuScreen != c_1_menuScreen){
			ClearScreen();
			PrintScreen();
			c_1_menuScreen = c_menuScreen;
			f_1_menuChoice = f_menuChoice;

		} else if (f_menuChoice != f_1_menuChoice || updateScreen ){
			PrintScreen();
			f_1_menuChoice = f_menuChoice;
			updateScreen = false;

		}


		__no_operation();

		InitMonitoredVariables();

	}
}

void InitBuzzer(){
	P2DIR |= BIT5;                       // P2.5 output
	P2SEL |= BIT5;                       // P2.5 options select
	TA2CCR0 = 128;                            // PWM Period/2
	TA2CCTL2 = OUTMOD_6;                      // CCR2 toggle
	TA2CCR2 = 96;                             // CCR2 PWM duty cycle
	TA2CTL = TASSEL_2 + MC_3 + TACLR;         // SMCLK, up-down mode, clear TAR


}

void ToggleBuzzer(){
;
}

void ResetBuzzer(){
	TA2CCTL2 = OUTMOD_5;                      // CCR2 reset
	TA2CCR2 = 96;                             // CCR2 PWM duty cycle
	TA2CTL = TASSEL_2 + MC_3 + TACLR;         // SMCLK, up-down mode, clear TAR
}

//Convert the input variables from buttons to discrete events by performing rising edge detection.
void InputEvents(){
	I_leftSelBtn = i_leftSelBtn & !i_1_leftSelBtn;
	i_1_leftSelBtn=i_leftSelBtn;

	I_middleSelBtn = i_middleSelBtn & !i_1_middleSelBtn;
	i_1_middleSelBtn=i_middleSelBtn;

	I_rightSelBtn = i_rightSelBtn & !i_1_rightSelBtn;
	i_1_rightSelBtn=i_rightSelBtn;

	I_leftDirBtn = i_leftDirBtn & !i_1_leftDirBtn;
	i_1_leftDirBtn=i_leftDirBtn;

	I_rightDirBtn = i_rightDirBtn & !i_1_rightDirBtn;
	i_1_rightDirBtn=i_rightDirBtn;

	I_upDirBtn = i_upDirBtn & !i_1_upDirBtn;
	i_1_upDirBtn=i_upDirBtn;

	I_downDirBtn = i_downDirBtn & !i_1_downDirBtn;
	i_1_downDirBtn=i_downDirBtn;
}

