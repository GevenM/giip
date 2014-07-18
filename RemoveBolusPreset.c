#include "RemoveBolusPreset.h"



bool F_removeBolusPreset; // from NL expression [Remove Basal Profile]
y_bolus p_bolRemSelected;


void RemoveBolusPreset(){
	if (c_operation == RemoveBolPre){
		switch(c_bolRemStatus){
		case e_opStatus_idle:
			if (M_bolSelected){
				if(!BolusPresetIsActive( &m_bolSelected )){
					c_bolRemStatus = e_opStatus_confirm;
					F_removeBolusPreset = false;
					CopyBolusPreset( &m_bolSelected, &p_bolRemSelected );
				}
				else {
					c_bolRemStatus = e_opStatus_invalid;
					F_removeBolusPreset = false;
				}
			} else {
				F_removeBolusPreset = false;
			}
			break;

		case e_opStatus_confirm:
			if ( M_bolRemResp == ACCEPT ){
				c_bolRemStatus = e_opStatus_idle;
				F_removeBolusPreset = true;
				RemovePresetFromSet( &p_bolRemSelected );
				CopyBolusPreset( &k_emptyBol, &p_bolRemSelected );

			} else if( M_bolRemResp == RETRY){
				c_bolRemStatus = e_opStatus_idle;
				F_removeBolusPreset = false;
				CopyBolusPreset( &k_emptyBol, &p_bolRemSelected );

			} else if (M_bolRemResp == CANCEL){
				c_bolRemStatus = e_opStatus_idle;
				F_removeBolusPreset = false;
				CopyBolusPreset( &k_emptyBol, &p_bolRemSelected );

			}
			break;

		case e_opStatus_invalid:
			if(M_bolRemResp == RETRY){
				c_bolRemStatus = e_opStatus_idle;
				F_removeBolusPreset = false;
				CopyBolusPreset( &k_emptyBol, &p_bolRemSelected );

			} else if (M_bolRemResp == CANCEL){
				c_bolRemStatus = e_opStatus_idle;
				F_removeBolusPreset = false;
				CopyBolusPreset( &k_emptyBol, &p_bolRemSelected );

			} else {
				F_removeBolusPreset = false;
			}

			break;
		default: break;
		}
	} else {
		F_removeBolusPreset = false;
		CopyBolusPreset( &k_emptyBol, &p_bolRemSelected );
	}
}

bool BolusPresetRemovalCompleted(){
	if (F_removeBolusPreset || M_bolRemResp == CANCEL){
		F_removeBolusPreset = false;
		return true;
	}

	return false;
}


