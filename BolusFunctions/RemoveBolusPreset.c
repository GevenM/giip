#include "BolusFunctions.h"

y_bolus p_bolRemSelected;


void RemoveBolusPreset(){
	if (c_operation == e_operation_removeBolusPreset){
		switch(c_bolRemStatus){
		case e_opStatus_idle:
			if (M_bolSelected){
				c_bolRemStatus = e_opStatus_confirm;
				//F_removeBolusPreset = false;
				CopyPreset( &m_bolSelected, &p_bolRemSelected );

			} else {
				;//F_removeBolusPreset = false;
			}
			break;

		case e_opStatus_confirm:
			if ( M_bolRemResp == e_response_accept ){
				c_bolRemStatus = e_opStatus_idle;
				F_removeBolusPreset = true;
				CopyPreset( &p_bolRemSelected, &F_bolusPresetToRemove );
				//RemovePresetFromSet( &p_bolRemSelected );
				CopyPreset( &k_emptyBol, &p_bolRemSelected );

			} else if( M_bolRemResp == e_response_retry){
				c_bolRemStatus = e_opStatus_idle;
			//	F_removeBolusPreset = false;
				CopyPreset( &k_emptyBol, &p_bolRemSelected );

			} else if (M_bolRemResp == e_response_cancel){
				c_bolRemStatus = e_opStatus_idle;
			//	F_removeBolusPreset = false;
				CopyPreset( &k_emptyBol, &p_bolRemSelected );

			}
			break;

		default: break;
		}
	} else {
		//F_removeBolusPreset = false;
		CopyPreset( &k_emptyBol, &p_bolRemSelected );
	}
}




