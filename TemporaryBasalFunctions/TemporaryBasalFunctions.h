#ifndef TEMPORARYBASALFUNCTIONS_H
#define TEMPORARYBASALFUNCTIONS_H

#include "Shared.h"
#include "MonitoredVariables.h"
#include <stdbool.h>

// F_/f_ variables
extern bool F_startTmpBasal;
extern y_tmpBasal F_tmpBasalToStart;
extern y_tmpBasal f_activeTmpBasal;
extern bool f_tmpBasalIsActive;
extern bool F_stopTmpBasal;


// Functions from function tables
extern void ActivateTemporaryBasal();						// Table 18
extern bool TemporaryBasalActivationCompleted();			// Table 19
extern bool TemporaryBasalIsValid( y_tmpBasal *profile );	// Table 20
extern void DeactivateTemporaryBasal();						// Table 21
extern bool TemporaryBasalDeactivationCompleted();			// Table 22
extern void UpdateActiveTemporaryBasal();					// Table 41


// Other functions
extern void ResetFVariablesTemporaryBasal();
extern void CopyTmpBasal(y_tmpBasal *fromTmpBasal, y_tmpBasal *toTmpBasal);
extern bool TmpBasalCompare(y_tmpBasal *profile1, y_tmpBasal *profile2);
extern bool TemporaryBasalIsActive();
extern bool TemporaryRateOutOfBound( y_tmpBasal *profile );

#endif
