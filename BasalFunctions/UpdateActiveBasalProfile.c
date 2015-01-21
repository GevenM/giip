#include "BasalFunctions.h"


void UpdateActiveBasalProfile(){
	if ( c_pwrStatus == e_pwrStatus_ready ){
		if ( F_stopBasal ){
			CopyProfile( &k_emptyBas, &f_activeBasal );
			f_basalIsActive = false;
		} else if ( !F_stopBasal ){
			if ( F_startBasal ) {
				CopyProfile( &F_basalToStart, &f_activeBasal );
				f_basalIsActive = true;
			} else {
				;
			}
		}
	} else {
		CopyProfile( &k_emptyBas, &f_activeBasal );
		f_basalIsActive = false;
	}
}
