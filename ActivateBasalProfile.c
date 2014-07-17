#include "ActivateBasalProfile.h"

y_basal p_basActSelected;
bool F_startBasal; // From NL expression [ Start Basal ]

void StartBasalProfile(y_basal *profile);

void ActivateBasalProfile(){
	if (c_operation == StartBasProf){
		switch(c_basStartStatus){
		case e_opStatus_idle:
			if (M_basActSelected){
				if (ActivateBasalProfileIsValid( &m_basActSelected )){
					c_basStartStatus = e_opStatus_confirm;
					F_startBasal = false;
					CopyProfile(&m_basActSelected, &p_basActSelected);
				} else {
					c_basStartStatus = e_opStatus_invalid;
					F_startBasal = false;
				}
			} else {
				F_startBasal = false;
			}
			break;

		case e_opStatus_confirm:
			if(M_basStartResp == ACCEPT){
				c_basStartStatus = e_opStatus_idle;
				F_startBasal = true;
				StartBasalProfile(&p_basActSelected);
				CopyProfile(&k_emptyBas, &p_basActSelected);

			} else if (M_basStartResp == RETRY){
				c_basStartStatus = e_opStatus_idle;
				F_startBasal = false;
				CopyProfile(&k_emptyBas, &p_basActSelected);

			} else if (M_basStartResp == CANCEL){
				c_basStartStatus = e_opStatus_idle;
				F_startBasal = false;
				CopyProfile(&k_emptyBas, &p_basActSelected);

			}
			break;

		case e_opStatus_invalid:
			if(M_basStartResp == ACCEPT){
				c_basStartStatus = e_opStatus_idle;
				F_startBasal = false;
				CopyProfile(&k_emptyBas, &p_basActSelected);

			} else if (M_basStartResp == RETRY){
				c_basStartStatus = e_opStatus_idle;
				F_startBasal = false;
				CopyProfile(&k_emptyBas, &p_basActSelected);

			} else {
				F_startBasal = false;

			}
			break;
		}
	} else {
		F_startBasal = false;
		CopyProfile(&k_emptyBas, &p_basActSelected);
	}
}

void StartBasalProfile(y_basal *profile){
	CopyProfile(profile, &f_activeBasal);
}

bool BasalProfileActivationCompleted(){
	if ( F_startBasal || M_basStartResp == CANCEL ){
		return true;
	}
	return false;
}
