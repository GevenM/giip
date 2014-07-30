#ifndef PRINTBASAL_H
#define PRINTBASAL_H

#include "Shared.h"
#include "Driverlib.h"
#include "grlib.h"
#include "LcdDriver/Sharp96x96.h"
#include <string.h>

extern void PrintBasal_Manage( tContext *context, y_menus f_menuChoice );
extern void PrintBasNoActive(tContext *context, y_menus f_menuChoice);
extern void PrintBasBothActive(tContext *context, y_menus f_menuChoice);
extern void PrintBasTmpActive(tContext *context, y_menus f_menuChoice);
extern void PrintBasProfActive(tContext *context, y_menus f_menuChoice);
extern void PrintNoBasProf(tContext *context);
extern void PrintBasCreateNotAllowed(tContext *context);
extern void PrintCreateBasProf(tContext *context);


#endif
