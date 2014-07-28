#ifndef REMINDER_H
#define REMINDER_H

#include "TypesAndConstants.h"
#include "Flash.h"

#define k_maxNumberOfReminders 6  // at message length of 63, name length of 13 and, date/time size of 8, 6 profiles fit on 512bytes of flash.

typedef struct y_reminderSet{
	y_reminder Reminder[ k_maxNumberOfReminders ];
	char NumberOfReminders; // Current number of reminders in set
} y_reminderSet;


extern int AddReminderToSet( );
extern int RemoveReminderFromSet( );

extern bool ReminderIsValid( y_reminder *reminder );
extern void CopyReminder ( y_reminder *from, y_reminder *to );



#endif
