#include "Shared.h"




//y_basal f_activeBasal = {"", {0}};
//bool f_basalIsActive = false;

//y_tmpBasal f_activeTmpBasal = {0, 0};
//y_bolus f_activeBolus = {"", 0};




y_operation c_operation = e_operation_idle;
y_menus c_menuScreen = None;
y_menus c_1_menuScreen = None;
y_menus f_menuChoice = Basal;
y_menus f_1_menuChoice = Basal;
y_pwrStatus c_pwrStatus = e_pwrStatus_standby;
y_safetyStatus c_safetyStatus = e_safe;


y_opStatus c_basCreateStatus = e_opStatus_idle;
y_opStatus c_basRemStatus = e_opStatus_idle;
y_opStatus c_basStartStatus = e_opStatus_idle;
y_opStatus c_basStopStatus = e_opStatus_idle;
y_opStatus c_tmpStartStatus = e_opStatus_idle;
y_opStatus c_bolCreateStatus = e_opStatus_idle;
y_opStatus c_bolRemStatus = e_opStatus_idle;
y_opStatus c_remindCreateStatus = e_opStatus_idle;
y_opStatus c_remindRemStatus = e_opStatus_idle;

y_bolStatus c_bolStartStatus;



//bool f_temporaryBasalIsActive = false;
//bool f_bolusInProgress = false;


bool ScheduleCreationAllowed(){
	return true;
}

bool ScheduleExists(){
	return false;
}







