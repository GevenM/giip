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
#include "BasalFunctions/CreateBasalProfile.h"
#include "BasalFunctions/RemoveBasalProfile.h"
#include "BasalFunctions/ActivateBasalProfile.h"
#include "BasalFunctions/DeactivateBasalProfile.h"
#include "TemporaryBasalFunctions/ActivateTemporaryBasal.h"
#include "TemporaryBasalFunctions/DeactivateTemporaryBasal.h"
#include "BolusFunctions/CreateBolusPreset.h"
#include "BolusFunctions/RemoveBolusPreset.h"
#include "BolusFunctions/ActivateBolus.h"
#include "RTC.h"
#include "ReminderFunctions/CreateReminder.h"
#include "ReminderFunctions/RemoveReminder.h"

#include "InsulinDeliveryMechanism.h"

void InputEvents();



#include "BasalFunctions/BasalProfiles.h"
#include "Flash.h"


unsigned int reservoirLevel = 0;

void main(void){



    // Stop WDT
    WDT_A_hold(WDT_A_BASE);

    // Basic GPIO initialization
    boardInit();
    //timerInit();
    ledInit();
    buttonInit();
    motorInit();

    clockInit(8000000);   // Config clocks. MCLK=SMCLK=FLL=8MHz; ACLK=REFO=32kHz

    InitRTC();

    // initialize Timer0_A for motors
    TA0CCR0 = 3000;  // set up terminal count
    TA0CTL = TASSEL_2 + ID_3 + MC_1; // configure and start timer

    TA0CCTL0 = CCIE;   // enable timer interrupts
    __enable_interrupt();      // enable interrupts


    // adc stuff
    REFCTL0 &= ~REFMSTR;                      // Reset REFMSTR to hand over control to
                                                // ADC12_A ref control registers
    ADC12CTL0 = ADC12SHT0_8 + ADC12REFON + ADC12ON;
                                                // Internal ref = vcc
    ADC12CTL1 = ADC12SHP;                     // enable sample timer
    ADC12MCTL0 = ADC12SREF_0 + ADC12INCH_3;  // ADC i/p ch A3
    ADC12IE = 0x001;                          // ADC_IFG upon conv result-ADCMEMO

    ADC12CTL0 |= ADC12ENC; // enables conversion



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

		UpdateOperation();



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
		}



		if(c_menuScreen != c_1_menuScreen){
			ClearScreen();
			PrintScreen(reservoirLevel);
			c_1_menuScreen = c_menuScreen;
			f_1_menuChoice = f_menuChoice;

		} else if (f_menuChoice != f_1_menuChoice || updateScreen ){
			PrintScreen(reservoirLevel);
			f_1_menuChoice = f_menuChoice;
			updateScreen = false;

		}


		__no_operation();

		InitMonitoredVariables();

		GPIO_setOutputHighOnPin( MOTOR_ENABLE_PORT, MOTOR_ENABLE_PIN );
		//GPIO_setOutputHighOnPin( MOTOR_COIL_A1_PORT, MOTOR_COIL_A1_PIN );

	    ADC12CTL0 &= ~ADC12SC;
	    ADC12CTL0 |= ADC12SC;                   // Sampling and conversion start

	    DeliverPendingInsulin();

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
}



#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(ADC12_VECTOR))) ADC12ISR (void)
#else
#error Compiler not supported!
#endif
{
  switch(__even_in_range(ADC12IV,34))
  {
  case  0: break;                           // Vector  0:  No interrupt
  case  2: break;                           // Vector  2:  ADC overflow
  case  4: break;                           // Vector  4:  ADC timing overflow
  case  6:                                  // Vector  6:  ADC12IFG0
    reservoirLevel = ((-5.1282 * ADC12MEM0 ) + 20513)/200;                       // Move results, IFG is cleared


   // __bic_SR_register_on_exit(LPM4_bits);   // Exit active CPU
    break;
  case  8: break;                           // Vector  8:  ADC12IFG1
  case 10: break;                           // Vector 10:  ADC12IFG2
  case 12: break;                           // Vector 12:  ADC12IFG3
  case 14: break;                           // Vector 14:  ADC12IFG4
  case 16: break;                           // Vector 16:  ADC12IFG5
  case 18: break;                           // Vector 18:  ADC12IFG6
  case 20: break;                           // Vector 20:  ADC12IFG7
  case 22: break;                           // Vector 22:  ADC12IFG8
  case 24: break;                           // Vector 24:  ADC12IFG9
  case 26: break;                           // Vector 26:  ADC12IFG10
  case 28: break;                           // Vector 28:  ADC12IFG11
  case 30: break;                           // Vector 30:  ADC12IFG12
  case 32: break;                           // Vector 32:  ADC12IFG13
  case 34: break;                           // Vector 34:  ADC12IFG14
  default: break;
  }
}
