
#include "RTC.h"

#include "InsulinOutputCalculator.h" // dependency should be removed


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

bool CalendarIsValid( Calendar calendar ){
	int year = BCDtoInt(calendar.Year);
	if ( BCDtoInt( calendar.Seconds ) >= 60 ) return false;
	if ( BCDtoInt( calendar.Minutes ) >= 60 ) return false;
	if ( BCDtoInt( calendar.Hours ) >= 24 ) return false;

	if ( BCDtoInt( calendar.DayOfMonth ) < 1 || BCDtoInt( calendar.DayOfMonth ) > 31) return false;
	if ( BCDtoInt( calendar.Month ) < 1 || BCDtoInt( calendar.Month ) > 12 ) return false;


	else if ( calendar.Month == 0x02 || calendar.Month == 0x04 || calendar.Month == 0x06 || calendar.Month == 0x09 || calendar.Month == 0x11 ){
		if ( calendar.DayOfMonth > 0x30) return false;

		if (calendar.Month == 0x02 ){
			bool leapYear = IsLeapYear(year);

			if ( leapYear ){
				if ( calendar.DayOfMonth > 0x29 ) return false;
			} else if ( calendar.DayOfMonth > 0x28 ) return false;
		}
	}

	return true;

}

Calendar GetCurrentCalendar(){
	return RTC_A_getCalendarTime( RTC_A_BASE );
}

int GetCurrentHour(){
	//p_currentTime = GetCurrentCalendar();
    return p_currentTime.Hours;
}

int GetCurrentMin(){
	//p_currentTime =  GetCurrentCalendar();
    return p_currentTime.Minutes;

}

int GetCurrentSec(){
    //p_currentTime = GetCurrentCalendar();
    return p_currentTime.Seconds;
}


void GetDay( Calendar *date ){
	int dayNum = BCDtoInt(&date->DayOfMonth);
	int month = BCDtoInt(&date->Month);
	int year = BCDtoInt(&date->Year);
	int dayName;
	int d, m, y, c;

	d = GetdNumber(dayNum);
	m = GetmNumber(month, year);
	y = GetyNumber(year);
	c = GetcNumber(year);

	dayName = (d + m + y + (y/4) + c) % 7;

	date->DayOfWeek = dayName;
}


int GetdNumber(int day){
	int d;

	switch (day){
	case 1:
		d = 1;
		break;
	case 2:
		d = 2;
		break;
	case 3:
		d = 3;
		break;
	case 4:
		d = 4;
		break;
	case 5:
		d = 5;
		break;
	case 6:
		d = 6;
		break;
	case 7:
		d = 0;
		break;
	case 8:
		d = 1;
		break;
	case 9:
		d = 2;
		break;
	case 10:
		d = 3;
		break;
	case 11:
		d = 4;
		break;
	case 12:
		d = 5;
		break;
	case 13:
		d = 6;
		break;
	case 14:
		d = 0;
		break;
	case 15:
		d = 1;
		break;
	case 16:
		d = 2;
		break;
	case 17:
		d = 3;
		break;
	case 18:
		d = 4;
		break;
	case 19:
		d = 5;
		break;
	case 20:
		d = 6;
		break;
	case 21:
		d = 0;
		break;
	case 22:
		d = 1;
		break;
	case 23:
		d = 2;
		break;
	case 24:
		d = 3;
		break;
	case 25:
		d = 4;
		break;
	case 26:
		d = 5;
		break;
	case 27:
		d = 6;
		break;
	case 28:
		d = 0;
		break;
	case 29:
		d = 1;
		break;
	case 30:
		d = 2;
		break;
	case 31:
		d = 3;
		break;

	}
	return d;
}

int GetmNumber(int month, int year){
	int m;
	bool leapYear = IsLeapYear(year);

	switch(month){
	case 1://jan
		if(leapYear == true)
			m = 6;
		else
			m = 0;
		break;
	case 2://feb
		if(leapYear == true)
			m = 2;
		else
			m = 3;
		break;
	case 3://mar
		m = 3;
		break;
	case 4://apr
		m = 6;
		break;
	case 5://may
		m = 1;
		break;
	case 6://jun
		m = 4;
		break;
	case 7://jul
		m = 6;
		break;
	case 8://aug
		m = 2;
		break;
	case 9://sep
		m = 5;
		break;
	case 10://oct
		m = 0;
		break;
	case 11://nov
		m = 3;
		break;
	case 12://dec
		m = 5;
		break;
	}

	return m;
}

