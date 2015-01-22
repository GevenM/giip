#include "TemporaryBasalFunctions.h"

bool TemporaryBasalActivationCompleted(){
	if ( F_startTmpBasal || M_tmpStartResp == e_response_cancel ){
		//F_activateTemporaryBasal = false;
		return true;
	}

	return false;
}
