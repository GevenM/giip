#include "BolusFunctions.h"
#include "BolusPresets.h"
#include "InsulinOutputCalculator.h"

void UpdateActiveBolus(){
	if ( c_pwrStatus == e_pwrStatus_ready ){
		if ( f_bolusInProgress ){
			if ( ( f_activeBolus.Amount - f_bolusOut ) <= 0 ){
				CopyPreset( &k_emptyBol, &f_activeBolus );
				f_bolusInProgress = false;
			} else {
				f_activeBolus.Amount -= f_bolusOut;
			}
		} else {
			if ( F_startBolus ){
				CopyPreset( &F_bolusToStart, &f_activeBolus );
				f_bolusInProgress = true;
			} else{
				; //NC
			}
		}
	} else {
		CopyPreset( &k_emptyBol, &f_activeBolus );
		f_bolusInProgress = false;
	}
}

