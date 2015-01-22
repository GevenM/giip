#include "ReminderFunctions.h"

bool ReminderCreationCompleted(){
	if (F_createReminder || M_remindCreateResp == e_response_cancel ){
	//	F_createReminder = false;
		return true;
	}
	return false;
}
