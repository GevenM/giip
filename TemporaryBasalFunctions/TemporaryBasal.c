#include "TemporaryBasalFunctions.h"


void CopyTmpBasal(y_tmpBasal *fromTmpBasal, y_tmpBasal *toTmpBasal){

	toTmpBasal->Rate = fromTmpBasal->Rate;

	toTmpBasal->Duration = fromTmpBasal->Duration;

}

bool TemporaryRateOutOfBound( y_tmpBasal *profile ){

	if ( profile->Rate < k_minTmpRate || profile->Rate > k_maxTmpRate) //the rate is outside allowable bounds
		return true;

	if (profile->Rate*(profile->Duration/60) > k_maxDailyInsulin) // the rate is outside allowable daily tolerance
		return true;

	return false;
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
