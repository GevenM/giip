#include "BasalTables.h"

bool BasalProfileCreationCompleted(){
	if (F_createBasalProfile || M_basCreateResp == e_response_cancel ){
		//F_createBasalProfile = false;
		return true;
	}

	return false;
}
