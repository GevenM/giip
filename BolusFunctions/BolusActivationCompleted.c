#include "BolusFunctions.h"


bool BolusActivationCompleted(){
	if ( F_startBolus || M_bolStartResp == e_response_cancel ){
		return true;
	}
	return false;
}
