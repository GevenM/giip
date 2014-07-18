#ifndef BOLUSPRESETS_H
#define BOLUSPRESETS_H

#include "Flash.h"
#include <stdbool.h>


#define k_bolusNameLength 12
#define k_maxNumberOfBolusPresets 8

typedef int y_insulinValue;
typedef char y_bolusName[k_bolusNameLength+1];

typedef struct bolPreset{
	y_bolusName Name;
	y_insulinValue Amount;
} y_bolus;

typedef struct y_bolusSet{
	y_bolus Preset[k_maxNumberOfBolusPresets];
	char NumberOfBolusProfiles;
} y_bolusSet;

extern void CopyBolusPreset(y_bolus *fromPreset, y_bolus *toPreset);
extern bool EnteredBolusIsValid(y_bolus *preset);

#endif
