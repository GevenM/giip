#include "BolusFunctions.h"

bool BolusPresetCreationCompleted(){
	if ( F_createBolusPreset || M_bolCreateResp == e_response_cancel ){
		//F_createBolusPreset = false;
		return true;
	}

	return false;
}
