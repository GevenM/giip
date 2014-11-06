#ifndef PRINTOVERLAY_MASTER_H
#define PRINTOVERLAY_MASTER_H

#include "Shared.h"
#include "Driverlib.h"
#include "grlib.h"
#include "LcdDriver/Sharp96x96.h"
#include <string.h>
#include "RTC.h"

extern void LoadBanner( tContext *context , unsigned int reservoirLevel);
extern void LoadLeftButton( tContext *context, const char * text );
extern void LoadMiddleButton( tContext *context, const char * text );
extern void LoadRightButton( tContext *context, const char * text );

void ClearRightButton( tContext *context );
void ClearScreenContent( tContext *context );

#endif
