#include "BasalTables.h"

void UpdateBasalProfileSet(){
	if ( c_pwrStatus == e_pwrStatus_ready ){
		if( F_createBasalProfile ){
			AddProfileToSet( &F_basalProfileToCreate );
		} else if ( F_removeBasalProfile ){
			RemoveProfileFromSet( &F_basalProfileToRemove );
		} else {
			;
		}
	} else {
		;
	}
}
