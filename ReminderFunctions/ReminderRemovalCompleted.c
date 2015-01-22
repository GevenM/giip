#include"ReminderFunctions.h"

bool ReminderRemovalCompleted(){
	if (F_removeReminder || M_remindRemResp == e_response_cancel ){
		//F_removeReminder = false;
		return true;
	}
	return false;
}
