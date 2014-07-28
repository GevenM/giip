#include "DeactivateBasalProfile.h"

#include "Shared.h"
#include "MonitoredVariables.h"
#include "BasalProfiles.h"

bool F_stopBasal; // From NL expression [ Start Basal ]

void StopBasalProfile();

void DeactivateBasalProfile(){
	if ( c_operation == e_operation_stopBasProf ){
		if ( M_basStopResp == e_response_accept ){
			F_stopBasal = true;
			StopBasalProfile();

		} else if ( M_basStopResp == e_response_cancel ){
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
	if ( F_stopBasal || M_basStopResp == e_response_cancel ){
		return true;
	}
	return false;
}
