#include "TemporaryBasalFunctions.h"

bool F_startTmpBasal = false;
y_tmpBasal F_tmpBasalToStart;

y_tmpBasal f_activeTmpBasal;
bool f_tmpBasalIsActive = false;

bool F_stopTmpBasal = false;


void ResetFVariablesTemporaryBasal(){
	CopyTmpBasal( &k_emptyTmp, &F_tmpBasalToStart );
	F_startTmpBasal = false;

	F_stopTmpBasal = false;
}
