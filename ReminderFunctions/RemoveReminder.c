#include "ReminderFunctions.h"

static y_reminder p_reminder;

void RemoveReminder(){
	if( c_operation == e_operation_removeReminder ){
		switch( c_remindRemStatus ){
		case e_opStatus_idle:
			if( M_reminder ){
				c_remindRemStatus = e_opStatus_confirm;
				//F_removeReminder = false;
				CopyReminder( &m_reminder, &p_reminder );
			} else {
				F_removeReminder = false;
			}
			break;

		case e_opStatus_confirm:
			if ( M_remindRemResp == e_response_accept ){
				c_remindRemStatus = e_opStatus_idle;
				F_removeReminder = true;
				CopyReminder( &p_reminder, &F_reminderToRemove );
			//	RemoveReminderFromSet( &p_reminder );
				CopyReminder( &k_emptyReminder, &p_reminder );

			} else if ( M_remindRemResp == e_response_retry ){
				c_remindRemStatus = e_opStatus_idle;
				//F_removeReminder = false;
				CopyReminder( &k_emptyReminder, &p_reminder );

			} else if ( M_remindRemResp == e_response_cancel ){
				c_remindRemStatus = e_opStatus_idle;
				//F_removeReminder = false;
				CopyReminder( &k_emptyReminder, &p_reminder );

			}
			break;
		default: break;
		}
	} else {
		//F_removeReminder = false;
		CopyReminder( &k_emptyReminder, &p_reminder );
	}
}




