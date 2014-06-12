#include "DisplayOut.h"
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
			else if (M_bolCreateReq) c_operation = CreateBolusPreset;
			else if (M_bolRemoveReq) c_operation = RemoveBolusPreset;
			else if (M_bolStartReq) c_operation = StartBolus;
			else if (M_reminderCreateReq) c_operation = CreateReminder;
			else if (M_reminderRemoveReq) c_operation = RemoveReminder;
			else ;
			break;
		case CreateBasProf:

		case RemoveBasProf:

		case StartBasProf:

		case StopBasProf:

		case StartTmpBas:

		case StopTmpBas:

		case CreateBolusPreset:

		case RemoveBolusPreset:

		case StartBolus:

		case CreateReminder:

		case RemoveReminder:

		default: break;
		}
		break;
	default: c_operation = Idle; break;
	}
}
