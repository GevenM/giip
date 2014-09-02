#include "RemoveReminder.h"

static bool F_removeReminder = false;
static y_reminder p_reminder;

void RemoveReminder(){
	if( c_operation == e_operation_removeReminder ){
		switch( c_remindRemStatus ){
		case e_opStatus_idle:
			if( M_reminder ){
				c_remindRemStatus = e_opStatus_confirm;
				F_removeReminder = false;
				CopyReminder( &m_reminder, &p_reminder );
			} else {
				F_removeReminder = false;
			}
			break;

		case e_opStatus_confirm:
			if ( M_remindRemResp == e_response_accept ){
				c_remindRemStatus = e_opStatus_idle;
				F_removeReminder = true;
				RemoveReminderFromSet( &p_reminder );
				CopyReminder( &k_emptyReminder, &p_reminder );

			} else if ( M_remindRemResp == e_response_retry ){
				c_remindRemStatus = e_opStatus_idle;
				F_removeReminder = false;
				CopyReminder( &k_emptyReminder, &p_reminder );

			} else if ( M_remindRemResp == e_response_cancel ){
				c_remindRemStatus = e_opStatus_idle;
				F_removeReminder = false;
				CopyReminder( &k_emptyReminder, &p_reminder );

			}
			break;
		default: break;
		}
	} else {
		F_removeReminder = false;
		CopyReminder( &k_emptyReminder, &p_reminder );
	}
}

bool ReminderRemovalCompleted(){
	if (F_removeReminder || M_remindRemResp == e_response_cancel ){
		F_removeReminder = false;
		return true;
	}
	return false;
}


