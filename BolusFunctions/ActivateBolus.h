#ifndef ACTIVATEBOLUS_H
#define ACTIVATEBOLUS_H

#include "Shared.h"
#include "MonitoredVariables.h"
#include "BolusPresets.h"

extern void ActivateBolus();
extern bool BolusActivationCompleted();
extern void BolusToActivate(y_bolus *bolus);

#endif
