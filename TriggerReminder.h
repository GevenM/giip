#ifndef TRIGGERREMINDER_H
#define TRIGGERREMINDER_H

extern void TriggerReminder();
extern y_reminder GetPendingReminder();
extern bool ReminderIsPending();
extern void PendingReminderAckHandler();

#endif
