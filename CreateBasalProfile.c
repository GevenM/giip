#include "CreateBasalProfile.h"

#define ACCEPT 1
#define RETRY 2
#define CANCEL 3

bool BasalProfileIsValid(y_basal *m_basProf);
bool F_createBasalProfile;
void SaveBasalProfile(y_basal *profile);
y_basal *p_basProf;


void CreateBasalProfile(){
	if (c_operation == CreateBasProf){
		switch(c_basCreateStatus){
		case e_opStatus_idle:
			if(M_basProf){
				if (BasalProfileIsValid(&m_basProf)){
					c_basCreateStatus = e_opStatus_confirm;
					p_basProf = &m_basProf;
				} else {
					c_basCreateStatus = e_opStatus_invalid;
				}
			}
			break;

		case e_opStatus_confirm:
			if (M_basCreateResp == ACCEPT){
				c_basCreateStatus = e_opStatus_idle;
				F_createBasalProfile = true;
				SaveBasalProfile(p_basProf);
				p_basProf = 0;

			} else if(M_basCreateResp == RETRY){
				c_basCreateStatus = e_opStatus_idle;
				p_basProf = 0;

			} else if (M_basCreateResp == CANCEL){
				c_basCreateStatus = e_opStatus_idle;
				p_basProf = 0;
			}

			break;

		case e_opStatus_invalid:
			if(M_basCreateResp == RETRY){
				c_basCreateStatus = e_opStatus_idle;
				p_basProf = 0;

			} else if (M_basCreateResp == CANCEL){
				c_basCreateStatus = e_opStatus_idle;
				p_basProf = 0;

			} else {
				;
			}

			break;
		default: break;
		}
	} else {
		p_basProf = 0;
	}
}

bool BasalProfileCreationCompleted(){
	if (F_createBasalProfile || M_basCreateResp == CANCEL){
		F_createBasalProfile = false;
		return true;
	}
	else if (!(F_createBasalProfile || M_basCreateResp == CANCEL)){
		return false;
	}
	return false;
}

bool BasalProfileIsValid(y_basal *m_basProf){
	return true;
}

void SaveBasalProfile(y_basal *profile){
	;
}
