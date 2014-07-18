
#include "UpdateOperation.h"


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
			else if (M_bolStartReq) c_operation = StartBolus;
			else if (M_reminderCreateReq) c_operation = CreateReminder;
			else if (M_reminderRemoveReq) c_operation = RemoveReminder;
			else ;
			break;
		case CreateBasProf:
			if (BasalProfileCreationCompleted()){
				c_operation = Idle;
			}
			break;
		case RemoveBasProf:
			if (BasalProfileRemovalCompleted()){
				c_operation = Idle;
			}
			break;

		case StartBasProf:
			if (BasalProfileActivationCompleted()){
				c_operation = Idle;
			}
			break;
		case StopBasProf:
			if (BasalProfileDeactivationCompleted()){
				c_operation = Idle;
			}
			break;
		case StartTmpBas:
			if (TemporaryBasalActivationCompleted()){
				c_operation = Idle;
			}
			break;
		case StopTmpBas:
			break;
		case CreateBolPre:
			break;
		case RemoveBolPre:
			break;
		case StartBolus:
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
