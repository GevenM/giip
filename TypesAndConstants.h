#ifndef TYPESANDCONSTANTS_H
#define TYPESANDCONSTANTS_H

#include "driverlib.h"

/****** CONSTANTS FROM DESIGN SPEC ******/


#define k_segDay 48

#define k_basalNameLength 12
#define k_bolusNameLength 12

#define k_remindMessageLength 100
#define k_remindNameLength 12

#define k_maxOutputRate 720000
#define k_maxDailyInsulin 360000

#define k_IUMultiplier 3600
#define k_secPerHour 3600
#define k_minPerHour 60

//single rate increment bounds
#define k_maxBasalBound 36000
#define k_minBasalBound 0

#define k_maxBolusBound 36000
#define k_minBolusBound 3600

#define k_maxTmpDuration 1440
#define k_minTmpDuration 60
#define k_maxTmpRate 36000
#define k_minTmpRate 3600


/****** SIMPLE TYPES FROM DESIGN SPEC ******/
#include<stdbool.h>
typedef char y_basalName[ k_basalNameLength + 1 ];
typedef unsigned int y_basalRate;

typedef enum {
	e_bolMethod_calculator,
	e_bolMethod_preset,
	e_bolMethod_manual,
	e_bolMethod_noValue,
} y_bolMethod;

typedef enum {
	e_bolStatus_idle,
	e_bolStatus_confirm,
	e_bolStatus_invalid,
	e_bolStatus_preset,
	e_bolStatus_calculator,
	e_bolStatus_manual,
} y_bolStatus;

typedef char y_bolusName[ k_bolusNameLength+1 ];
typedef unsigned int y_carbs;
typedef unsigned char y_day;
typedef unsigned int y_duration;
typedef unsigned int y_glucose;
typedef unsigned char y_hour;
typedef unsigned long y_insulinValue;
typedef unsigned char y_minute;
typedef unsigned char y_month;

typedef enum {
	e_operation_idle,
	e_operation_createBasProf,
	e_operation_removeBasProf,
	e_operation_startBasProf,
	e_operation_stopBasProf,
	e_operation_startTmpBas,
	e_operation_stopTmpBas,
	e_operation_createBolusPreset,
	e_operation_removeBolusPreset,
	e_operation_startBolus,
	e_operation_createReminder,
	e_operation_removeReminder,
} y_operation;

typedef enum{
	e_opStatus_idle,
	e_opStatus_confirm,
	e_opStatus_invalid,
} y_opStatus;

typedef enum{
	e_post_pass,
	e_post_fail,
} y_post;

typedef enum{
	e_pwrStatus_ready,
	e_pwrStatus_standby,
	e_pwrStatus_post,
	e_pwrStatus_offReq
} y_pwrStatus;

typedef char y_remindMessage[ k_remindMessageLength + 1 ];
typedef char y_remindName[ k_remindNameLength + 1 ];

typedef enum{
	e_response_accept,
	e_response_retry,
	e_response_cancel,
	e_response_noValue,
} y_response;

typedef unsigned char y_s;
typedef unsigned char y_second;
typedef unsigned char y_segment;
typedef unsigned int y_year;


/******	COMPLEX TYPES FROM DESIGN SPEC ******/
typedef struct y_basal{
	y_basalName Name;
	y_basalRate Rate[k_segDay];
} y_basal;

typedef struct y_bolus{
	y_bolusName Name;
	y_insulinValue Amount;
} y_bolus;

typedef Calendar y_dateTime;

typedef struct y_reminder{
	y_remindName Name;
	y_remindMessage Message;
	y_dateTime Time;
} y_reminder;

typedef struct tmpBasal{
	y_basalRate Rate;
	y_duration Duration;
} y_tmpBasal;


/***** MORE CONSTANTS ******/
extern y_basal k_emptyBas;
extern y_tmpBasal k_emptyTmp;
extern y_bolus k_emptyBol;
extern y_reminder k_emptyReminder;

#endif
