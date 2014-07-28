#include "CreateBolusPreset.h"

#include "Shared.h"
#include "MonitoredVariables.h"
#include "BolusPresets.h"

bool F_createBolusPreset;
y_bolus p_bolus;


void SaveBolusPreset (y_bolus *preset);


void CreateBolusPreset(){
	if (c_operation == e_operation_createBolusPreset){
		switch(c_bolCreateStatus){
		case e_opStatus_idle:
			if(M_bolus){
				if (EnteredBolusIsValid(&m_bolus)){
					c_bolCreateStatus = e_opStatus_confirm;
					CopyBolusPreset(&m_bolus, &p_bolus);
					F_createBolusPreset = false;
				} else {
					c_bolCreateStatus = e_opStatus_invalid;
					F_createBolusPreset = false;
				}
			}
			else {
				F_createBolusPreset = false;
			}
			break;

		case e_opStatus_confirm:
			if ( M_bolCreateResp == e_response_accept ){
				c_bolCreateStatus = e_opStatus_idle;
				F_createBolusPreset = true;
				SaveBolusPreset( &p_bolus );
				CopyBolusPreset( &k_emptyBol, &p_bolus );

			} else if( M_bolCreateResp == e_response_retry ){
				c_bolCreateStatus = e_opStatus_idle;
				F_createBolusPreset = false;
				CopyBolusPreset( &k_emptyBol, &p_bolus );

			} else if ( M_bolCreateResp == e_response_cancel ){
				c_bolCreateStatus = e_opStatus_idle;
				F_createBolusPreset = false;
				CopyBolusPreset( &k_emptyBol, &p_bolus );
			}

			break;
		case e_opStatus_invalid:
			if( M_bolCreateResp == e_response_retry ){
				c_bolCreateStatus = e_opStatus_idle;
				F_createBolusPreset = false;
				CopyBolusPreset( &k_emptyBol, &p_bolus );

			} else if ( M_bolCreateResp == e_response_cancel ){
				c_bolCreateStatus = e_opStatus_idle;
				F_createBolusPreset = false;
				CopyBolusPreset( &k_emptyBol, &p_bolus );

			} else {
				F_createBolusPreset = false;
			}
			break;

		default: break;

		}
	} else {
		F_createBolusPreset = false;
		CopyBolusPreset( &k_emptyBol, &p_bolus );
	}
}


bool BolusPresetCreationCompleted(){
	if ( F_createBolusPreset || M_bolCreateResp == e_response_cancel ){
		F_createBolusPreset = false;
		return true;
	}

	return false;
}

void SaveBolusPreset (y_bolus *preset){
	AddPresetToSet(preset);
}
