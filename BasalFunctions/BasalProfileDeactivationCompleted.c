#include "BasalTables.h"

bool BasalProfileDeactivationCompleted(){
	if ( F_stopBasal || M_basStopResp == e_response_cancel ){
		return true;
	}
	return false;
}
