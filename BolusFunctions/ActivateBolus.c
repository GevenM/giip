#include "BolusFunctions.h"

y_bolus p_interBol;

y_bolus GetBolusToActivate (){
	return p_interBol;
}

void ActivateBolus(){
	if (c_operation == e_operation_startBolus){
		switch(c_bolStartStatus){
		case e_bolStatus_idle:
			switch( M_selectedMethod ){
			case e_bolMethod_calculator:
				c_bolStartStatus = e_bolStatus_calculator;
				//F_startBolus = false;
				break;

			case e_bolMethod_preset:
				c_bolStartStatus = e_bolStatus_preset;
				//F_startBolus = false;
				break;

			case e_bolMethod_manual:
				c_bolStartStatus = e_bolStatus_manual;
				//F_startBolus = false;
				break;

			default: break;
			}
			break;

		case e_bolStatus_calculator:
			if ( M_bloodGlucose && M_carbs ) {
				if ( CalculatedBolusIsValid( &m_bloodGlucose, &m_carbs )){
					c_bolStartStatus = e_bolStatus_confirm;
					//F_startBolus = false;
					p_interBol = CalculatedBolus( &m_bloodGlucose, &m_carbs ); // calculates bolus and puts it into p_interBol
				} else {
					c_bolStartStatus = e_bolStatus_invalid;
					CopyPreset( &p_interBol, &F_bolusToStart ); // added from req because p_interBol was written to in order to check the validity.
					//F_startBolus = false;
				}
			} else if( M_bolStartResp == e_response_retry ){
				c_bolStartStatus = e_bolStatus_idle;
				//F_startBolus = false;
			} else if( M_bolStartResp == e_response_cancel ){
				c_bolStartStatus = e_bolStatus_idle;
				//F_startBolus = false;
			} else {
				;//F_startBolus = false;
			}
			break;

		case e_bolStatus_preset:
			if( M_bolSelected ){
				if ( BolusIsValid( &m_bolSelected )){
					c_bolStartStatus = e_bolStatus_confirm;
				//	F_startBolus = false;
					CopyPreset( &m_bolSelected, &p_interBol );
				} else {
					c_bolStartStatus = e_bolStatus_invalid;
				//	F_startBolus = false;
				}
			} else if( M_bolStartResp == e_response_retry ){
				c_bolStartStatus = e_bolStatus_idle;
				//F_startBolus = false;
			} else if( M_bolStartResp == e_response_cancel ){
				c_bolStartStatus = e_bolStatus_idle;
			//	F_startBolus = false;
			} else {
				;//F_startBolus = false;
			}
			break;

		case e_bolStatus_manual:
			if( M_bolus ){
				if ( BolusIsValid( &m_bolus )){
					c_bolStartStatus = e_bolStatus_confirm;
				//	F_startBolus = false;
					CopyPreset( &m_bolus, &p_interBol );
				} else {
					c_bolStartStatus = e_bolStatus_invalid;
				//	F_startBolus = false;
				}
			} else if( M_bolStartResp == e_response_retry ){
				c_bolStartStatus = e_bolStatus_idle;
			//	F_startBolus = false;
			} else if( M_bolStartResp == e_response_cancel ){
				c_bolStartStatus = e_bolStatus_idle;
				//F_startBolus = false;
			} else {
			;//	F_startBolus = false;
			}
			break;

		case e_bolStatus_confirm:
			if( M_bolStartResp == e_response_accept ){
				c_bolStartStatus = e_bolStatus_idle;
				F_startBolus = true;
				CopyPreset( &p_interBol, &F_bolusToStart );
				//StartBolus( &p_interBol );
			} else if( M_bolStartResp == e_response_retry ){
				c_bolStartStatus = e_bolStatus_idle;
			//	F_startBolus = false;
			} else if( M_bolStartResp == e_response_cancel ){
				c_bolStartStatus = e_bolStatus_idle;
				//F_startBolus = false;
			} else {
				;//F_startBolus = false;
			}
			break;

		case e_bolStatus_invalid:
			if( M_bolStartResp == e_response_retry ){
				c_bolStartStatus = e_bolStatus_idle;
			//	F_startBolus = false;
			} else if( M_bolStartResp == e_response_cancel ){
				c_bolStartStatus = e_bolStatus_idle;
			//	F_startBolus = false;
			} else {
			//	F_startBolus = false;
			}
			break;

		default:
			break;
		}
	} else {
		;//F_startBolus = false;
	}
}
