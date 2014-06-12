#include <stdbool.h>
#include "MonitoredVariables.h"

bool M_menuReq;
bool M_backReq;
bool M_selReq;
bool M_upReq;
bool M_downReq;
bool M_rightReq;
bool M_leftReq;
bool M_nextReq;
bool M_addReq;

bool M_pwrReq;
bool M_bolStartReq;
bool M_reminderCreateReq;
bool M_reminderRemoveReq;
bool M_basStopReq;
bool M_tmpBasStopReq;
bool M_tmpBasStartReq;
bool M_basStartReq;
bool M_basCreateReq;
bool M_basRemoveReq;
bool M_bolCreateReq;
bool M_bolRemoveReq;

y_basal M_basProf;



void UpdateMonitoredVariables(){
	M_backReq = I_leftSelBtn;
	M_selReq = I_middleSelBtn;
	M_upReq = I_upDirBtn;
	M_downReq = I_downDirBtn;
	M_menuReq = I_middleSelBtn;
	M_rightReq = I_rightDirBtn;
	M_leftReq = I_leftDirBtn;
	M_nextReq =  I_rightSelBtn;
	M_addReq =  I_rightSelBtn;

	//M_selReq must be updated before the following requests.
	M_pwrReq =
			c_operation == Idle &&
			c_menuScreen == Main &&
			M_selReq &&
			f_menuChoice == ShutDown;

	M_bolStartReq =
			c_operation == Idle &&
			c_menuScreen == Bolus &&
			M_selReq &&
			f_menuChoice == Bolus_Start &&
			!BolusInProgress();

	M_reminderCreateReq =
			c_operation == Idle &&
			c_menuScreen == Schedule &&
			M_selReq &&
			f_menuChoice == Schedule_Create &&
			ScheduleCreationAllowed();

	M_reminderRemoveReq =
			c_operation == Idle &&
			c_menuScreen == Schedule &&
			M_selReq &&
			f_menuChoice == Schedule_Remove &&
			ScheduleExists();

	M_basStopReq =
			c_operation == Idle &&
			(c_menuScreen == BasalBothActive || c_menuScreen == BasalProfActive) &&
			M_selReq &&
			f_menuChoice == Basal_StopProfile;

	M_tmpBasStopReq =
			c_operation == Idle &&
			(c_menuScreen == BasalBothActive || c_menuScreen == BasalTmpActive ) &&
			M_selReq &&
			f_menuChoice == Basal_StopTmp;

	M_tmpBasStartReq =
			c_operation == Idle &&
			(c_menuScreen == BasalProfActive || c_menuScreen == BasalNoActive ) &&
			M_selReq &&
			f_menuChoice == Basal_StartTmp;

	M_basStartReq =
			c_operation == Idle &&
			(c_menuScreen == BasalTmpActive || c_menuScreen == BasalNoActive) &&
			M_selReq &&
			BasalProfileExists() &&
			f_menuChoice == Basal_StartProfile;

	M_basCreateReq =
			c_operation == Idle &&
			c_menuScreen == Basal_Manage &&
			M_selReq &&
			f_menuChoice == Basal_Manage_Create &&
			BasalCreationAllowed();

	M_basRemoveReq =
			c_operation == Idle &&
			c_menuScreen == Basal_Manage &&
			M_selReq &&
			f_menuChoice == Basal_Manage_Remove &&
			BasalProfileExists();

	M_bolCreateReq =
			c_operation == Idle &&
			c_menuScreen == Bolus_Manage &&
			M_selReq &&
			f_menuChoice == Bolus_Manage_Create &&
			BolusCreationAllowed();

	M_bolRemoveReq =
			c_operation == Idle &&
			c_menuScreen == Bolus_Manage &&
			M_selReq &&
			f_menuChoice == Bolus_Manage_Remove &&
			BolusPresetExists();
}

void InitMonitoredVariables(){
	M_menuReq = false;
	M_backReq = false;
	M_selReq = false;
	M_upReq = false;
	M_downReq = false;
	M_nextReq = false;
	M_addReq = false;

	M_pwrReq = false;
	M_bolStartReq = false;
	M_reminderCreateReq = false;
	M_reminderRemoveReq = false;
	M_basStopReq = false;
	M_tmpBasStopReq = false;
	M_tmpBasStartReq = false;
	M_basStartReq = false;
	M_basCreateReq = false;
	M_basRemoveReq = false;
	M_bolCreateReq = false;
	M_bolRemoveReq = false;

	strcpy(M_basProf.Name, "Profile 1");

	int i;
	for (i = 0; i < k_segDay; i++){
		M_basProf.Rate[i] = 0;
	}

}
