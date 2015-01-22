#include "BolusFunctions.h"


bool F_createBolusPreset = false;
y_bolus F_bolusPresetToCreate;
bool F_removeBolusPreset = false;
y_bolus F_bolusPresetToRemove;

bool F_startBolus = false;
y_bolus F_bolusToStart;

bool f_bolusInProgress = false;
y_bolus f_activeBolus;


void ResetFVariablesBolus(){
	F_createBolusPreset = false;
	F_removeBolusPreset = false;
	F_startBolus = false;

	CopyPreset( &k_emptyBol, &F_bolusPresetToCreate );
	CopyPreset( &k_emptyBol, &F_bolusPresetToRemove );
	CopyPreset( &k_emptyBol, &F_bolusToStart );
}
