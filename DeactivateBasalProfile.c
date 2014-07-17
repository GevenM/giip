#include "DeactivateBasalProfile.h"


bool F_stopBasal; // From NL expression [ Start Basal ]

void StopBasalProfile();

void DeactivateBasalProfile(){
	if ( c_operation == StopBasProf ){
		if ( M_basStopResp == ACCEPT ){
			F_stopBasal = true;
			StopBasalProfile();

		} else if ( M_basStopResp == CANCEL ){
			F_stopBasal = false;
		}

	} else {
		F_stopBasal = false;
	}
}

void StopBasalProfile(){
	CopyProfile( &k_emptyBas, &f_activeBasal );
}

bool BasalProfileDeactivationCompleted(){
	if ( F_stopBasal || M_basStopResp == CANCEL ){
		return true;
	}
	return false;
}
