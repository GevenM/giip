#ifndef BOLUSPRESETS_H
#define BOLUSPRESETS_H

#include <stdbool.h>
#include "../Shared.h"
#include "../Flash.h"

#define k_maxNumberOfBolusPresets 8

typedef struct y_bolusSet{
	y_bolus Preset[k_maxNumberOfBolusPresets];
	char NumberOfBolusPresets;
} y_bolusSet;

extern void InitBolusSet();
extern void CopyBolusPreset(y_bolus *fromPreset, y_bolus *toPreset);
extern bool EnteredBolusIsValid(y_bolus *preset);
extern bool PresetCompare( y_bolus *preset1, y_bolus *preset2 );
extern int GetPresetIndex( y_bolus * preset);
extern int GetNumberOfBolusPresets ();

extern int AddPresetToSet(y_bolus *preset);
extern int RemovePresetFromSet(y_bolus *preset);

extern bool BolusPresetCreationAllowed();

extern bool BolusPresetIsActive(y_bolus *preset);
extern bool BolusPresetExists();
extern bool BolusIsActive();

extern void GetPresetName(y_bolusName *name, int index);
void LoadPreset( y_bolus *preset, int index);

extern y_bolus CalculateBolus( y_glucose glucose, y_carbs carbs );
extern bool CalculatedBolusIsValid( y_bolus bolus );
extern bool BolusIsValid( y_bolus *bolus );

#endif
