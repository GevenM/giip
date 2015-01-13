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


y_response M_basCreateResp = e_response_noValue;

y_basal m_basRemSelected;
bool M_basRemSelected;
y_response M_basRemResp = e_response_noValue;

y_basal m_basProf;
bool M_basProf;

bool M_basActSelected;
y_basal m_basActSelected;
y_response M_basStartResp = e_response_noValue;

y_response M_basStopResp = e_response_noValue;

y_response M_bolCreateResp = e_response_noValue;
y_bolus m_bolus;
bool M_bolus;

y_response M_bolRemResp = e_response_noValue;
y_bolus m_bolSelected;
bool M_bolSelected;

y_response M_tmpStartResp = e_response_noValue;
y_tmpBasal m_tmpBas;
bool M_tmpBas;

y_response M_tmpStopResp = e_response_noValue;

y_response M_bolStartResp = e_response_noValue;
y_glucose m_bloodGlucose;
y_carbs m_carbs;
bool M_bloodGlucose;
bool M_carbs;
y_bolMethod M_selectedMethod = e_bolMethod_noValue;

y_reminder m_reminder;
bool M_reminder;
y_response M_remindCreateResp;
y_response M_remindRemResp;

bool M_occlusionInLine;
bool M_bubbleInLine;

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
			c_operation == e_operation_idle &&
			c_menuScreen == Main &&
			M_selReq &&
			f_menuChoice == ShutDown;

	M_bolStartReq =
			c_operation == e_operation_idle &&
			c_menuScreen == Bolus &&
			M_selReq &&
			f_menuChoice == Bolus_Start &&
			!BolusIsActive();

	M_reminderCreateReq =
			c_operation == e_operation_idle &&
			c_menuScreen == Reminder &&
			M_selReq &&
			f_menuChoice == Reminder_Create &&
			ReminderCreationAllowed();

	M_reminderRemoveReq =
			c_operation == e_operation_idle &&
			c_menuScreen == Reminder &&
			M_selReq &&
			f_menuChoice == Reminder_Remove &&
			ReminderRemovalAllowed();

	M_basStopReq =
			c_operation == e_operation_idle &&
			(c_menuScreen == BasalBothActive || c_menuScreen == BasalProfActive) &&
			M_selReq &&
			f_menuChoice == Basal_StopProfile;

	M_tmpBasStopReq =
			c_operation == e_operation_idle &&
			(c_menuScreen == BasalBothActive || c_menuScreen == BasalTmpActive ) &&
			M_selReq &&
			f_menuChoice == Basal_StopTmp;

	M_tmpBasStartReq =
			c_operation == e_operation_idle &&
			(c_menuScreen == BasalProfActive || c_menuScreen == BasalNoActive ) &&
			M_selReq &&
			f_menuChoice == Basal_StartTmp;

	M_basStartReq =
			c_operation == e_operation_idle &&
			(c_menuScreen == BasalTmpActive || c_menuScreen == BasalNoActive) &&
			M_selReq &&
			BasalProfileExists() &&
			f_menuChoice == Basal_StartProfile;

	M_basCreateReq =
			c_operation == e_operation_idle &&
			c_menuScreen == Basal_Manage &&
			M_selReq &&
			f_menuChoice == Basal_Manage_Create &&
			BasalCreationAllowed();

	M_basRemoveReq =
			c_operation == e_operation_idle &&
			c_menuScreen == Basal_Manage &&
			M_selReq &&
			f_menuChoice == Basal_Manage_Remove &&
			BasalProfileExists();

	M_bolCreateReq =
			c_operation == e_operation_idle &&
			c_menuScreen == Bolus_Manage &&
			M_selReq &&
			f_menuChoice == Bolus_Manage_Create &&
			BolusPresetCreationAllowed();

	M_bolRemoveReq =
			c_operation == e_operation_idle &&
			c_menuScreen == Bolus_Manage &&
			M_selReq &&
			f_menuChoice == Bolus_Manage_Remove &&
			BolusPresetExists();

	if ( c_operation == e_operation_createBasProf ){
		if ( I_middleSelBtn ) M_basCreateResp = e_response_accept;
		else if ( I_rightSelBtn ) M_basCreateResp = e_response_retry;
		else if ( I_leftSelBtn ) M_basCreateResp = e_response_cancel;
	}

	if ( c_operation == e_operation_removeBasProf ){
		if ( I_middleSelBtn ) M_basRemResp = e_response_accept;
		else if ( I_rightSelBtn ) M_basRemResp = e_response_retry;
		else if ( I_leftSelBtn ) M_basRemResp = e_response_cancel;
	}

	if ( c_operation == e_operation_startBasProf ){
		if ( I_middleSelBtn ) M_basStartResp = e_response_accept;
		else if ( I_rightSelBtn ) M_basStartResp = e_response_retry;
		else if ( I_leftSelBtn ) M_basStartResp = e_response_cancel;
	}

	if ( c_operation == e_operation_startTmpBas ){
		if ( I_middleSelBtn ) M_tmpStartResp = e_response_accept;
		else if ( I_rightSelBtn ) M_tmpStartResp = e_response_retry;
		else if ( I_leftSelBtn ) M_tmpStartResp = e_response_cancel;
	}

	if ( c_operation == e_operation_stopBasProf ){
		if ( I_middleSelBtn ) M_basStopResp = e_response_accept;
		else if ( I_leftSelBtn ) M_basStopResp = e_response_cancel;
		else M_basStopResp = e_response_noValue;
	}

	if ( c_operation == e_operation_stopTmpBas ){
		if ( I_middleSelBtn ) M_tmpStopResp = e_response_accept;
		else if ( I_leftSelBtn ) M_tmpStopResp = e_response_cancel;
		else M_tmpStopResp = e_response_noValue;
	}

	if ( c_operation == e_operation_createBolusPreset ){
		if ( I_middleSelBtn ) M_bolCreateResp = e_response_accept;
		else if ( I_rightSelBtn ) M_bolCreateResp = e_response_retry;
		else if ( I_leftSelBtn ) M_bolCreateResp = e_response_cancel;
		else M_bolCreateResp = e_response_noValue;
	}

	if ( c_operation == e_operation_removeBolusPreset ){
		if ( I_middleSelBtn ) M_bolRemResp = e_response_accept;
		else if ( I_rightSelBtn ) M_bolRemResp = e_response_retry;
		else if ( I_leftSelBtn ) M_bolRemResp = e_response_cancel;
		else M_bolRemResp = e_response_noValue;
	}

	if ( c_operation == e_operation_startBolus ){
		if ( I_middleSelBtn ) M_bolStartResp = e_response_accept;
		else if ( I_rightSelBtn ) M_bolStartResp = e_response_retry;
		else if ( I_leftSelBtn ) M_bolStartResp = e_response_cancel;
		else M_bolStartResp = e_response_noValue;
	}

	if ( c_operation == e_operation_createReminder ){
		if ( I_middleSelBtn ) M_remindCreateResp = e_response_accept;
		else if ( I_rightSelBtn ) M_remindCreateResp = e_response_retry;
		else if ( I_leftSelBtn ) M_remindCreateResp = e_response_cancel;
		else M_remindCreateResp = e_response_noValue;
	}

	if ( c_operation == e_operation_removeReminder ){
		if ( I_middleSelBtn ) M_remindRemResp = e_response_accept;
		else if ( I_rightSelBtn ) M_remindRemResp = e_response_retry;
		else if ( I_leftSelBtn ) M_remindRemResp = e_response_cancel;
		else M_remindRemResp = e_response_noValue;
	}

	if ( I_sensor1Btn || i_sensor1Btn ){
		M_occlusionInLine = true;
	}

	if ( I_sensor2Btn || i_sensor2Btn ){
		M_bubbleInLine = true;
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

	M_basCreateResp = e_response_noValue;
	M_basRemResp = e_response_noValue;

	M_basActSelected = false;
	M_basStartResp = e_response_noValue;

	M_basStopResp = e_response_noValue;

	M_tmpStartResp = e_response_noValue;
	M_tmpBas = false;

	M_tmpStopResp = e_response_noValue;

	M_bolus = false;
	M_bolCreateResp = e_response_noValue;

	M_bolSelected = false;
	M_bolRemResp = e_response_noValue;

	M_bolStartResp = e_response_noValue;
	M_selectedMethod = e_bolMethod_noValue;
	M_carbs = false;
	M_bloodGlucose = false;

	M_reminder = false;
	M_remindCreateResp = e_response_noValue;
	M_remindRemResp = e_response_noValue;

	M_occlusionInLine = false;
	M_bubbleInLine = false;
}
