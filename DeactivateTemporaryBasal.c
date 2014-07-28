#include "DeactivateTemporaryBasal.h"

#include "Shared.h"
#include "MonitoredVariables.h"
#include "TemporaryBasal.h"

bool F_stopTemporaryBasal; // From NL expression [ Stop Temporary Basal ]

void StopTemporaryBasal();

void DeactivateTemporaryBasal(){
	if ( c_operation == e_operation_stopTmpBas ){
		if ( M_tmpStopResp == e_response_accept ){
			F_stopTemporaryBasal = true;
			StopTemporaryBasal();

		} else if ( M_tmpStopResp == e_response_cancel ){
			F_stopTemporaryBasal = false;
		}

	} else {
		F_stopTemporaryBasal = false;
	}
}

void StopTemporaryBasal(){
	CopyTmpBasal( &k_emptyTmp, &f_activeTmpBasal );
}

bool TemporaryBasalDeactivationCompleted(){
	if ( F_stopTemporaryBasal || M_tmpStopResp == e_response_cancel ){
		return true;
	}
	return false;
}

