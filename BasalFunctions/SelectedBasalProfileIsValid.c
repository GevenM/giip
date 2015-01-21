#include "BasalFunctions.h"
#include "BasalProfiles.h"

// implements Table 15
bool SelectedBasalProfileIsValid(y_basal *profile){

	if( ProfileSegmentOutOfBound( profile ) ){
		return false;
	}

	if( ProfileSumOutOfBound( profile )){
		return false;
	}

	return true;
}
