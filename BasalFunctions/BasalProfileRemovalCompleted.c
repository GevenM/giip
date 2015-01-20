#include "BasalTables.h"

bool BasalProfileRemovalCompleted(){
	if (F_removeBasalProfile || M_basRemResp == e_response_cancel){
		//F_removeBasalProfile = false;
		return true;
	}
	return false;
}
