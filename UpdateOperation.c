
#include "UpdateOperation.h"

#include "Shared.h"
#include "DisplayOut.h"
#include "CreateBasalProfile.h"
#include "RemoveBasalProfile.h"
#include "ActivateBasalProfile.h"
#include "DeactivateBasalProfile.h"
#include "ActivateTemporaryBasal.h"
#include "DeactivateTemporaryBasal.h"
#include "CreateBolusPreset.h"
#include "RemoveBolusPreset.h"
#include "ActivateBolus.h"
#include "CreateReminder.h"
#include "RemoveReminder.h"


void UpdateOperation(){
	switch (c_pwrStatus){
	case e_pwrStatus_ready:
		switch(c_operation){
		case e_operation_idle:
			if (M_basCreateReq) c_operation = e_operation_createBasProf;
			else if (M_basRemoveReq) c_operation = e_operation_removeBasProf;
			else if (M_basStartReq) c_operation = e_operation_startBasProf;
			else if (M_basStopReq) c_operation = e_operation_stopBasProf;
			else if (M_tmpBasStartReq) c_operation = e_operation_startTmpBas;
			else if (M_tmpBasStopReq) c_operation = e_operation_stopTmpBas;
			else if (M_bolCreateReq) c_operation = e_operation_createBolusPreset;
			else if (M_bolRemoveReq) c_operation = e_operation_removeBolusPreset;
			else if (M_bolStartReq) c_operation = e_operation_startBolus;
			else if (M_reminderCreateReq) c_operation = e_operation_createReminder;
			else if (M_reminderRemoveReq) c_operation = e_operation_removeReminder;
			else ;
			break;
		case e_operation_createBasProf:
			if (BasalProfileCreationCompleted()) c_operation = e_operation_idle;
			break;

		case e_operation_removeBasProf:
			if (BasalProfileRemovalCompleted()) c_operation = e_operation_idle;
			break;

		case e_operation_startBasProf:
			if (BasalProfileActivationCompleted()) c_operation = e_operation_idle;
			break;

		case e_operation_stopBasProf:
			if (BasalProfileDeactivationCompleted()) c_operation = e_operation_idle;
			break;

		case e_operation_startTmpBas:
			if (TemporaryBasalActivationCompleted()) c_operation = e_operation_idle;
			break;

		case e_operation_stopTmpBas:
			if ( TemporaryBasalDeactivationCompleted() ) c_operation = e_operation_idle;
			break;

		case e_operation_createBolusPreset:
			if ( BolusPresetCreationCompleted() ) c_operation = e_operation_idle;
			break;

		case e_operation_removeBolusPreset:
			if ( BolusPresetRemovalCompleted() ) c_operation = e_operation_idle;
			break;

		case e_operation_startBolus:
			if ( BolusActivationCompleted() ) c_operation = e_operation_idle;
			break;

		case e_operation_createReminder:
			if ( ReminderCreationCompleted() ) c_operation = e_operation_idle;
			break;

		case e_operation_removeReminder:
			if ( ReminderRemovalCompleted() ) c_operation = e_operation_idle;
			break;

		default: break;
		}
		break;
	default: c_operation = e_operation_idle; break;
	}
}
