

#include "Shared.h"
#include "BasalProfiles.h"
#include "BolusPresets.h"
#include "TemporaryBasal.h"

unsigned char deltaT = 1; // represents 1 second timestep

y_insulinValue f_basalOut = 0;
y_insulinValue f_bolusOut = 0;

void InsulinOutputCalculator(){
	if ( c_pwrStatus == Ready ){
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
}

