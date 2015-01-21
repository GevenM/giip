#ifndef MONITOREDVARIABLES_H
#define MONITOREDVARIABLES_H

#include "shared.h"
#include "hardware.h"
//#include <string.h>
#include "BasalProfiles.h"
#include "TemporaryBasalFunctions/TemporaryBasal.h"
#include "BolusFunctions/BolusPresets.h"
#include "ReminderFunctions/Reminder.h"

extern void UpdateMonitoredVariables();
extern void InitMonitoredVariables();


extern bool M_menuReq;
extern bool M_backReq;
extern bool M_selReq;
extern bool M_upReq;
extern bool M_downReq;
extern bool M_rightReq;
extern bool M_leftReq;
extern bool M_nextReq;
extern bool M_addReq;

extern bool M_pwrReq;
extern bool M_bolStartReq;
extern bool M_reminderCreateReq;
extern bool M_reminderRemoveReq;
extern bool M_basStopReq;
extern bool M_tmpBasStopReq;
extern bool M_tmpBasStartReq;
extern bool M_basStartReq;
extern bool M_basCreateReq;
extern bool M_basRemoveReq;
extern bool M_bolCreateReq;
extern bool M_bolRemoveReq;

extern y_basal m_basProf;
extern bool M_basProf;

extern y_response M_basCreateResp;

extern y_basal m_basRemSelected;
extern bool M_basRemSelected;
extern y_response M_basRemResp;

extern bool M_basActSelected;
extern y_basal m_basActSelected;
extern y_response M_basStartResp;

extern y_response M_basStopResp;

extern y_response M_tmpStartResp;
extern y_tmpBasal m_tmpBas;
extern bool M_tmpBas;

extern y_response M_tmpStopResp;

extern y_response M_bolCreateResp;
extern y_bolus m_bolus;
extern bool M_bolus;

extern y_response M_bolRemResp;
extern y_bolus m_bolSelected;
extern bool M_bolSelected;

extern y_response M_bolStartResp;
extern y_glucose m_bloodGlucose;
extern y_carbs m_carbs;
extern bool M_bloodGlucose;
extern bool M_carbs;
extern y_bolMethod M_selectedMethod;

extern y_reminder m_reminder;
extern bool M_reminder;
extern y_response M_remindCreateResp;
extern y_response M_remindRemResp;

extern bool M_occlusionInLine;
extern bool M_bubbleInLine;

#endif
