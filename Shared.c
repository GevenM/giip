#include "Shared.h"


y_basal k_emptyBas = {"", {0}};
y_basal f_activeBasal;
y_basal f_activeTmpBasal;

//single rate increment bounds
const y_insulinValue k_maxBasalBound = 10;
const y_insulinValue k_minBasalBound = 0;

//daily bound
const y_insulinValue k_maxDailyInsulin = 100;

e_operations c_operation = Idle;
e_menus c_menuScreen = None;
e_menus c_1_menuScreen = None;
e_menus f_menuChoice = Basal;
e_menus f_1_menuChoice = Basal;
e_pwrStatus c_pwrStatus = Standby;


e_opStatus c_basCreateStatus;
e_opStatus c_basRemStatus;
e_opStatus c_basStartStatus;
e_opStatus c_basStopStatus;
e_opStatus c_tmpStartStatus;
e_opStatus c_bolCreateStatus;
e_opStatus c_bolRemStatus;
e_opStatus c_remindCreateStatus;
e_opStatus c_remindRemStatus;

e_bolStatus c_bolStartStatus;


bool f_basalIsActive = false;
bool f_temporaryBasalIsActive = false;
bool f_bolusInProgress = false;


bool BolusInProgress(){
	return f_bolusInProgress;
}

bool ScheduleCreationAllowed(){
	return true;
}

bool ScheduleExists(){
	return false;
}



bool BolusPresetExists(){
	return false;
}

bool BolusCreationAllowed(){
	return false;
}

bool BasalIsActive(){
	return !( ProfileCompare( &f_activeBasal, &k_emptyBas ));
}

bool TemporaryBasalIsActive(){
	return false;
}
