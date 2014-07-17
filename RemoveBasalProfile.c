#include "RemoveBasalProfile.h"



bool F_removeBasalProfile; // from NL expression [Remove Basal Profile]
unsigned char *p_basRemSelected; // Using index rather than whole profile, discuss?

bool ProfileIsActive(unsigned char profileIndex);

unsigned char *p_basRemSelected;

void RemoveBasalProfile(){
	if (c_operation == RemoveBasProf){
		switch(c_basRemStatus){
		case e_opStatus_idle:
			if (M_basRemSelected){
				if(!ProfileIsActive(m_basRemSelected)){
					c_basRemStatus = e_opStatus_confirm;
					F_removeBasalProfile = false;
					p_basRemSelected = &m_basRemSelected;
				}
				else {
					c_basRemStatus = e_opStatus_invalid;
					F_removeBasalProfile = false;
				}
			} else {
				F_removeBasalProfile = false;
			}
			break;

		case e_opStatus_confirm:
			if (M_basRemResp == ACCEPT){
				c_basRemStatus = e_opStatus_idle;
				F_removeBasalProfile = true;
				RemoveProfileFromSet(*p_basRemSelected);
				*p_basRemSelected = 0;

			} else if( M_basRemResp == RETRY){
				c_basRemStatus = e_opStatus_idle;
				F_removeBasalProfile = false;
				*p_basRemSelected = 0;

			} else if (M_basRemResp == CANCEL){
				c_basRemStatus = e_opStatus_idle;
				F_removeBasalProfile = false;
				*p_basRemSelected = 0;

			}
			break;

		case e_opStatus_invalid:
			if(M_basRemResp == RETRY){
				c_basRemStatus = e_opStatus_idle;
				F_removeBasalProfile = false;
				*p_basRemSelected = 0;

			} else if (M_basRemResp == CANCEL){
				c_basRemStatus = e_opStatus_idle;
				F_removeBasalProfile = false;
				*p_basRemSelected = 0;

			} else {
				F_removeBasalProfile = false;
			}

			break;
		default: break;
		}
	} else {
		F_removeBasalProfile = false;
		*p_basRemSelected = 0;
	}
}

bool BasalProfileRemovalCompleted(){
	if (F_removeBasalProfile || M_basRemResp == CANCEL){
		F_removeBasalProfile = false;
		return true;
	}

	return false;
}



bool ProfileIsActive(unsigned char profileIndex){
	return false;
}
