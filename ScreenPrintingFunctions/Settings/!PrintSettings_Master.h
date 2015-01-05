#ifndef PRINTSETTINGS_H
#define PRINTSETTINGS_H

#include "Shared.h"
#include "Driverlib.h"
#include "grlib.h"
#include "LcdDriver/Sharp96x96.h"
#include <string.h>
#include "RTC.h"
#include "ScreenPrintingFunctions/Overlay/!PrintOverlay_Master.h"

extern void PrintSettings( tContext *context, y_menus f_menuChoice );
extern void  PrintSettings_DateTime(tContext *context, Calendar calendar, unsigned char calendarIndex);
extern void PrintSettings_DateTime_NotAllowed(tContext *context);
extern void PrintSettings_MotorTest( tContext *context );
#endif
