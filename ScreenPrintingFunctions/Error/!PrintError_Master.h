#ifndef PRINTERROR_MASTER_H
#define PRINTERROR_MASTER_H

#include "Shared.h"
#include "Driverlib.h"
#include "grlib.h"
#include "LcdDriver/Sharp96x96.h"
#include <string.h>
#include "ScreenPrintingFunctions/Overlay/!PrintOverlay_Master.h"

extern void PrintError( tContext *context );

#endif
