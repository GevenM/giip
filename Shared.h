#ifndef SHARED_FILE
#define SHARED_FILE

#include "TypesAndConstants.h"


#include <stdbool.h>


typedef enum {
	None,
	Main,
	Basal,
	Bolus,
	Reminder,
	Settings,
	ShutDown,
	BasalTmpActive,
	BasalBothActive,
	BasalProfActive,
	BasalNoActive,
	Basal_Manage,
	Basal_StartProfile,
	Basal_StopProfile,
	Basal_StartTmp,
	Basal_StopTmp,
	Basal_Manage_Create,
	Basal_Manage_Remove,
	Bolus_Start,
	Bolus_Manage,
	Bolus_Manage_Create,
	Bolus_Manage_Remove,
	Reminder_Create,
	Reminder_Remove,

	BolusAlreadyActive,
	RemindCreateNotAllowed,
	NoRemind,
	BolusCreateNotAllowed,
	NoBolusPreset,
	BasCreateNotAllowed,
	NoBasProf,

	CreateBasProf_Confirm,
	CreateBasProf_Idle,
	CreateBasProf_Invalid,

	RemoveBasProf_Confirm,
	RemoveBasProf_Idle,
	RemoveBasProf_Invalid,

	StartBasProf_Idle,
	StartBasProf_Confirm,
	StartBasProf_Invalid,

	StopBasProf_All,

	StartTmpBas_Idle,
	StartTmpBas_Confirm,
	StartTmpBas_Invalid,

	StopTmpBas_All,

	CreateBolusPreset_Idle,
	CreateBolusPreset_Confirm,
	CreateBolusPreset_Invalid,

	RemoveBolusPreset_Idle,
	RemoveBolusPreset_Confirm,
	RemoveBolusPreset_Invalid,

	StartBolus_Idle,
	StartBolus_Confirm,
	StartBolus_Invalid,
	StartBolus_Preset,
	StartBolus_Calculator,
	StartBolus_Manual,

	CreateReminder_Idle,
	CreateReminder_Confirm,
	CreateReminder_Invalid,

	RemoveReminder_Idle,
	RemoveReminder_Confirm,

	Settings_ClearFlash,
	Settings_DateTime,
	Settings_DateTime_NotAllowed
} y_menus;



extern y_menus c_menuScreen;
extern y_menus c_1_menuScreen;
extern y_menus f_menuChoice;
extern y_menus f_1_menuChoice;

extern y_operation c_operation;
extern y_pwrStatus c_pwrStatus;

extern y_opStatus c_basCreateStatus;
extern y_opStatus c_basRemStatus;
extern y_opStatus c_basStartStatus;
extern y_opStatus c_basStopStatus;
extern y_opStatus c_tmpStartStatus;
extern y_opStatus c_bolCreateStatus;
extern y_opStatus c_bolRemStatus;
extern y_opStatus c_remindCreateStatus;
extern y_opStatus c_remindRemStatus;

extern y_bolStatus c_bolStartStatus;


extern bool ReminderCreationAllowed();
extern bool ReminderExists();



extern bool BasalIsActive();
extern bool TemporaryBasalIsActive();


extern y_basal f_activeBasal;
extern y_tmpBasal f_activeTmpBasal;
extern y_bolus f_activeBolus;



#endif



