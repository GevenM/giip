#include "TemporaryBasalFunctions.h"
#include "TypesAndConstants.h"
#include "RTC.h"

int p_prevMin = 0;


void UpdateActiveTemporaryBasal(){
	if ( c_pwrStatus == e_pwrStatus_ready ){
		if( f_tmpBasalIsActive ){
			if( F_stopTmpBasal ){
				CopyTmpBasal( &k_emptyTmp, &f_activeTmpBasal );
				f_tmpBasalIsActive = false;
			} else {
				if ( p_prevMin != GetCurrentMin() ){
					if( f_activeTmpBasal.Duration - 1 <= 0 ){
						CopyTmpBasal( &k_emptyTmp, &f_activeTmpBasal );
						f_tmpBasalIsActive = false;
					} else {
						f_activeTmpBasal.Duration = f_activeTmpBasal.Duration - 1;
					}
				}
				p_prevMin = GetCurrentMin();
			}
		} else {
			if( F_stopTmpBasal ){
				CopyTmpBasal( &k_emptyTmp, &f_activeTmpBasal );
				f_tmpBasalIsActive = false;
			} else {
				if( F_startTmpBasal ){
					CopyTmpBasal( &F_tmpBasalToStart, &f_activeTmpBasal );
					f_tmpBasalIsActive = true;
				} else {
					; //NC
				}
			}

		}
	} else {
		CopyTmpBasal( &k_emptyTmp, &f_activeTmpBasal );
		f_tmpBasalIsActive = false;
	}
}

