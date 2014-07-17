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

unsigned char M_basCreateResp;

y_basal m_basRemSelected;
bool M_basRemSelected;
unsigned char M_basRemResp;

y_basal m_basProf;
bool M_basProf;

bool M_basActSelected;
y_basal m_basActSelected;
unsigned char M_basStartResp;

bool M_basStopResp;

bool M_tmpStartResp;
y_tmpBasal m_tmpBas;
bool M_tmpBas;

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

	if ( c_operation == CreateBasProf ){
		if ( I_middleSelBtn ) M_basCreateResp = ACCEPT;
		else if ( I_rightSelBtn ) M_basCreateResp = RETRY;
		else if ( I_leftSelBtn ) M_basCreateResp = CANCEL;
	}

	if ( c_operation == RemoveBasProf ){
		if ( I_middleSelBtn ) M_basRemResp = ACCEPT;
		else if ( I_rightSelBtn ) M_basRemResp = RETRY;
		else if ( I_leftSelBtn ) M_basRemResp = CANCEL;
	}

	if ( c_operation == StartBasProf ){
		if ( I_middleSelBtn ) M_basStartResp = ACCEPT;
		else if ( I_rightSelBtn ) M_basStartResp = RETRY;
		else if ( I_leftSelBtn ) M_basStartResp = CANCEL;
	}

	if ( c_operation == StartTmpBas ){
		if ( I_middleSelBtn ) M_tmpStartResp = ACCEPT;
		else if ( I_rightSelBtn ) M_tmpStartResp = RETRY;
		else if ( I_leftSelBtn ) M_tmpStartResp = CANCEL;
	}

	if ( c_operation == StopBasProf ){
		if ( I_middleSelBtn ) M_basStartResp = ACCEPT;
		else if ( I_leftSelBtn ) M_basStartResp = CANCEL;
	}

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

	M_basProf = false;
	M_basRemSelected = false;

	M_basCreateResp = NO_VALUE;
	M_basRemResp = NO_VALUE;

	M_basActSelected = false;
	M_basStartResp = NO_VALUE;

	M_basStopResp = NO_VALUE;

	M_tmpStartResp = NO_VALUE;
	M_tmpBas = false;

}
