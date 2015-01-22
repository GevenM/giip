#include "ReminderFunctions/Reminder.h"
#include <stdlib.h>
#include "flash.h"
#include <string.h>
#include "../RTC.h"

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

void IncrementReminderDay( y_reminder *reminder ){
	int day = BCDtoInt( reminder->Time.DayOfMonth );

	if ( day < 28 ) reminder->Time.DayOfMonth = IntToBCD( ++day );
	else {
		if ( reminder->Time.Month == 0x04 || reminder->Time.Month == 0x06 || reminder->Time.Month == 0x09 || reminder->Time.Month == 0x11 ){
			if ( day < 30 ) reminder->Time.DayOfMonth = IntToBCD( ++day );
			else {
				reminder->Time.DayOfMonth = 1;
				IncrementReminderMonth( reminder );
			}
		} else if ( reminder->Time.Month == 0x02 ){
			int year = BCDtoInt( reminder->Time.Year );
			if ( IsLeapYear(year) ){
				if ( day < 29 ) reminder->Time.DayOfMonth = IntToBCD( ++day );
				else {
						reminder->Time.DayOfMonth = 1;
						IncrementReminderMonth( reminder );
				}
			} else {
				if ( day < 28 ) reminder->Time.DayOfMonth = IntToBCD( ++day );
				else {
					reminder->Time.DayOfMonth = 1;
					IncrementReminderMonth( reminder );
				}
			}
		} else {
			if ( day < 31 ) reminder->Time.DayOfMonth = IntToBCD( ++day );
			else {
				reminder->Time.DayOfMonth = 1;
				IncrementReminderMonth( reminder );
			}
		}

	}
}

void IncrementReminderMonth( y_reminder *reminder ){
	int month = BCDtoInt( reminder->Time.Month );

	if( month < 12 ) {
		month++;
		reminder->Time.Month = IntToBCD( month );

	} else {
		reminder->Time.Month = 1;
		IncrementReminderYear( reminder );
	}
}

void IncrementReminderYear( y_reminder *reminder ){
	int year = BCDtoInt( reminder->Time.Year & 0xFF );

	if( year < 99 ) {
		year++;
		reminder->Time.Year &= 0xff00;
		reminder->Time.Year |= IntToBCD( year );

	} else {
		int century = BCDtoInt( reminder->Time.Year >> 8 );
		century++;
		reminder->Time.Year &= 0x0000;
		reminder->Time.Year |= ( IntToBCD( century ) << 8 );
	}
}

extern bool ReminderNameIsValidAndUnique( y_reminder *reminder ){
	if( strcmp( reminder->Name, "" ) == 0 ){
		return false;
	}

	LoadRemindersFromFlash();

	int i;
	for( i = 0 ; i < reminderSetLocal.NumberOfReminders ; i++ ){
		if ( strcmp( reminderSetLocal.Reminder[i].Name, reminder->Name ) == 0){
			return false;
		}
	}
	return true;
}

extern bool ReminderTimesAreValid( y_reminder *reminder ){
	if( reminder->Time.DayOfWeek == 0 || reminder->Time.DayOfWeek == 6 ){ //if reminder on weekend
		if( reminder->Frequency == e_remindFreq_weekdays ) return false;
	} else { // if reminder on a weekday
		if ( reminder->Frequency == e_remindFreq_weekends ) return false;
	}

	if ( ! ReminderDateTimeValid( reminder )){
		return false;
	}
	return true;
}

extern bool ReminderMessageIsValid( y_reminder *reminder ){
	if( strcmp( reminder->Message, "" ) == 0 ){
		return false;
	}
	return true;
}
