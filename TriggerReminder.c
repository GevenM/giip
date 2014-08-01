#include "Reminder.h"
#include "RTC.h"
#include "Shared.h"
#include <string.h>
#include <stdlib.h>

static y_reminder p_pendingReminder;


void TriggerReminder(){

	// Check if there's any reminder that is due
	// Check all reminders to see if the date/time is the same as current time or a previous time.

	// Get the current date and time
	y_dateTime currentCalendar = GetCurrentCalendar();


	// Variable to hold each of the reminders
	y_reminder *reminder;
	reminder = ( y_reminder * ) malloc( sizeof ( y_reminder ));

	// Cycle through all reminders to see if the date/time is the same as current time or a previous time.
	// if there is one that should be activated,
	int numberOfReminders = GetNumberOfReminders();
	int i;
	for ( i = 0 ; i < numberOfReminders ; i++ ){
		(*reminder) = GetReminderFromIndex( i );

		if ( ((*reminder).Time.Year == currentCalendar.Year &&
				(*reminder).Time.Month == currentCalendar.Month &&
				(*reminder).Time.DayOfMonth == currentCalendar.DayOfMonth &&
				(*reminder).Time.Hours == currentCalendar.Hours &&
				(*reminder).Time.Minutes == currentCalendar.Minutes ) ||

				(*reminder).Time.Year < currentCalendar.Year ||
				((*reminder).Time.Year == currentCalendar.Year && (*reminder).Time.Month < currentCalendar.Month ) ||
				((*reminder).Time.Year == currentCalendar.Year && (*reminder).Time.Month == currentCalendar.Month && (*reminder).Time.DayOfMonth < currentCalendar.DayOfMonth ) ||
				((*reminder).Time.Year == currentCalendar.Year && (*reminder).Time.Month == currentCalendar.Month && (*reminder).Time.DayOfMonth == currentCalendar.DayOfMonth && (*reminder).Time.Hours < currentCalendar.Hours ) ||
				((*reminder).Time.Year == currentCalendar.Year && (*reminder).Time.Month == currentCalendar.Month && (*reminder).Time.DayOfMonth == currentCalendar.DayOfMonth && (*reminder).Time.Hours == currentCalendar.Hours && (*reminder).Time.Minutes < currentCalendar.Minutes )
			){

			p_pendingReminder = *reminder;
			break;
		}
	}


	free( reminder );
	//
}

bool ReminderIsPending(){
	// if pending reminder name is empty
	if( strcmp( p_pendingReminder.Name, k_emptyReminder.Name ) == 0 ){
		return false;
	}
	return true;
}

y_reminder GetPendingReminder(){
	return p_pendingReminder;
}

void PendingReminderAckHandler(){
	int i;
	switch ( p_pendingReminder.Frequency ){
	case e_remindFreq_oneTime:
		RemoveReminderFromSet( &p_pendingReminder );
		p_pendingReminder = k_emptyReminder;
		break;

	case e_remindFreq_daily:
		// Need to set the next time it's activated to the next day.
		RemoveReminderFromSet( &p_pendingReminder );
		IncrementReminderDay( &p_pendingReminder );
		//GetDay( &p_pendingReminder ); not important
		AddReminderToSet( &p_pendingReminder );
		p_pendingReminder = k_emptyReminder;
		break;


	case e_remindFreq_weekly:

		RemoveReminderFromSet( &p_pendingReminder );
		for( i = 1; i < 7 ; i++ ){ // increment 7 times to set for same time next week.
			IncrementReminderDay( &p_pendingReminder );
		}
		AddReminderToSet( &p_pendingReminder );
		p_pendingReminder = k_emptyReminder;
		break;

	case e_remindFreq_weekdays:
		RemoveReminderFromSet( &p_pendingReminder );
		if( p_pendingReminder.Time.DayOfWeek == 5 ){ // if reminder is for friday, increment to monday
			IncrementReminderDay( &p_pendingReminder );
			IncrementReminderDay( &p_pendingReminder );
			IncrementReminderDay( &p_pendingReminder );
		} else {
			IncrementReminderDay( &p_pendingReminder );
		}
		AddReminderToSet( &p_pendingReminder );
		p_pendingReminder = k_emptyReminder;
		break;

	case e_remindFreq_weekends:
		RemoveReminderFromSet( &p_pendingReminder );
		if( p_pendingReminder.Time.DayOfWeek == 0 ){// if reminder is for sunday
			for( i = 1; i < 7 ; i++ ){ // increment until it's saturday
				IncrementReminderDay( &p_pendingReminder );
			}
		} else {
			IncrementReminderDay( &p_pendingReminder );
		}
		AddReminderToSet( &p_pendingReminder );
		p_pendingReminder = k_emptyReminder;
		break;

	default: break;
	}

	TriggerReminder(); // Check if there's another reminder that needs to be shown.
}
