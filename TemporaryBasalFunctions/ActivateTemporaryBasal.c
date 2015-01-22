#include "TemporaryBasalFunctions.h"

y_tmpBasal p_tmpBas;

void ActivateTemporaryBasal(){
	if (c_operation == e_operation_startTmpBas) {
		switch (c_tmpStartStatus) {
		case e_opStatus_idle:
			if (M_tmpStartResp == e_response_cancel) {
				c_tmpStartStatus = e_opStatus_idle;
				//F_activateTemporaryBasal = false;
				CopyTmpBasal(&k_emptyTmp, &p_tmpBas);
			}
			else {
				if (M_tmpBas) {
					if (TemporaryBasalIsValid( &m_tmpBas )) {
						c_tmpStartStatus = e_opStatus_confirm;
						CopyTmpBasal(&m_tmpBas, &p_tmpBas);
						//F_activateTemporaryBasal = false;
					}
					else {
						c_tmpStartStatus = e_opStatus_invalid;
						//F_activateTemporaryBasal = false;
					}
				}
				else {
					;//F_activateTemporaryBasal = false;
				}

			}
			break;

		case e_opStatus_confirm:
			if ( M_tmpStartResp == e_response_accept ){
					c_tmpStartStatus = e_opStatus_idle;
					F_startTmpBasal = true;
					CopyTmpBasal( &p_tmpBas, &F_tmpBasalToStart );
					CopyTmpBasal( &k_emptyTmp, &p_tmpBas );

				} else if(M_tmpStartResp == e_response_retry ){
					c_tmpStartStatus = e_opStatus_idle;
					//F_activateTemporaryBasal = false;
					CopyTmpBasal(&k_emptyTmp, &p_tmpBas);

				} else if (M_tmpStartResp == e_response_cancel ){
					c_tmpStartStatus = e_opStatus_idle;
				//	F_activateTemporaryBasal = false;
					CopyTmpBasal(&k_emptyTmp, &p_tmpBas);
				}
				break;

		case e_opStatus_invalid:
			if(M_tmpStartResp == e_response_retry ){
					c_tmpStartStatus = e_opStatus_idle;
					//F_activateTemporaryBasal = false;
					CopyTmpBasal(&k_emptyTmp, &p_tmpBas);

				} else if (M_tmpStartResp == e_response_cancel ){
					c_tmpStartStatus = e_opStatus_idle;
					//F_activateTemporaryBasal = false;
					CopyTmpBasal(&k_emptyTmp, &p_tmpBas);

				} else {
				;//	F_activateTemporaryBasal = false;
				}
				break;
		default: break;
		}
	} else {
		//F_activateTemporaryBasal = false;
		CopyTmpBasal(&k_emptyTmp, &p_tmpBas);
	}
}




