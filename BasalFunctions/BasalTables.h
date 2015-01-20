#ifndef BASALTABLES_H
#define BASALTABLES_H

#include "Shared.h"
#include "MonitoredVariables.h"
#include "BasalProfiles.h"
#include<stdbool.h>


bool F_createBasalProfile;
y_basal F_basalProfileToCreate;

bool F_removeBasalProfile;
y_basal F_basalProfileToRemove;

y_basal f_activeBasal;
bool f_basalIsActive;

bool F_startBasal;
bool F_stopBasal;
y_basal F_basalToStart;

extern void CreateBasalProfile();
extern bool BasalProfileCreationCompleted();

extern void RemoveBasalProfile();
extern bool BasalProfileRemovalCompleted();

extern void UpdateBasalProfileSet();
extern void ResetFVariablesBasal();


extern void ActivateBasalProfile();
extern bool BasalProfileActivationCompleted();
extern void DeactivateBasalProfile();
extern bool BasalProfileDeactivationCompleted();
extern void UpdateActiveBasalProfile();

#endif
