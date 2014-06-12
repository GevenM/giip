#include "shared.h"
#include "hardware.h"
#include <string.h>

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

extern y_basal M_BasProf;
