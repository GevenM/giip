#include "ActivateTemporaryBasal.h"

bool F_activateTemporaryBasal;
y_basal p_tmpBas

void ActivateTemporaryBasal(){
		if (c_operation == StartTmpBas) {
			switch (c_tmpStartStatus) {
			case e_opStatus_idle:
				if (M_tmpStartResp == CANCEL) {
					c_tmpStartStatus = e_opStatus_idle;
					F_activateTemporaryBasal = false;
					CopyProfile(&k_emptyBas, &p_tmpBas);
				}
				else {
					if (M_tmpBas) {
						if (ActivateTemporaryBasalIsValid(&m_tmpBas)) {
							c_tmpStartStatus = e_opStatus_confirm;
							CopyProfile(&m_tmpBas, &p_tmpBas);
							F_activateTemporaryBasal = false;
						}
						else {
							c_tmpStartStatus = e_opStatus_invalid;
							F_activateTemporaryBasal = false;
						}
					}
					else {
						F_activateTemporaryBasal = false;
					}

				}
				break;

			case e_opStatus_confirm:
				if (M_tmpStartResp == ACCEPT){
						c_tmpStartStatus = e_opStatus_idle;
						F_activateTemporaryBasal = true;
						ActivateTemporaryBasal(&p_tmpBas);
						CopyProfile(&k_emptyBas, &p_tmpBas);

					} else if(M_basCreateResp == RETRY){
						c_tmpStartStatus = e_opStatus_idle;
						F_activateTemporaryBasal = false;
						CopyProfile(&k_emptyBas, &p_tmpBas);

					} else if (M_basCreateResp == CANCEL){
						c_tmpStartStatus = e_opStatus_idle;
						F_activateTemporaryBasal = false;
						CopyProfile(&k_emptyBas, &p_tmpBas);
					}
					break;

			case e_opStatus_invalid:
				if(M_basCreateResp == RETRY){
						c_tmpStartStatus = e_opStatus_idle;
						F_activateTemporaryBasal = false;
						CopyProfile(&k_emptyBas, &p_tmpBas);

					} else if (M_basCreateResp == CANCEL){
						c_tmpStartStatus = e_opStatus_idle;
						F_activateTemporaryBasal = false;
						CopyProfile(&k_emptyBas, &p_tmpBas);

					} else {
						F_activateTemporaryBasal = false;
					}
					break;
			default: break;
			}
		} else {
			F_activateTemporaryBasal = false;
			CopyProfile(&k_emptyBas, &p_tmpBas);
		}
}

bool ActivateTemporaryBasalIsValid(y_basal *profile){
	int i;
	y_insulinValue basalRateSum = 0;

	for ( i = 0 ; i < k_segDay ; i++ ){ //cycle through all segments or rates
		if ( profile->Rate[i] < k_minBasalBound || profile->Rate[i] > k_maxBasalBound) //each single rate is within allowable bounds
			return false;

		basalRateSum += profile->Rate[i]; //sum all rates to compare to daily max
	}


	if (basalRateSum > k_maxDailyInsulin) //compare sum of rates to daily max
		return false;
	else
		return true;
}

void ActivateTemporaryBasal(y_basal *profile){
	CopyProfile(profile, &f_activeBasal);
}

bool TemporaryBasalActivationCompleted(){
	if (F_activateTemporaryBasal || M_tmpStartResp == CANCEL){
		F_activateTemporaryBasal = false;
		return true;
	}

	return false;
}
