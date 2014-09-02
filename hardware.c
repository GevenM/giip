
#include "msp430.h"

#include "inc/hw_memmap.h"
#include "driverlib/MSP430F5xx_6xx/gpio.h"
#include "driverlib/MSP430F5xx_6xx/wdt_a.h"
#include "driverlib/MSP430F5xx_6xx/ucs.h"
#include "driverlib/MSP430F5xx_6xx/pmm.h"

#include "hardware.h"
#include "driverlib.h"

bool i_1_leftSelBtn = false;
bool i_1_middleSelBtn = false;
bool i_1_rightSelBtn = false ;
bool i_1_leftDirBtn = false;
bool i_1_rightDirBtn = false;
bool i_1_upDirBtn = false;
bool i_1_downDirBtn = false;

bool I_leftSelBtn = false;
bool I_middleSelBtn = false;
bool I_rightSelBtn = false;
bool I_rightDirBtn = false;
bool I_leftDirBtn = false;
bool I_upDirBtn = false;
bool I_downDirBtn = false;

/* Configures the system clocks:
 * MCLK = SMCLK = DCO/FLL = mclkFreq (expected to be expressed in Hz)
 * ACLK = FLLref = REFO=32kHz
 *
 * XT2 is not configured here.  Instead, the USB API automatically starts XT2
 * when beginning USB communication, and optionally disables it during USB
 * suspend.  It's left running after the USB host is disconnected, at which
 * point you're free to disable it.  You need to configure the XT2 frequency
 * in the Descriptor Tool (currently set to 4MHz in this example, since that's
 * what the Launchpad uses).  See the Programmer's Guide for more information.
 */
void clockInit(unsigned long mclkFreq){

    UCS_clockSignalInit(
    	   UCS_FLLREF,
    	   UCS_REFOCLK_SELECT,
    	   UCS_CLOCK_DIVIDER_1);

    	UCS_clockSignalInit(
    	   UCS_ACLK,
    	   UCS_REFOCLK_SELECT,
    	   UCS_CLOCK_DIVIDER_1);

        UCS_initFLLSettle(
            mclkFreq/1000,
            mclkFreq/32768);
            //use REFO for FLL and ACLK
            UCSCTL3 = (UCSCTL3 & ~(SELREF_7)) | (SELREF__REFOCLK);
            UCSCTL4 = (UCSCTL4 & ~(SELA_7)) | (SELA__REFOCLK);
}

void boardInit(){
	/*
	 * This function drives all the I/O's as output-low, to avoid floating inputs
	 * (which cause extra power to be consumed).  This setting is compatible with
	 * TI FET target boards, the F5529 Launchpad, and F5529 Experimenters Board;
	 * but may not be compatible with custom hardware, which may have components
	 * attached to the I/Os that could be affected by these settings.  So if using
	 * other boards, this function may need to be modified.
	 */

	#ifdef __MSP430_HAS_PORT1_R__
		GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_ALL);
		GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_ALL);
	#endif

	#ifdef __MSP430_HAS_PORT2_R__
		GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_ALL);
		GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_ALL);
	#endif

	#ifdef __MSP430_HAS_PORT3_R__
		GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_ALL);
		GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_ALL);
	#endif

	#ifdef __MSP430_HAS_PORT4_R__
		GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_ALL);
		GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_ALL);
	#endif

	#ifdef __MSP430_HAS_PORT5_R__
		GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_ALL);
		GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_ALL);
	#endif

	#ifdef __MSP430_HAS_PORT6_R__
		GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_ALL);
		GPIO_setAsOutputPin(GPIO_PORT_P6, GPIO_ALL);
	#endif

	#ifdef __MSP430_HAS_PORT7_R__
		GPIO_setOutputLowOnPin(GPIO_PORT_P7, GPIO_ALL);
		GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_ALL);
	#endif

	#ifdef __MSP430_HAS_PORT8_R__
		GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_ALL);
		GPIO_setAsOutputPin(GPIO_PORT_P8, GPIO_ALL);
	#endif

	#ifdef __MSP430_HAS_PORT9_R__
		GPIO_setOutputLowOnPin(GPIO_PORT_P9, GPIO_ALL);
		GPIO_setAsOutputPin(GPIO_PORT_P9, GPIO_ALL);
	#endif

	#ifdef __MSP430_HAS_PORTJ_R__
		GPIO_setOutputLowOnPin(GPIO_PORT_PJ, GPIO_ALL);
		GPIO_setAsOutputPin(GPIO_PORT_PJ, GPIO_ALL);
	#endif
}

void ledInit(){
    //Set P1.0 to output direction
    GPIO_setAsOutputPin( GPIO_PORT_P1, GPIO_PIN0 );
}

void timerInit(){
    TIMER_A_configureUpMode(TIMER_A1_BASE,TIMER_A_CLOCKSOURCE_SMCLK,
                        TIMER_A_CLOCKSOURCE_DIVIDER_64,65535-1,
                        TIMER_A_TAIE_INTERRUPT_ENABLE,
                        TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE, TIMER_A_SKIP_CLEAR);

    TIMER_A_initCompare(TIMER_A1_BASE,
    					TIMER_A_CAPTURECOMPARE_REGISTER_1,
    					TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE,
    					TIMER_A_OUTPUTMODE_OUTBITVALUE,
    					62500 );

    TIMER_A_startCounter(TIMER_A1_BASE,
    		TIMER_A_UP_MODE
    					);
}

void buttonInit(){
	GPIO_setAsInputPinWithPullUpresistor( LEFT_SEL_BTN_PORT, LEFT_SEL_BTN_PIN );
	GPIO_setAsInputPinWithPullUpresistor( MIDDLE_SEL_BTN_PORT, MIDDLE_SEL_BTN_PIN );
	GPIO_setAsInputPinWithPullUpresistor( RIGHT_SEL_BTN_PORT, RIGHT_SEL_BTN_PIN );
	GPIO_setAsInputPinWithPullUpresistor( LEFT_DIR_BTN_PORT, LEFT_DIR_BTN_PIN );
	GPIO_setAsInputPinWithPullUpresistor( RIGHT_DIR_BTN_PORT, RIGHT_DIR_BTN_PIN );
	GPIO_setAsInputPinWithPullUpresistor( UP_DIR_BTN_PORT, UP_DIR_BTN_PIN );
	GPIO_setAsInputPinWithPullUpresistor( DOWN_DIR_BTN_PORT, DOWN_DIR_BTN_PIN );

	//  P1DIR &= ~BIT4;
	//  P1DIR &= ~BIT3;
	//  P1DIR &= ~BIT2;
	// P3DIR &= ~BIT7;
	 // P4DIR &= ~BIT3;
	 // P4DIR &= ~BIT0;
	 // P8DIR &= ~BIT2;
}
