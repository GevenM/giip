#include "BolusFunctions.h"

bool BolusPresetRemovalCompleted(){
	if (F_removeBolusPreset || M_bolRemResp == e_response_cancel){
	//	F_removeBolusPreset = false;
		return true;
	}

	return false;
}
