#ifndef SHARED_FILE
#define SHARED_FILE

#define NO_VALUE 0

#define ACCEPT 1
#define RETRY 2
#define CANCEL 3

#define CALCULATOR 4
#define PRESET 5
#define MANUAL 6


#define k_maxOutputRate 10 // maximum output rate in IU/hr.
#define k_secPerHour 	3600

//#define k_segDay 48

#include <stdbool.h>
#include "BasalProfiles.h"
#include "TemporaryBasal.h"
#include "BolusPresets.h"

typedef enum {
	None,
	Main,
	Basal,
	Bolus,
	Schedule,
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
	Schedule_Create,
	Schedule_Remove,

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
} e_menus;


typedef enum {
	Standby,
	POST,
	Ready,
	OffReq,
	Error,
} e_pwrStatus;


typedef enum {
	Idle,
	CreateBasProf,
	RemoveBasProf,
	StartBasProf,
	StopBasProf,
	StartTmpBas,
	StopTmpBas,
	CreateBolPre,
	RemoveBolPre,
	StartBol,
	CreateReminder,
	RemoveReminder,
} e_operations;


typedef enum {
	e_opStatus_idle,
	e_opStatus_confirm,
	e_opStatus_invalid,

} e_opStatus;


typedef enum {
	e_bolStatus_idle,
	e_bolStatus_confirm,
	e_bolStatus_invalid,
	e_bolStatus_preset,
	e_bolStatus_calculator,
	e_bolStatus_manual,
} e_bolStatus;




extern e_menus c_menuScreen;
extern e_menus c_1_menuScreen;
extern e_menus f_menuChoice;
extern e_menus f_1_menuChoice;

extern e_operations c_operation;

extern e_pwrStatus c_pwrStatus;

extern e_opStatus c_basCreateStatus;
extern e_opStatus c_basRemStatus;
extern e_opStatus c_basStartStatus;
extern e_opStatus c_basStopStatus;
extern e_opStatus c_tmpStartStatus;
extern e_opStatus c_bolCreateStatus;
extern e_opStatus c_bolRemStatus;
extern e_opStatus c_remindCreateStatus;
extern e_opStatus c_remindRemStatus;

extern e_bolStatus c_bolStartStatus;


extern bool ScheduleCreationAllowed();
extern bool ScheduleExists();



extern bool BasalIsActive();
extern bool TemporaryBasalIsActive();

extern y_basal k_emptyBas;
extern y_tmpBasal k_emptyTmp;
extern y_bolus k_emptyBol;

extern y_basal f_activeBasal;
extern y_tmpBasal f_activeTmpBasal;
extern y_bolus f_activeBolus;

extern const y_insulinValue k_maxBasalBound;
extern const y_insulinValue k_minBasalBound;
extern const y_insulinValue k_maxDailyInsulin;
extern const y_insulinValue k_maxBolusBound;
extern const y_insulinValue k_minBolusBound;

extern const y_duration k_maxTmpDuration;
extern const y_duration k_minTmpDuration;
extern const y_tmpBasalRate k_maxTmpRate;
extern const y_tmpBasalRate k_minTmpRate;

#endif



