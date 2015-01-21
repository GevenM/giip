#include "BasalFunctions.h"

y_basal p_basActSelected;

void ActivateBasalProfile(){
	if (c_operation == e_operation_startBasProf){
		switch(c_basStartStatus){
		case e_opStatus_idle:
			if (M_basActSelected){
				if (SelectedBasalProfileIsValid( &m_basActSelected )){
					c_basStartStatus = e_opStatus_confirm;
					//F_startBasal = false;
					CopyProfile(&m_basActSelected, &p_basActSelected);
				} else {
					c_basStartStatus = e_opStatus_invalid;
					//F_startBasal = false;
				}
			} else {
				;//F_startBasal = false;
			}
			break;

		case e_opStatus_confirm:
			if(M_basStartResp == e_response_accept ){
				c_basStartStatus = e_opStatus_idle;
				F_startBasal = true;
				CopyProfile(&p_basActSelected, &F_basalToStart);
				//StartBasalProfile(&p_basActSelected);
				CopyProfile(&k_emptyBas, &p_basActSelected);

			} else if (M_basStartResp == e_response_retry){
				c_basStartStatus = e_opStatus_idle;
				//F_startBasal = false;
				CopyProfile(&k_emptyBas, &p_basActSelected);

			} else if (M_basStartResp == e_response_cancel){
				c_basStartStatus = e_opStatus_idle;
				//F_startBasal = false;
				CopyProfile(&k_emptyBas, &p_basActSelected);

			}
			break;

		case e_opStatus_invalid:
			if(M_basStartResp == e_response_accept){
				c_basStartStatus = e_opStatus_idle;
				//F_startBasal = false;
				CopyProfile(&k_emptyBas, &p_basActSelected);

			} else if (M_basStartResp == e_response_retry){
				c_basStartStatus = e_opStatus_idle;
				//F_startBasal = false;
				CopyProfile(&k_emptyBas, &p_basActSelected);

			} else {
				;//F_startBasal = false;
			}
			break;
		}
	} else {
		//F_startBasal = false;
		CopyProfile(&k_emptyBas, &p_basActSelected);
	}
}
