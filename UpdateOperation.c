
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


void UpdateOperation(){
	switch (c_pwrStatus){
	case Ready:
		switch(c_operation){
		case Idle:
			if (M_basCreateReq) c_operation = CreateBasProf;
			else if (M_basRemoveReq) c_operation = RemoveBasProf;
			else if (M_basStartReq) c_operation = StartBasProf;
			else if (M_basStopReq) c_operation = StopBasProf;
			else if (M_tmpBasStartReq) c_operation = StartTmpBas;
			else if (M_tmpBasStopReq) c_operation = StopTmpBas;
			else if (M_bolCreateReq) c_operation = CreateBolPre;
			else if (M_bolRemoveReq) c_operation = RemoveBolPre;
			else if (M_bolStartReq) c_operation = StartBol;
			else if (M_reminderCreateReq) c_operation = CreateReminder;
			else if (M_reminderRemoveReq) c_operation = RemoveReminder;
			else ;
			break;
		case CreateBasProf:
			if (BasalProfileCreationCompleted()) c_operation = Idle;
			break;

		case RemoveBasProf:
			if (BasalProfileRemovalCompleted()) c_operation = Idle;
			break;

		case StartBasProf:
			if (BasalProfileActivationCompleted()) c_operation = Idle;
			break;

		case StopBasProf:
			if (BasalProfileDeactivationCompleted()) c_operation = Idle;
			break;

		case StartTmpBas:
			if (TemporaryBasalActivationCompleted()) c_operation = Idle;
			break;

		case StopTmpBas:
			if ( TemporaryBasalDeactivationCompleted() ) c_operation = Idle;
			break;

		case CreateBolPre:
			if ( BolusPresetCreationCompleted() ) c_operation = Idle;
			break;

		case RemoveBolPre:
			if ( BolusPresetRemovalCompleted() ) c_operation = Idle;
			break;

		case StartBol:
			if ( BolusActivationCompleted() ) c_operation = Idle;
			break;

		case CreateReminder:
			break;
		case RemoveReminder:
			break;
		default: break;
		}
		break;
	default: c_operation = Idle; break;
	}
}
