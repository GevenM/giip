#include "Shared.h"
#include "BasalProfiles.h"
#include "BolusFunctions/BolusPresets.h"
#include "BolusFunctions/BolusFunctions.h"

#include "TemporaryBasalFunctions/TemporaryBasalFunctions.h"

unsigned char deltaT = 1; // represents 1 second timestep

y_insulinValue f_basalOut = 0;
y_insulinValue f_bolusOut = 0;

void InsulinOutputCalculator(){
	if ( c_pwrStatus == e_pwrStatus_ready ){
		if ( TemporaryBasalIsActive() ){
			if( f_activeTmpBasal.Rate <= k_maxOutputRate ) {
				if ( BolusIsActive() ){
					if ( f_activeBolus.Amount > (( k_maxOutputRate - f_activeTmpBasal.Rate ) / k_secPerHour ) * deltaT ){
						f_basalOut = f_activeTmpBasal.Rate / k_secPerHour * deltaT;
						f_bolusOut = (( k_maxOutputRate - f_activeTmpBasal.Rate ) / k_secPerHour ) * deltaT;
					} else {
						f_basalOut = f_activeTmpBasal.Rate / k_secPerHour * deltaT;
						f_bolusOut = f_activeBolus.Amount;
					}
				} else {
					f_basalOut = f_activeTmpBasal.Rate / k_secPerHour * deltaT;
					f_bolusOut = 0;
				}
			} else {
				f_basalOut = ( k_maxOutputRate / k_secPerHour ) * deltaT;
			}
		} else if ( BasalIsActive() ) {
			if ( f_activeBasal.Rate[ GetCurrentTimeSegment() ] < k_maxOutputRate ){
				if ( BolusIsActive () ){
					if ( f_activeBolus.Amount > (( k_maxOutputRate - f_activeBasal.Rate[ GetCurrentTimeSegment() ] ) / k_secPerHour ) * deltaT ){
						f_basalOut = f_activeBasal.Rate[ GetCurrentTimeSegment() ] / k_secPerHour * deltaT;
						f_bolusOut = (( k_maxOutputRate - f_activeBasal.Rate[ GetCurrentTimeSegment() ]) / k_secPerHour ) * deltaT;
					} else {
						f_basalOut = f_activeBasal.Rate[ GetCurrentTimeSegment() ] / k_secPerHour * deltaT;
						f_bolusOut = f_activeBolus.Amount;
					}
				} else {
					f_basalOut = f_activeBasal.Rate[ GetCurrentTimeSegment() ] / k_secPerHour * deltaT;
					f_bolusOut = 0;
				}
			} else {
				f_basalOut = k_maxOutputRate / k_secPerHour * deltaT;
				f_bolusOut = 0;
			}
		} else {
			if ( BolusIsActive() ){
				if( f_activeBolus.Amount > ( k_maxOutputRate / k_secPerHour ) * deltaT ){
					f_basalOut = 0;
					f_bolusOut = ( k_maxOutputRate / k_secPerHour ) * deltaT;
				} else {
					f_basalOut = 0;
					f_bolusOut = f_activeBolus.Amount;
				}
			} else {
				f_basalOut = 0;
				f_bolusOut = 0;
			}
		}
	} else {
		f_basalOut = 0;
		f_bolusOut = 0;
	}


	//f_activeBolus.Amount -= f_bolusOut;

}

int GetCurrentInsulinOutput(){
	//f_activeBolus.Amount -= f_bolusOut;
	return f_basalOut + f_bolusOut;
}

void ClearCurrentInsulinOutputs(){
	f_basalOut = 0;
	f_bolusOut = 0;
}
