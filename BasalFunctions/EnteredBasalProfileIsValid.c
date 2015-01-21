#include "BasalFunctions.h"
#include <string.h>
#include "BasalProfiles.h"

bool EnteredBasalProfileIsValid(y_basal *profile){
	// implementation does not use too many nested ifs for readability, but functions the same as function table
	// by first eliminating possible outcomes that return false.

	// profile exists in the basal set.
	if( ProfileInSet( profile ) ){
		return false;
	}

	// profile does not have a name.
	if ( !ProfileHasName( profile ) ){ //check name is not empty string. strcmp return 0 on match and 1 or -1 if different
		return false;
	}


	if ( ProfileSegmentOutOfBound( profile )){
		return false;
	}


	if ( ProfileSumOutOfBound ( profile )){
		return false;
	}

	return true;
}




