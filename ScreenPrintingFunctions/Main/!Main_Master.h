#ifndef MAIN_MASTER_H
#define MAIN_MASTER_H

#include "Shared.h"
#include "Driverlib.h"
#include "grlib.h"
#include "LcdDriver/Sharp96x96.h"
#include <string.h>

extern void PrintIdle( tContext *context );
extern void PrintMainMenu( tContext *context, y_menus f_menuChoice );

#endif
