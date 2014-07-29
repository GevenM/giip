#ifndef RTC_H
#define RTC_H

#include "driverlib.h"

extern void InitRTC();

extern Calendar GetCurrentCalendar();
extern int GetCurrentHour();
extern int GetCurrentMin();
extern int GetCurrentSec();
extern int GetCurrentDayOfWeek();
extern uint8_t BCDtoInt( uint8_t bcd );
extern uint8_t IntToBCD( uint8_t val );
extern void SetCalendar( Calendar calendar );
extern bool CalendarIsValid( Calendar calendar );
extern void GetDay( Calendar *date );
extern int GetdNumber(int day);
extern int GetmNumber(int month, int year);
extern int GetyNumber(int year);
extern int GetcNumber(int year);
extern bool IsLeapYear(int year);


#endif
