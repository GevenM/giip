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
#include "BasalFunctions/BasalFunctions.h"
#include "TemporaryBasalFunctions/TemporaryBasalFunctions.h"
#include "BolusFunctions/BolusFunctions.h"

#include "RTC.h"
#include "ReminderFunctions/CreateReminder.h"
#include "ReminderFunctions/RemoveReminder.h"

#include "InsulinDeliveryMechanism.h"
#include "InsulinReservoir.h"

#include "SafetyStatus.h"

void InputEvents();

#include "BasalProfiles.h"
#include "Flash.h"

void main(void){

    // Stop WDT
    WDT_A_hold(WDT_A_BASE);


    // Initializations of Hardware and Software
    InitHardware();
    InitClock(8000000);   // Config clocks. MCLK=SMCLK=FLL=8MHz; ACLK=REFO=32kHz
    InitRTC();
    InitInsulinDeliveryMechanism();
    InitInsulinReservoirSensor();
    Sharp96x96_LCDInit(); // Set up the LCD
    InitDisplayContext ();
  	InitMonitoredVariables();


  	c_pwrStatus = e_pwrStatus_ready; // Should probably be done by a POST
  	EnableInsulinDeliveryMechanism();

  	PrintScreen();

  	int currentSec = 0;
  	int prevSec = 0;



	while(1){

		InputEvents();
		UpdateMonitoredVariables();
		UpdateInsulinReservoirSensor();
		UpdateSafetyStatus();

		if ( c_safetyStatus == e_bubbleInLine || c_safetyStatus == e_occlusionInLine || c_safetyStatus == e_emptyReservoir ){
			c_pwrStatus = e_pwrStatus_error;
		} else {
			c_pwrStatus = e_pwrStatus_ready;
		}

		DisplayOut();

		// Call Function Table functions
		CreateBasalProfile(); // 7
		RemoveBasalProfile(); // 10
		UpdateBasalProfileSet(); //39

		ActivateBasalProfile(); // 13
		DeactivateBasalProfile(); // 16
		UpdateActiveBasalProfile(); //40

		ActivateTemporaryBasal(); // 18
		DeactivateTemporaryBasal(); //21
		UpdateActiveTemporaryBasal(); //41


		CreateBolusPreset(); // 23, 24
		RemoveBolusPreset(); // 26, 27
		ActivateBolus(); // 28, 29
		UpdateBolusPresetSet();
		UpdateActiveBolus();

		// bolus is active, check if it's all delivered and stop bolus if it is
		//if ( BolusIsActive() ){
		//	if ( f_activeBolus.Amount + (int)(GetInsulinOutputBuffer()+0.5) <= 16 ) {
		//		CopyBolusPreset( &k_emptyBol, &f_activeBolus);
		//		updateScreen = true;
		//	}
		//}



		CreateReminder(); //34, 35
		RemoveReminder(); //37, 38
		UpdateOperation(); //6

		ResetFVariablesBasal();
		ResetFVariablesTemporaryBasal();
		ResetFVariablesBolus();

		DeliverPendingInsulin();






		// update screen every second
		currentSec = GetCurrentSec ();
		if ( currentSec != prevSec ){
			updateScreen = true;
			prevSec = currentSec;
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

		InitMonitoredVariables();
	}
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


	I_sensor1Btn = i_sensor1Btn &! i_1_sensor1Btn;
	i_1_sensor1Btn = i_sensor1Btn;

	I_sensor2Btn = i_sensor2Btn &! i_1_sensor2Btn;
	i_1_sensor2Btn = i_sensor2Btn;
}



