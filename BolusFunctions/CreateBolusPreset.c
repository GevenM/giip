#include "BolusFunctions.h"

#include "Shared.h"
#include "MonitoredVariables.h"
#include "BolusPresets.h"


y_bolus p_bolus;

y_bolus GetBolusToCreate(){
	return p_bolus;
}


void CreateBolusPreset(){
	if (c_operation == e_operation_createBolusPreset){
		switch(c_bolCreateStatus){
		case e_opStatus_idle:
			if(M_bolus){
				if ( BolusIsValid(&m_bolus) ){
					c_bolCreateStatus = e_opStatus_confirm;
					CopyPreset(&m_bolus, &p_bolus);
					//F_createBolusPreset = false;
				} else {
					c_bolCreateStatus = e_opStatus_invalid;
				//	F_createBolusPreset = false;
				}
			}
			else {
				;//F_createBolusPreset = false;
			}
			break;

		case e_opStatus_confirm:
			if ( M_bolCreateResp == e_response_accept ){
				c_bolCreateStatus = e_opStatus_idle;
				F_createBolusPreset = true;
				CopyPreset( &p_bolus, &F_bolusPresetToCreate );
				CopyPreset( &k_emptyBol, &p_bolus );

			} else if( M_bolCreateResp == e_response_retry ){
				c_bolCreateStatus = e_opStatus_idle;
				//F_createBolusPreset = false;
				CopyPreset( &k_emptyBol, &p_bolus );

			} else if ( M_bolCreateResp == e_response_cancel ){
				c_bolCreateStatus = e_opStatus_idle;
			//	F_createBolusPreset = false;
				CopyPreset( &k_emptyBol, &p_bolus );
			}

			break;
		case e_opStatus_invalid:
			if( M_bolCreateResp == e_response_retry ){
				c_bolCreateStatus = e_opStatus_idle;
				//F_createBolusPreset = false;
				CopyPreset( &k_emptyBol, &p_bolus );

			} else if ( M_bolCreateResp == e_response_cancel ){
				c_bolCreateStatus = e_opStatus_idle;
				//F_createBolusPreset = false;
				CopyPreset( &k_emptyBol, &p_bolus );

			} else {
				;//F_createBolusPreset = false;
			}
			break;

		default: break;

		}
	} else {
	//	F_createBolusPreset = false;
		CopyPreset( &k_emptyBol, &p_bolus );
	}
}
