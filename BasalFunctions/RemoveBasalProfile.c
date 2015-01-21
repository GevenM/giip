 #include "BasalFunctions.h"

y_basal p_basRemSelected;


void RemoveBasalProfile(){
	if (c_operation == e_operation_removeBasProf){
		switch(c_basRemStatus){
		case e_opStatus_idle:
			if (M_basRemSelected){
				if(!SelectedBasalProfileIsActive(&m_basRemSelected)){
					c_basRemStatus = e_opStatus_confirm;
					//F_removeBasalProfile = false;
					CopyProfile(&m_basRemSelected, &p_basRemSelected);
				}
				else {
					c_basRemStatus = e_opStatus_invalid;
					//F_removeBasalProfile = false;
				}
			} else {
				;//F_removeBasalProfile = false;
			}
			break;

		case e_opStatus_confirm:
			if (M_basRemResp == e_response_accept){
				c_basRemStatus = e_opStatus_idle;
				F_removeBasalProfile = true;
				CopyProfile( &p_basRemSelected, &F_basalProfileToRemove );
				//RemoveProfileFromSet(&p_basRemSelected);
				CopyProfile( &k_emptyBas, &p_basRemSelected );

			} else if( M_basRemResp == e_response_retry){
				c_basRemStatus = e_opStatus_idle;
				//F_removeBasalProfile = false;
				CopyProfile(&k_emptyBas, &p_basRemSelected);

			} else if (M_basRemResp == e_response_cancel){
				c_basRemStatus = e_opStatus_idle;
				//F_removeBasalProfile = false;
				CopyProfile(&k_emptyBas, &p_basRemSelected);

			}
			break;

		case e_opStatus_invalid:
			if(M_basRemResp == e_response_retry){
				c_basRemStatus = e_opStatus_idle;
				//F_removeBasalProfile = false;
				CopyProfile(&k_emptyBas, &p_basRemSelected);

			} else if (M_basRemResp == e_response_cancel){
				c_basRemStatus = e_opStatus_idle;
				//F_removeBasalProfile = false;
				CopyProfile(&k_emptyBas, &p_basRemSelected);

			} else {
				;//F_removeBasalProfile = false;
			}

			break;
		default: break;
		}
	} else {
		//F_removeBasalProfile = false;
		CopyProfile(&k_emptyBas, &p_basRemSelected);
	}
}
