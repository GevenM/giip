#include "TemporaryBasalFunctions.h"

bool TemporaryBasalDeactivationCompleted(){
	if ( F_stopTmpBasal || M_tmpStopResp == e_response_cancel ){
		return true;
	}
	return false;
}
