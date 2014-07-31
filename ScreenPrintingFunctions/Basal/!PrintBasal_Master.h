#ifndef PRINTBASAL_H
#define PRINTBASAL_H

#include "Shared.h"
#include "Driverlib.h"
#include "grlib.h"
#include "LcdDriver/Sharp96x96.h"
#include <string.h>
#include "BasalProfiles.h"

extern void PrintBasal_Manage( tContext *context, y_menus f_menuChoice );
extern void PrintBasNoActive( tContext *context, y_menus f_menuChoice );
extern void PrintBasBothActive( tContext *context, y_menus f_menuChoice );
extern void PrintBasTmpActive( tContext *context, y_menus f_menuChoice );
extern void PrintBasProfActive( tContext *context, y_menus f_menuChoice );
extern void PrintNoBasProf( tContext *context );
extern void PrintBasCreateNotAllowed( tContext *context );
extern void PrintCreateBasProf( tContext *context );

extern void PrintRemoveBasProf_Idle( tContext *context, y_basal *selectedProfile );
extern void PrintRemoveBasProf_Confirm( tContext *context );
extern void PrintRemoveBasProf_Invalid( tContext *context );

extern void PrintStartBasProf_Idle( tContext *context, y_basal *selectedProfile );
extern void PrintStartBasProf_Confirm( tContext *context );
extern void PrintStartBasProf_Invalid( tContext *context );

extern void PrintCreateBasProf_Idle( tContext *context, y_basal *p_profile, bool nameEntered, unsigned char segmentIndex, unsigned char rateIndex, unsigned char *segments );
extern void PrintCreateBasProf_Confirm( tContext *context );
extern void PrintCreateBasProf_Invalid( tContext *context );

extern void PrintStopBas_All( tContext *context );

#endif
