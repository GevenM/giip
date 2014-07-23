#include "ActivateBolus.h"

bool F_startBolus = false;
y_bolus p_interBol;

void StartBolus(y_bolus *bolus);

void ActivateBolus(){
	if (c_operation == StartBol){
		switch(c_bolStartStatus){
		case e_bolStatus_idle:
			switch( M_selectedMethod ){
			case CALCULATOR:
				c_bolStartStatus = e_bolStatus_calculator;
				F_startBolus = false;
				break;

			case PRESET:
				c_bolStartStatus = e_bolStatus_preset;
				F_startBolus = false;
				break;

			case MANUAL:
				c_bolStartStatus = e_bolStatus_manual;
				F_startBolus = false;
				break;

			default: break;
			}
			break;

		case e_bolStatus_calculator:
			if ( M_bloodGlucose && M_carbs ) {
				if ( CalculatedBolusIsValid( CalculateBolus( m_bloodGlucose, m_carbs ))){
					c_bolStartStatus = e_bolStatus_confirm;
					F_startBolus = false;
					p_interBol = CalculateBolus( m_bloodGlucose, m_carbs ); // calculates bolus and puts it into p_interBol
				} else {
					c_bolStartStatus = e_bolStatus_invalid;
					F_startBolus = false;
				}
			} else if( M_bolStartResp == RETRY ){
				c_bolStartStatus = e_bolStatus_idle;
				F_startBolus = false;
			} else if( M_bolStartResp == CANCEL ){
				c_bolStartStatus = e_bolStatus_idle;
				F_startBolus = false;
			} else {
				F_startBolus = false;
			}
			break;

		case e_bolStatus_preset:
			if( M_bolSelected ){
				if ( BolusIsValid( &m_bolSelected )){
					c_bolStartStatus = e_bolStatus_confirm;
					F_startBolus = false;
					CopyBolusPreset( &m_bolSelected, &p_interBol );
				} else {
					c_bolStartStatus = e_bolStatus_invalid;
					F_startBolus = false;
				}
			} else if( M_bolStartResp == RETRY ){
				c_bolStartStatus = e_bolStatus_idle;
				F_startBolus = false;
			} else if( M_bolStartResp == CANCEL ){
				c_bolStartStatus = e_bolStatus_idle;
				F_startBolus = false;
			} else {
				F_startBolus = false;
			}
			break;

		case e_bolStatus_manual:
			if( M_bolus ){
				if ( BolusIsValid( &m_bolus )){
					c_bolStartStatus = e_bolStatus_confirm;
					F_startBolus = false;
					CopyBolusPreset( &m_bolus, &p_interBol );
				} else {
					c_bolStartStatus = e_bolStatus_invalid;
					F_startBolus = false;
				}
			} else if( M_bolStartResp == RETRY ){
				c_bolStartStatus = e_bolStatus_idle;
				F_startBolus = false;
			} else if( M_bolStartResp == CANCEL ){
				c_bolStartStatus = e_bolStatus_idle;
				F_startBolus = false;
			} else {
				F_startBolus = false;
			}
			break;

		case e_bolStatus_confirm:
			if( M_bolStartResp == ACCEPT ){
				c_bolStartStatus = e_bolStatus_idle;
				F_startBolus = true;
				StartBolus( &p_interBol );
			} else if( M_bolStartResp == RETRY ){
				c_bolStartStatus = e_bolStatus_idle;
				F_startBolus = false;
			} else if( M_bolStartResp == CANCEL ){
				c_bolStartStatus = e_bolStatus_idle;
				F_startBolus = false;
			} else {
				F_startBolus = false;
			}
			break;

		case e_bolStatus_invalid:
			if( M_bolStartResp == RETRY ){
				c_bolStartStatus = e_bolStatus_idle;
				F_startBolus = false;
			} else if( M_bolStartResp == CANCEL ){
				c_bolStartStatus = e_bolStatus_idle;
				F_startBolus = false;
			} else {
				F_startBolus = false;
			}
			break;

		default:
			break;
		}
	} else {
		F_startBolus = false;
	}
}


bool BolusActivationCompleted(){
	if ( F_startBolus || M_bolStartResp == CANCEL ){
		return true;
	}
	return false;
}


void StartBolus(y_bolus *bolus){
	CopyBolusPreset( bolus, &f_activeBolus );
}

// Will put the bolus profile that is to be activated into 'bolus'
// This function can be used by the UI to get details about the profile to activate when requiring the user to confirm activation.
void BolusToActivate(y_bolus *bolus){
	CopyBolusPreset( &p_interBol, bolus );
}

