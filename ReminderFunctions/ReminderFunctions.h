#ifndef REMINDERFUNCTIONS_H
#define REMINDERFUNCTIONS_H

#include <stdbool.h>
#include "Shared.h"
#include "MonitoredVariables.h"


// Shared F/f variables
extern bool F_createReminder;
extern y_reminder F_reminderToCreate;

extern bool F_removeReminder;
extern y_reminder F_reminderToRemove;


// Functions from Function Tables
extern void CreateReminder();				// Table 34
extern bool ReminderCreationCompleted();	// Table 35
extern bool ReminderIsValid();				// Table 36

extern void RemoveReminder();				// Table 37
extern bool ReminderRemovalCompleted();		// Table 38
extern void UpdateReminders();				// Table 44

// Other functions
extern void ResetFVariablesReminder();


#endif
