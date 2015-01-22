#include "TemporaryBasalFunctions.h"


void DeactivateTemporaryBasal(){
	if ( c_operation == e_operation_stopTmpBas ){
		if ( M_tmpStopResp == e_response_accept ){
			F_stopTmpBasal = true;

		} else if ( M_tmpStopResp == e_response_cancel ){
			;//F_stopTemporaryBasal = false;
		}

	} else {
		;//F_stopTemporaryBasal = false;
	}
}





