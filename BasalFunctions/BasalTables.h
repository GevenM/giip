#ifndef BASALTABLES_H
#define BASALTABLES_H

#include "Shared.h"
#include "MonitoredVariables.h"
#include "BasalProfiles.h"
#include<stdbool.h>


extern bool F_createBasalProfile;
extern y_basal F_basalProfileToCreate;

extern bool F_removeBasalProfile;
extern y_basal F_basalProfileToRemove;

extern y_basal f_activeBasal;
extern bool f_basalIsActive;

extern bool F_startBasal;
extern bool F_stopBasal;
extern y_basal F_basalToStart;

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
