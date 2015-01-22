#include "ReminderFunctions.h"
#include "Reminder.h"

void UpdateReminders(){
	if( c_pwrStatus == e_pwrStatus_ready ){
		if ( F_createReminder ){
			AddReminderToSet( &F_reminderToCreate );
		} else if ( F_removeReminder ){
			RemoveReminderFromSet( &F_reminderToRemove );
		} else {
			;//NC
		}
	} else {
		; //NC
	}
}
