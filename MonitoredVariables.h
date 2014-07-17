#ifndef MONITOREDVARIABLES_H
#define MONITOREDVARIABLES_H

#include "shared.h"
#include "hardware.h"
#include <string.h>
#include "BasalProfiles.h"

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

extern unsigned char m_basRemSelected;
extern bool M_basRemSelected;
extern unsigned char M_basRemResp;

extern bool M_basActSelected;
extern y_basal m_basActSelected;
extern unsigned char M_basStartResp;

#endif
