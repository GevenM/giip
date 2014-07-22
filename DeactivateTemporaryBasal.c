#include "DeactivateTemporaryBasal.h"

#include "Shared.h"
#include "MonitoredVariables.h"
#include "TemporaryBasal.h"

bool F_stopTemporaryBasal; // From NL expression [ Stop Temporary Basal ]

void StopTemporaryBasal();

void DeactivateTemporaryBasal(){
	if ( c_operation == StopTmpBas ){
		if ( M_tmpStopResp == ACCEPT ){
			F_stopTemporaryBasal = true;
			StopTemporaryBasal();

		} else if ( M_tmpStopResp == CANCEL ){
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
	if ( F_stopTemporaryBasal || M_tmpStopResp == CANCEL ){
		return true;
	}
	return false;
}

