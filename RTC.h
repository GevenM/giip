#ifndef RTC_H
#define RTC_H

extern void InitRTC();

extern Calendar GetCurrentCalendar();
extern int GetCurrentHour();
extern int GetCurrentMin();
extern int GetCurrentSec();
extern int BCDtoInt( int bcd );
extern int IntToBCD( int val );
extern void SetCalendar( Calendar calendar );

#endif
