#include "BolusFunctions.h"
#include "BolusPresets.h"
#include <string.h>

bool BolusIsValid(y_bolus *preset){

	// Check that profile name is unique
	if ( !PresetNameIsValidAndUnique( preset )){
		return false;
	}

	if ( !BolusIsInBounds( preset )){
		return false;
	}

	return true;
}
