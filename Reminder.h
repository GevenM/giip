#ifndef REMINDER_H
#define REMINDER_H

#include "TypesAndConstants.h"

extern void AddReminderToSet( );
extern void RemoveReminderFromSet( );


extern bool ReminderIsValid( y_reminder *reminder );
extern void CopyReminder ( y_reminder *from, y_reminder *to );



#endif
