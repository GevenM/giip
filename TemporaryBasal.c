#include "TemporaryBasal.h"
#include "Shared.h"

void CopyTmpBasal(y_tmpBasal *fromTmpBasal, y_tmpBasal *toTmpBasal){

	toTmpBasal->Rate = fromTmpBasal->Rate;

	toTmpBasal->Duration = fromTmpBasal->Duration;

}

bool ActivateTemporaryBasalIsValid(y_tmpBasal *profile){

	if ( profile->Rate < k_minBasalBound || profile->Rate > k_maxBasalBound) //each single rate is within allowable bounds
			return false;

	if (profile->Rate*profile->Duration > k_maxDailyInsulin) //compare sum of rates to daily max
		return false;
	else
		return true;
}
