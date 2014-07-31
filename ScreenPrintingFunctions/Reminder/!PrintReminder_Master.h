#ifndef PRINTREMINDER_H
#define PRINTREMINDER_H

#include "Shared.h"
#include "Driverlib.h"
#include "grlib.h"
#include "LcdDriver/Sharp96x96.h"
#include <string.h>
#include "RTC.h"
#include "ScreenPrintingFunctions/Overlay/!PrintOverlay_Master.h"

extern void PrintNoRemind(tContext *context);
extern void PrintRemindCreateNotAllowed(tContext *context);
extern void PrintReminder(tContext *context, y_menus f_menuChoice);
extern void PrintCreateReminder_Idle(tContext *context, char remindEntryIndex, y_reminder reminder, char remindSubIndex);
extern void PrintCreateReminder_Confirm(tContext *context);
extern void PrintCreateReminder_Invalid(tContext *context);
extern void PrintRemoveReminder_Idle(tContext *context);
extern void PrintRemoveReminder_Confirm(tContext *context);

#endif
