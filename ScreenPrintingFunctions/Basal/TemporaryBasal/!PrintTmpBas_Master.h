#ifndef PRINTTMPBAS_H
#define PRINTTMPBAS_H

#include "Shared.h"
#include "Driverlib.h"
#include "grlib.h"
#include "LcdDriver/Sharp96x96.h"
#include <string.h>
#include "ScreenPrintingFunctions/Overlay/!PrintOverlay_Master.h"

extern void PrintStartTmpBas_Confirm(tContext *context, y_tmpBasal tmpBas);
extern void PrintStartTmpBas_Invalid(tContext *context);
extern void PrintStartTmpBas_Idle(tContext *context, bool tmpBasal_DurationEntered, y_tmpBasal tmpBas);
extern void PrintStopTmpBas_All(tContext *context);

#endif
