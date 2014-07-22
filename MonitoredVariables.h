#ifndef MONITOREDVARIABLES_H
#define MONITOREDVARIABLES_H

#include "shared.h"
#include "hardware.h"
#include <string.h>
#include "BasalProfiles.h"
#include "TemporaryBasal.h"

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

extern unsigned char M_basCreateResp;

extern y_basal m_basRemSelected;
extern bool M_basRemSelected;
extern unsigned char M_basRemResp;

extern bool M_basActSelected;
extern y_basal m_basActSelected;
extern unsigned char M_basStartResp;

extern unsigned char M_basStopResp;

extern unsigned char M_tmpStartResp;
extern y_tmpBasal m_tmpBas;
extern bool M_tmpBas;

extern unsigned char M_tmpStopResp;

extern unsigned char M_bolCreateResp;
extern y_bolus m_bolus;
extern bool M_bolus;

extern unsigned char M_bolRemResp;
extern y_bolus m_bolSelected;
extern bool M_bolSelected;

extern unsigned char M_bolStartResp;
extern y_glucose m_bloodGlucose;
extern y_carbs m_carbs;
extern bool M_bloodGlucose;
extern bool M_carbs;
extern unsigned char M_selectedMethod;


#endif
