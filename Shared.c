#include "Shared.h"

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

bool BasalProfileExists(){
	return false;
}

bool BasalCreationAllowed(){
	return true;
}

bool BolusPresetExists(){
	return false;
}

bool BolusCreationAllowed(){
	return false;
}

bool BasalIsActive(){
	return false;
}

bool TemporaryBasalIsActive(){
	return false;
}
