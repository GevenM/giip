#include "Reminder.h"
#include <stdlib.h>
#include "flash.h"
#include <string.h>


// Allocates space on flash for the given variable
#pragma DATA_SECTION(reminderSet, ".mydata3");
#pragma DATA_ALIGN(reminderSet, 512);

// Private variables that store the basal profiles
y_reminderSet reminderSet;
y_reminderSet reminderSetLocal;

void LoadRemindersFromFlash(void);
void SaveRemindersToFlash(void);
bool ReminderDateTimeValid( y_reminder *reminder );

// Add a reminder to the set of reminders.
int AddReminderToSet(y_reminder *reminder){
	LoadRemindersFromFlash();

	// Check if max number of reminders has been stored
	if ( ReminderCreationAllowed() ){

		// create an index variable for where to store the next reminder and increment number of reminders.
		char reminderIndex = reminderSetLocal.NumberOfReminders;
		reminderSetLocal.NumberOfReminders++;

		// Copy the reminder to the set
		CopyReminder( reminder, &reminderSetLocal.Reminder[ reminderIndex ] );

		SaveRemindersToFlash();
		return 1;
	}

	return -1;
}

bool ReminderCreationAllowed(){
	LoadRemindersFromFlash();

	if ( reminderSetLocal.NumberOfReminders < k_maxNumberOfReminders ){
		return true;
	}

	return false;
}

bool ReminderRemovalAllowed(){
	LoadRemindersFromFlash();

	if ( reminderSetLocal.NumberOfReminders > 0 ){
		return true;
	}

	return false;
}

int RemoveReminderFromSet( y_reminder *reminder ){
	LoadRemindersFromFlash();

	// Create index to hold the location of reminder to remove
	int reminderIndex = GetReminderIndex( reminder );
	if ( reminderIndex == -1 ) return -1; //not in set

	// If the reminder to remove is the last one, simply decrement the number of reminders
	if( reminderIndex == reminderSetLocal.NumberOfReminders - 1 ){
		reminderSetLocal.NumberOfReminders--;
		SaveRemindersToFlash();
		return 1;
	}

	// If it's a reminder that is not the last, move all the reminders after the one to remove up one place.
	if ( reminderIndex < reminderSetLocal.NumberOfReminders - 1 ){
		int i;
		for (i = reminderIndex; i < reminderSetLocal.NumberOfReminders - 1 ; i++){
			CopyReminder( &reminderSetLocal.Reminder[ i + 1 ], &reminderSetLocal.Reminder[ i ] );
		}
		reminderSetLocal.NumberOfReminders--;
		SaveRemindersToFlash();
		return 1;
	}

	return -1;
}

int GetReminderIndex( y_reminder *reminder ){
	LoadRemindersFromFlash();

	int i = 0;
	while ( strcmp( reminder->Name, reminderSetLocal.Reminder[ i ].Name ) && i < k_maxNumberOfReminders ){
		i++;
	}

	if ( i == k_maxNumberOfReminders ) return -1;

	return i;
}

bool ReminderIsValid( y_reminder *reminder ){
	if( GetReminderIndex( reminder ) == -1 ){
		if( strcmp( reminder->Name, "" ) != 0 ){
			if( strcmp( reminder->Message, "" ) != 0 ){
				if ( ReminderDateTimeValid( reminder )){
					return true;
				}
			}
		}
	}
	return true;

}

bool ReminderDateTimeValid( y_reminder *reminder ){
	return true; // NEED TO FILL IN THIS FUNCTION
}

void CopyReminder ( y_reminder *from, y_reminder *to ){
	*to = *from;
}


void SaveRemindersToFlash(void)
{
  flashEraseSegment((unsigned long)&reminderSet);

  UnlockFlash();
  reminderSet = reminderSetLocal;
  LockFlash();
}


void LoadRemindersFromFlash(void)
{
  reminderSetLocal = reminderSet;
}

void InitReminderSet(){
	reminderSetLocal.NumberOfReminders = 0;
	SaveRemindersToFlash();
}


int GetNumberOfReminders(){
	LoadRemindersFromFlash();

	return reminderSetLocal.NumberOfReminders;
}

y_reminder GetReminderFromIndex( int index ){
	LoadRemindersFromFlash();
	return reminderSetLocal.Reminder[ index ];
}

void GetReminderName( y_remindName *name, int index ){
	LoadRemindersFromFlash();
	strncpy( *name, reminderSetLocal.Reminder[ index ].Name, k_remindNameLength );
}
