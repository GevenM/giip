#ifndef PRINTREMINDER_H
#define PRINTREMINDER_H

#include "Shared.h"
#include "Driverlib.h"
#include "grlib.h"
#include "LcdDriver/Sharp96x96.h"
#include <string.h>

extern void PrintNoRemind(tContext *context);
extern void PrintRemindCreateNotAllowed(tContext *context);
extern void PrintReminder(tContext *context, y_menus f_menuChoice);

#endif
