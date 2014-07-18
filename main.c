



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
#include "stdint.h"

#include "hardware.h" // File that contains information regarding hardware and its initializations
#include "MonitoredVariables.h"
#include "DisplayOut.h"

#include "UpdateOperation.h"
#include "CreateBasalProfile.h"
#include "RemoveBasalProfile.h"
#include "ActivateBasalProfile.h"
#include "DeactivateBasalProfile.h"

void Delay(void);
void SavePreviousInput();
void InputEvents();



#include "BasalProfiles.h"
#include "Flash.h"

void main(void){

    // Stop WDT
    WDT_A_hold(WDT_A_BASE);

    // Basic GPIO initialization
    boardInit();
    timerInit();
    //ledInit();
    buttonInit();

    clockInit(8000000);   // Config clocks. MCLK=SMCLK=FLL=8MHz; ACLK=REFO=32kHz


    // Set up the LCD
    Sharp96x96_LCDInit();

    GrContextInit(&g_sContext, &g_sharp96x96LCD);
  	GrContextForegroundSet(&g_sContext, ClrBlack);
  	GrContextBackgroundSet(&g_sContext, ClrWhite);
  	GrContextFontSet(&g_sContext, &g_sFontFixed6x8);
  	GrClearDisplay(&g_sContext);
  	GrFlush(&g_sContext);


  	InitMonitoredVariables();
  	c_pwrStatus = Ready;
  	PrintScreen();

	while(1){

		InputEvents();
		UpdateMonitoredVariables();

		DisplayOut();

		CreateBasalProfile();
		RemoveBasalProfile();
		ActivateBasalProfile();
		DeactivateBasalProfile();
		ActivateTemporaryBasal();

		UpdateOperation();




		if(c_menuScreen != c_1_menuScreen){
			ClearScreen();
			PrintScreen();
			c_1_menuScreen = c_menuScreen;
			f_1_menuChoice = f_menuChoice;
		} else if (f_menuChoice != f_1_menuChoice || updateScreen){
			PrintScreen();
			f_1_menuChoice = f_menuChoice;
			updateScreen = false;
		}

		__no_operation();

		InitMonitoredVariables();

	}
}




void Delay(void){
	__delay_cycles(SYSTEM_CLOCK_SPEED*4);
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
