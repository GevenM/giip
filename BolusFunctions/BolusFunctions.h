#ifndef BOLUSFUNCTIONS_H
#define BOLUSFUNCTION_H

#include <stdbool.h>
#include "Shared.h"
#include "MonitoredVariables.h"


// Shared F/f variables
extern bool F_createBolusPreset;
extern y_bolus F_bolusPresetToCreate;
extern bool F_removeBolusPreset;
extern y_bolus F_bolusPresetToRemove;

extern bool F_startBolus;
extern y_bolus F_bolusToStart;

extern bool f_bolusInProgress;
extern y_bolus f_activeBolus;



// Functions from Function Tables
extern void CreateBolusPreset();								// Table 23
extern bool BolusPresetCreationCompleted(); 					// Table 24
extern bool BolusIsValid( y_bolus *preset );					// Table 25, 32, 33

extern void RemoveBolusPreset(); 								// Table 26
extern bool BolusPresetRemovalCompleted(); 						// Table 27
extern void ActivateBolus();	// Table 28
extern bool BolusActivationCompleted();							// Table 29


extern y_bolus CalculatedBolus( y_glucose *glucose, y_carbs *carbs ); // Table 30
extern bool CalculatedBolusIsValid( y_glucose *glucose, y_carbs *carbs ); // Table 31

extern void UpdateBolusPresetSet(); 							// Table 42
extern void UpdateActiveBolus(); 								// Table 43


// Other functions
extern void ResetFVariablesBolus();

extern y_bolus GetBolusToCreate();	// used by ui code to display the bolus preset to create.
extern y_bolus GetBolusToActivate(); // used by ui to display bolus to activate.

#endif
