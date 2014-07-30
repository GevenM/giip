#ifndef DAYOFWEEK_H
#define DAYOFWEEK_H

#include "driverlib.h"
#include <string.h>

extern void GetDay( Calendar *date );
void DateToDay(int date, char *day);
extern bool IsLeapYear(int year);

#endif
