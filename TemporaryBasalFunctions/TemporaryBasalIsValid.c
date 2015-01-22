#include "TemporaryBasalFunctions.h"

bool TemporaryBasalIsValid( y_tmpBasal *profile ){

	if ( TemporaryRateOutOfBound( profile ) ){
		return false;
	}

	return true;
}
