#ifndef BASALFUNCTIONS_H
#define BASALFUNCTIONS_H

#include "Shared.h"
#include "MonitoredVariables.h"
#include <stdbool.h>


// Shared F_/f_ variables
extern bool F_createBasalProfile;
extern y_basal F_basalProfileToCreate;

extern bool F_removeBasalProfile;
extern y_basal F_basalProfileToRemove;

extern y_basal f_activeBasal;
extern bool f_basalIsActive;

extern bool F_startBasal;
extern bool F_stopBasal;
extern y_basal F_basalToStart;


// Function Table Functions
extern void CreateBasalProfile();							// Table 7
extern bool BasalProfileCreationCompleted();				// Table 8
extern bool EnteredBasalProfileIsValid(y_basal *profile);	// Table 9
extern void RemoveBasalProfile();							// Table 10
extern bool BasalProfileRemovalCompleted();					// Table 11
extern bool SelectedBasalProfileIsActive(y_basal *profile); // Table 12
extern void ActivateBasalProfile();							// Table 13
extern bool BasalProfileActivationCompleted();				// Table 14
extern bool SelectedBasalProfileIsValid();					// Table 15
extern void DeactivateBasalProfile();			 			// Table 16
extern bool BasalProfileDeactivationCompleted(); 			// Table 17

extern void UpdateBasalProfileSet();						// Table 39
extern void UpdateActiveBasalProfile(); 					// Table 40


// Required Additional Functions
extern void ResetFVariablesBasal();		// Used to reset the event based F_ variables at the end of a program cycle. Simulates an event ending.

#endif
