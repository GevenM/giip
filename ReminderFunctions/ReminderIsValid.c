#include "ReminderFunctions.h"
#include "Reminder.h"

bool ReminderIsValid( y_reminder *reminder ){
	if ( !ReminderNameIsValidAndUnique( reminder ) ){
		return false;
	}

	if ( !ReminderMessageIsValid( reminder ) ){
		return false;
	}

	if ( !ReminderTimesAreValid( reminder ) ){
		return false;
	}
	return true;
}
