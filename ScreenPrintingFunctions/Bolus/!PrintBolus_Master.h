#ifndef PRINTBOLUS_H
#define PRINTBOLUS_H

#include "Shared.h"
#include "Driverlib.h"
#include "grlib.h"
#include "LcdDriver/Sharp96x96.h"
#include <string.h>


extern void PrintBolus( tContext *context, y_menus f_menuChoice );
extern void PrintBolus_Manage( tContext *context, y_menus f_menuChoice );

extern void PrintBolusAlreadyActive( tContext *context );
extern void PrintBolusCreateNotAllowed( tContext *context );
extern void PrintNoBolusPreset( tContext *context );

#endif