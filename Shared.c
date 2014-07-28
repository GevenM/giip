#include "Shared.h"




y_basal f_activeBasal = {"", {0}};
y_tmpBasal f_activeTmpBasal = {0, 0};
y_bolus f_activeBolus = {"", 0};




y_operation c_operation = e_operation_idle;
y_menus c_menuScreen = None;
y_menus c_1_menuScreen = None;
y_menus f_menuChoice = Basal;
y_menus f_1_menuChoice = Basal;
y_pwrStatus c_pwrStatus = e_pwrStatus_standby;


y_opStatus c_basCreateStatus;
y_opStatus c_basRemStatus;
y_opStatus c_basStartStatus;
y_opStatus c_basStopStatus;
y_opStatus c_tmpStartStatus;
y_opStatus c_bolCreateStatus;
y_opStatus c_bolRemStatus;
y_opStatus c_remindCreateStatus;
y_opStatus c_remindRemStatus;

y_bolStatus c_bolStartStatus;


bool f_basalIsActive = false;
bool f_temporaryBasalIsActive = false;
bool f_bolusInProgress = false;


bool ScheduleCreationAllowed(){
	return true;
}

bool ScheduleExists(){
	return false;
}







