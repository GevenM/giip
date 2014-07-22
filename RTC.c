
#include "driverlib.h"

Calendar p_currentTime;

void InitRTC(){
	// Sets up the crystal oscillator used for the RTC
	// Select XT1
	GPIO_setAsPeripheralModuleFunctionInputPin(
			GPIO_PORT_P5,
			GPIO_PIN4 + GPIO_PIN5
			);


	//Initialize LFXT1
	UCS_LFXT1Start(UCS_XT1_DRIVE3,
				   UCS_XCAP_3
				   );


	Calendar currentTime;
	//Setup Current Time for Calendar
	currentTime.Seconds    = 0x00;
	currentTime.Minutes    = 0x12;
	currentTime.Hours      = 0x01;
	currentTime.DayOfWeek  = 0x01;
	currentTime.DayOfMonth = 0x14;
	currentTime.Month      = 0x05;
	currentTime.Year       = 0x1988;

	//Initialize Calendar Mode of RTC
	/*
	 * Base Address of the RTC_A_A
	 * Pass in current time, intialized above
	 * Use BCD as Calendar Register Format
	 */
	RTC_A_calendarInit(RTC_A_BASE,
					   currentTime,
					   RTC_A_FORMAT_BCD);


	//Specify an interrupt to assert every minute
	RTC_A_setCalendarEvent(RTC_A_BASE,
						   RTC_A_CALENDAREVENT_MINUTECHANGE);

	//Enable interrupt for RTC Ready Status, which asserts when the RTC
	//Calendar registers are ready to read.
	//Also, enable interrupts for the Calendar alarm and Calendar event.
	RTC_A_clearInterrupt(RTC_A_BASE,
						 RTCRDYIFG + RTCTEVIFG + RTCAIFG);
	RTC_A_enableInterrupt(RTC_A_BASE,
						  RTCRDYIE + RTCTEVIE + RTCAIE);

	//Start RTC Clock
	RTC_A_startClock(RTC_A_BASE);

	 __enable_interrupt();
	/* Interrupts enabled */

}


Calendar GetCurrentCalendar(){
	return RTC_A_getCalendarTime( RTC_A_BASE );
}

int GetCurrentHour(){
	p_currentTime = GetCurrentCalendar();
    return p_currentTime.Hours;
}

int GetCurrentMin(){
	p_currentTime =  GetCurrentCalendar();
    return p_currentTime.Minutes;

}

int GetCurrentSec(){
    p_currentTime = GetCurrentCalendar();
    return p_currentTime.Seconds;
}

uint8_t BCDtoInt( uint8_t bcd ){
	char low, high;

	high = ( bcd >> 4 );
	low = bcd & 0xF;

	return high * 10 + low;
}

uint8_t IntToBCD( uint8_t val ){
	return ((val / 10) << 4) | (val % 10);
}

void SetCalendar( Calendar calendar ){
	RTC_A_calendarInit(RTC_A_BASE, calendar, RTC_A_FORMAT_BCD);
}


#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=RTC_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(RTC_VECTOR)))
#endif
void RTC_A_ISR(void)
{
	switch (__even_in_range(RTCIV, 16)) {
	case 0: break;  //No interrupts
	case 2:         //RTCRDYIFG
			//Toggle P1.0 every second
			GPIO_toggleOutputOnPin(
					GPIO_PORT_P1,
					GPIO_PIN0);
			break;

	case 4:         //RTCEVIFG
			//Interrupts every minute
		 	 p_currentTime = RTC_A_getCalendarTime(RTC_A_BASE);

			//Read out New Time a Minute Later BREAKPOINT HERE
			//newTime = RTC_A_getCalendarTime(RTC_A_BASE);
			break;
	case 6:         //RTCAIFG
			//Interrupts 5:00pm on 5th day of week
			__no_operation();
			break;
	case 8: break;  //RT0PSIFG
	case 10: break; //RT1PSIFG
	case 12: break; //Reserved
	case 14: break; //Reserved
	case 16: break; //Reserved
	default: break;
	}
}
