#include "TemporaryBasal.h"
#include "Shared.h"

void CopyTmpBasal(y_tmpBasal *fromTmpBasal, y_tmpBasal *toTmpBasal){

	toTmpBasal->Rate = fromTmpBasal->Rate;

	toTmpBasal->Duration = fromTmpBasal->Duration;

}

bool ActivateTemporaryBasalIsValid(y_tmpBasal *profile){

	if ( profile->Rate < k_minTmpRate || profile->Rate > k_maxTmpRate) //each single rate is within allowable bounds
			return false;

	if (profile->Rate*(profile->Duration/60) > k_maxDailyInsulin) //compare sum of rates to daily max
		return false;
	else
		return true;
}


bool TmpBasalCompare(y_tmpBasal *profile1, y_tmpBasal *profile2){
	// if the names match, the profiles are the same.
	if( profile1->Rate == profile2->Rate && profile1->Duration == profile2->Duration ){
		return true;
	}
	return false;
}


bool TemporaryBasalIsActive(){
	return !( TmpBasalCompare( &f_activeTmpBasal, &k_emptyTmp ));
}
