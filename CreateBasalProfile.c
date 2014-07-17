#include "CreateBasalProfile.h"




bool F_createBasalProfile;
void SaveBasalProfile(y_basal *profile);


y_basal *p_basProf;
//y_basal F_basalProfileToCreate;

void CreateBasalProfile(){
	if (c_operation == CreateBasProf){
		switch(c_basCreateStatus){
		case e_opStatus_idle:
			if (M_basCreateResp == CANCEL){
				c_basCreateStatus = e_opStatus_idle;
				F_createBasalProfile = false;
				p_basProf = 0;
			} else {
				if(M_basProf){
					if (BasalProfileIsValid(&m_basProf)){
						c_basCreateStatus = e_opStatus_confirm;
						p_basProf = &m_basProf;
						F_createBasalProfile = false;
					} else {
						c_basCreateStatus = e_opStatus_invalid;
						F_createBasalProfile = false;
					}
				}
				else {
					F_createBasalProfile = false;
				}
			}
			break;

		case e_opStatus_confirm:
			if (M_basCreateResp == ACCEPT){
				c_basCreateStatus = e_opStatus_idle;
				F_createBasalProfile = true;
				//CopyProfile(p_basProf, &F_basalProfileToCreate);
				SaveBasalProfile(p_basProf);
				p_basProf = 0;

			} else if(M_basCreateResp == RETRY){
				c_basCreateStatus = e_opStatus_idle;
				F_createBasalProfile = false;
				p_basProf = 0;

			} else if (M_basCreateResp == CANCEL){
				c_basCreateStatus = e_opStatus_idle;
				F_createBasalProfile = false;
				p_basProf = 0;
			}

			break;

		case e_opStatus_invalid:
			if(M_basCreateResp == RETRY){
				c_basCreateStatus = e_opStatus_idle;
				F_createBasalProfile = false;
				p_basProf = 0;

			} else if (M_basCreateResp == CANCEL){
				c_basCreateStatus = e_opStatus_idle;
				F_createBasalProfile = false;
				p_basProf = 0;

			} else {
				F_createBasalProfile = false;
			}

			break;
		default: break;
		}
	} else {
		F_createBasalProfile = false;
		p_basProf = 0;
	}
}

bool BasalProfileCreationCompleted(){
	if (F_createBasalProfile || M_basCreateResp == CANCEL){
		F_createBasalProfile = false;
		return true;
	}

	return false;
}



void SaveBasalProfile(y_basal *profile){
	AddProfileToSet(profile);
}

