#include "CreateReminder.h"
#include "MonitoredVariables.h"

bool F_createReminder = false;
y_reminder p_reminder;

void SaveReminder( y_reminder *reminder );
bool ReminderIsValid( y_reminder *reminder );
void CopyReminder ( y_reminder *from, y_reminder *to );

void CreateReminder(){
	if ( c_operation == e_operation_createReminder ){
		switch ( c_remindCreateStatus ){
		case e_opStatus_idle:
			if ( M_reminder ){
				if ( ReminderIsValid( &m_reminder )){
					c_remindCreateStatus = e_opStatus_confirm;
					F_createReminder = true;
					CopyReminder( &m_reminder, &p_reminder );
				} else {
					c_remindCreateStatus = e_opStatus_invalid;
					F_createReminder = false;
				}
			} else {
				F_createReminder = false;
			}
			break;

		case e_opStatus_confirm:
			if ( M_remindCreateResp == e_response_accept ){
				c_remindCreateStatus = e_opStatus_idle;
				F_createReminder = true;
				SaveReminder( &p_reminder );
				CopyReminder( &k_emptyReminder, &p_reminder );

			} else if ( M_remindCreateResp == e_response_retry ){
				c_remindCreateStatus = e_opStatus_idle;
				F_createReminder = false;
				CopyReminder( &k_emptyReminder, &p_reminder );

			} else if ( M_remindCreateResp == e_response_cancel ){
				c_remindCreateStatus = e_opStatus_idle;
				F_createReminder = false;
				CopyReminder( &k_emptyReminder, &p_reminder );

			}
			break;

		case e_opStatus_invalid:
			if ( M_remindCreateResp == e_response_retry ){
				c_remindCreateStatus = e_opStatus_idle;
				F_createReminder = false;
				CopyReminder( &k_emptyReminder, &p_reminder );

			} else if ( M_remindCreateResp == e_response_cancel ){
				c_remindCreateStatus = e_opStatus_idle;
				F_createReminder = false;
				CopyReminder( &k_emptyReminder, &p_reminder );

			} else {
				F_createReminder = false;
			}
			break;
		}

	} else {
		F_createReminder = false;
	}
}


bool ReminderCreationCompleted(){
	if (F_createReminder || M_remindCreateResp == e_response_cancel ){
		F_createReminder = false;
		return true;
	}
	return false;
}

bool ReminderIsValid( y_reminder *reminder ){
	return true;
}

void SaveReminder ( y_reminder *reminder ){
	;
}

void CopyReminder ( y_reminder *from, y_reminder *to ){
	;
}
