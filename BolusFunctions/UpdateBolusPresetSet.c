#include "BolusFunctions.h"
#include "BolusPresets.h"

void UpdateBolusPresetSet(){
	if ( c_pwrStatus == e_pwrStatus_ready ){
		if( F_createBolusPreset ){
			AddPresetToSet( &F_bolusPresetToCreate );

		} else if ( F_removeBolusPreset ){
			RemovePresetFromSet( &F_bolusPresetToRemove );
		} else {
			;
		}
	} else {
		;
	}
}
