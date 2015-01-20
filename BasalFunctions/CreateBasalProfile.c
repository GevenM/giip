#include "CreateBasalProfile.h"


void SaveBasalProfile(y_basal *profile);

bool F_createBasalProfile;
y_basal F_basalProfileToCreate;

bool F_removeBasalProfile;
y_basal F_basalProfileToRemove;

y_basal p_basProf;


//y_basal F_basalProfileToCreate;

void CreateBasalProfile(){
	if ( c_operation == e_operation_createBasProf ){
		switch(c_basCreateStatus){
		case e_opStatus_idle:
			if ( M_basCreateResp == e_response_cancel ){
				c_basCreateStatus = e_opStatus_idle;
				//F_createBasalProfile = false;
				CopyProfile(&k_emptyBas, &p_basProf);
			} else {
				if(M_basProf){
					if (BasalProfileIsValid( &m_basProf )){
						c_basCreateStatus = e_opStatus_confirm;
						CopyProfile(&m_basProf, &p_basProf);
						//F_createBasalProfile = false;
					} else {
						c_basCreateStatus = e_opStatus_invalid;
						//F_createBasalProfile = false;
					}
				}
				else {
					;//F_createBasalProfile = false;
				}
			}
			break;

		case e_opStatus_confirm:
			if ( M_basCreateResp == e_response_accept ){
				c_basCreateStatus = e_opStatus_idle;
				F_createBasalProfile = true;
				CopyProfile(&p_basProf, &F_basalProfileToCreate);
				//SaveBasalProfile(&p_basProf);
				CopyProfile(&k_emptyBas, &p_basProf);

			} else if( M_basCreateResp == e_response_retry ){
				c_basCreateStatus = e_opStatus_idle;
				//F_createBasalProfile = false;
				CopyProfile(&k_emptyBas, &p_basProf);

			} else if ( M_basCreateResp == e_response_cancel ){
				c_basCreateStatus = e_opStatus_idle;
				//F_createBasalProfile = false;
				CopyProfile(&k_emptyBas, &p_basProf);
			}

			break;

		case e_opStatus_invalid:
			if( M_basCreateResp == e_response_retry ){
				c_basCreateStatus = e_opStatus_idle;
				//F_createBasalProfile = false;
				CopyProfile(&k_emptyBas, &p_basProf);

			} else if ( M_basCreateResp == e_response_cancel ){
				c_basCreateStatus = e_opStatus_idle;
				//F_createBasalProfile = false;
				CopyProfile(&k_emptyBas, &p_basProf);

			} else {
				;//F_createBasalProfile = false;
			}

			break;
		default: break;
		}
	} else {
		//F_createBasalProfile = false;
		CopyProfile(&k_emptyBas, &p_basProf);
	}
}

bool BasalProfileCreationCompleted(){
	if (F_createBasalProfile || M_basCreateResp == e_response_cancel ){
		//F_createBasalProfile = false;
		return true;
	}

	return false;
}



void SaveBasalProfile(y_basal *profile){
	AddProfileToSet(profile);
}


void BasalProfileCreation(){
	if ( c_pwrStatus == e_pwrStatus_ready ){
		if( F_createBasalProfile ){
			AddProfileToSet( &F_basalProfileToCreate );
		} else if ( F_removeBasalProfile ){
			RemoveProfileFromSet( &F_basalProfileToRemove );
		} else {
			;
		}
	} else {
		;
	}
}

void ResetFVariables(){
	CopyProfile(&k_emptyBas, &F_basalProfileToCreate);
	F_createBasalProfile = false;
	CopyProfile(&k_emptyBas, &F_basalProfileToRemove);
	F_removeBasalProfile = false;
}
