#ifndef DISPLAYOUT_H
#define DISPLAYOUT_H

#include "grlib.h"
#include "LcdDriver/Sharp96x96.h"
#include "driverlib.h"
#include "stdlib.h"
#include "hardware.h"
#include "MonitoredVariables.h"
#include "Shared.h"
#include "BasalProfiles.h"
#include "TemporaryBasal.h"

extern void DisplayOut(void);
extern void PrintScreen();

extern bool BasalProfileExists();
extern bool BasalCreationAllowed();

extern bool ScheduleCreationAllowed();
extern bool ScheduleExists();

extern bool TemporaryBasalIsActive();
extern bool BasalIsActive();
extern bool BolusInProgress();

extern void ClearScreen();

extern const char * convertToChar(unsigned int x);

extern tContext g_sContext;
extern tRectangle myRectangleBotMid;
extern tRectangle myRectangleBotRight;
extern tRectangle myRectangleBotLeft;
extern tRectangle myRectangleTopBan;


extern bool updateScreen;


#endif

