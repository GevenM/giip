#include "BasalFunctions.h"

bool f_basalIsActive = false;
y_basal f_activeBasal;

bool F_createBasalProfile = false;
y_basal F_basalProfileToCreate;

bool F_removeBasalProfile = false;
y_basal F_basalProfileToRemove;

bool F_startBasal = false;
y_basal F_basalToStart;

bool F_stopBasal = false;

void ResetFVariablesBasal(){
	CopyProfile(&k_emptyBas, &F_basalProfileToCreate);
	F_createBasalProfile = false;

	CopyProfile(&k_emptyBas, &F_basalProfileToRemove);
	F_removeBasalProfile = false;

	F_startBasal = false;
	CopyProfile( &k_emptyBas, &F_basalToStart );

	F_stopBasal = false;
}
