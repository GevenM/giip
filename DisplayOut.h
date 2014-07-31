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


//datetime definitions
#define SEC		2
#define MIN		1
#define HR		0
#define MON		4
#define DOM		3
#define YEAR_1	5
#define YEAR_2	6


//reminder definitions
#define NAME 0
#define DATETIME 1
#define FREQ 2
#define MSG 3

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

extern int UnsignedInt_To_ASCII(unsigned int hex, char *ASCII);

//extern tContext g_sContext;
extern tRectangle myRectangleBotMid;
extern tRectangle myRectangleBotRight;
extern tRectangle myRectangleBotLeft;
extern tRectangle myRectangleTopBan;
extern tRectangle myRectangleScreen;


extern bool updateScreen;

extern void InitDisplayContext();

extern void LoadLeftButton(const char * text);
extern void LoadMiddleButton(const char * text);
extern void LoadRightButton(const char * text);

#endif