int GetyNumber(int year){
	int y;
	int yearMod = year % 100;

	switch (yearMod){
	case 0:
		y = 0;
		break;
	case 1:
		y = 1;
		break;
	case 2:
		y = 2;
		break;
	case 3:
		y = 3;
		break;
	case 4:
		y = 5;
		break;
	case 5:
		y = 6;
		break;
	case 6:
		y = 0;
		break;
	case 7:
		y = 1;
		break;
	case 8:
		y = 3;
		break;
	case 9:
		y = 4;
		break;
	case 10:
		y = 5;
		break;
	case 11:
		y = 6;
		break;
	case 12:
		y = 1;
		break;
	case 13:
		y = 2;
		break;
	case 14:
		y = 3;
		break;
	case 15:
		y = 4;
		break;
	case 16:
		y = 6;
		break;
	case 17:
		y = 0;
		break;
	case 18:
		y = 1;
		break;
	case 19:
		y = 2;
		break;
	case 20:
		y = 4;
		break;
	case 21:
		y = 5;
		break;
	case 22:
		y = 6;
		break;
	case 23:
		y = 0;
		break;
	case 24:
		y = 2;
		break;
	case 25:
		y = 3;
		break;
	case 26:
		y = 4;
		break;
	case 27:
		y = 5;
		break;
	case 28:
		y = 0;
		break;
	case 29:
		y = 1;
		break;
	case 30:
		y = 2;
		break;
	case 31:
		y = 3;
		break;
	case 32:
		y = 5;
		break;
	case 33:
		y = 6;
		break;
	case 34:
		y = 0;
		break;
	case 35:
		y = 1;
		break;
	case 36:
		y = 3;
		break;
	case 37:
		y = 4;
		break;
	case 38:
		y = 5;
		break;
	case 39:
		y = 6;
		break;
	case 40:
		y = 1;
		break;
	case 41:
		y = 2;
		break;
	case 42:
		y = 3;
		break;
	case 43:
		y = 4;
		break;
	case 44:
		y = 6;
		break;
	case 45:
		y = 0;
		break;
	case 46:
		y = 1;
		break;
	case 47:
		y = 2;
		break;
	case 48:
		y = 4;
		break;
	case 49:
		y = 5;
		break;
	case 50:
		y = 6;
		break;
	case 51:
		y = 0;
		break;
	case 52:
		y = 2;
		break;
	case 53:
		y = 3;
		break;
	case 54:
		y = 4;
		break;
	case 55:
		y = 5;
		break;
	case 56:
		y = 0;
		break;
	case 57:
		y = 1;
		break;
	case 58:
		y = 2;
		break;
	case 59:
		y = 3;
		break;
	case 60:
		y = 5;
		break;
	case 61:
		y = 6;
		break;
	case 62:
		y = 0;
		break;
	case 63:
		y = 1;
		break;
	case 64:
		y = 3;
		break;
	case 65:
		y = 4;
		break;
	case 66:
		y = 5;
		break;
	case 67:
		y = 6;
		break;
	case 68:
		y = 1;
		break;
	case 69:
		y = 2;
		break;
	case 70:
		y = 3;
		break;
	case 71:
		y = 4;
		break;
	case 72:
		y = 6;
		break;
	case 73:
		y = 0;
		break;
	case 74:
		y = 1;
		break;
	case 75:
		y = 2;
		break;
	case 76:
		y = 4;
		break;
	case 77:
		y = 5;
		break;
	case 78:
		y = 6;
		break;
	case 79:
		y = 0;
		break;
	case 80:
		y = 2;
		break;
	case 81:
		y = 3;
		break;
	case 82:
		y = 4;
		break;
	case 83:
		y = 5;
		break;
	case 84:
		y = 0;
		break;
	case 85:
		y = 1;
		break;
	case 86:
		y = 2;
		break;
	case 87:
		y = 3;
		break;
	case 88:
		y = 5;
		break;
	case 89:
		y = 6;
		break;
	case 90:
		y = 0;
		break;
	case 91:
		y = 1;
		break;
	case 92:
		y = 3;
		break;
	case 93:
		y = 4;
		break;
	case 94:
		y = 5;
		break;
	case 95:
		y = 6;
		break;
	case 96:
		y = 1;
		break;
	case 97:
		y = 2;
		break;
	case 98:
		y = 3;
		break;
	case 99:
		y = 4;
		break;
	}

	return y;
}

int GetcNumber(int year){
	int c, i;

	i = (year / 100);
	i = i % 4;
	switch (i){
	case 1:
		c = 4;
		break;
	case 2:
		c = 2;
		break;
	case 3:
		c = 0;
		break;
	case 0:
		c = 6;
		break;
	}

	return c;
}

bool IsLeapYear(int year){
	 bool leapYear = false;

	if ( year % 4 == 0) { // If year is divisible by 4
		leapYear = true;

			if ( year % 100 == 0 ){ // Year divisible by 100
				leapYear = false;

				if ( year % 400 == 0 ){ // Year divisible by 400
					leapYear = true;
				}
			}
	}

	return leapYear;
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

			p_currentTime = GetCurrentCalendar();
			InsulinOutputCalculator();
			break;

	case 4:         //RTCEVIFG
			//Interrupts every minute

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
