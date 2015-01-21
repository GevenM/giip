#include "BasalFunctions.h"
#include <string.h>
#include "BasalProfiles.h"

bool SelectedBasalProfileIsActive(y_basal *profile){
	if ( IsActiveProfile( profile ) ){
		return true;
	}
	return false;
}
