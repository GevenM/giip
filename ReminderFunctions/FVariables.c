#include "ReminderFunctions.h"
#include "Reminder.h"

bool F_createReminder = false;
y_reminder F_reminderToCreate;
bool F_removeReminder = false;
y_reminder F_reminderToRemove;



void ResetFVariablesReminder(){
	F_createReminder = false;
	F_removeReminder = false;

	CopyReminder( &k_emptyReminder, &F_reminderToCreate );
	CopyReminder( &k_emptyReminder, &F_reminderToRemove );

}
