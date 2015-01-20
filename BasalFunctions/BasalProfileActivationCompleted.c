#include"BasalTables.h"

bool BasalProfileActivationCompleted(){
	if ( F_startBasal || M_basStartResp == e_response_cancel ){
		return true;
	}
	return false;
}
