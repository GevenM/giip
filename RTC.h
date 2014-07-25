#ifndef RTC_H
#define RTC_H

#include "driverlib.h"

extern void InitRTC();

extern Calendar GetCurrentCalendar();
extern int GetCurrentHour();
extern int GetCurrentMin();
extern int GetCurrentSec();
extern uint8_t BCDtoInt( uint8_t bcd );
extern uint8_t IntToBCD( uint8_t val );
extern void SetCalendar( Calendar calendar );
extern bool CalendarIsValid( Calendar calendar );


#endif
