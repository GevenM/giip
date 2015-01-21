#include "BasalFunctions.h"

void DeactivateBasalProfile(){
	if ( c_operation == e_operation_stopBasProf ){
		if ( M_basStopResp == e_response_accept ){
			F_stopBasal = true;

		} else if ( M_basStopResp == e_response_cancel ){
		;	//F_stopBasal = false;
		}
	} else {
		;//F_stopBasal = false;
	}
}

