#include "ActivateTemporaryBasal.h"

bool F_activateTemporaryBasal;
y_tmpBasal p_tmpBas;

void StartTemporaryBasal(y_tmpBasal *profile);


void ActivateTemporaryBasal(){
	if (c_operation == StartTmpBas) {
		switch (c_tmpStartStatus) {
		case e_opStatus_idle:
			if (M_tmpStartResp == CANCEL) {
				c_tmpStartStatus = e_opStatus_idle;
				F_activateTemporaryBasal = false;
				CopyTmpBasal(&k_emptyTmp, &p_tmpBas);
			}
			else {
				if (M_tmpBas) {
					if (ActivateTemporaryBasalIsValid(&m_tmpBas)) {
						c_tmpStartStatus = e_opStatus_confirm;
						CopyTmpBasal(&m_tmpBas, &p_tmpBas);
						F_activateTemporaryBasal = false;
					}
					else {
						c_tmpStartStatus = e_opStatus_invalid;
						F_activateTemporaryBasal = false;
					}
				}
				else {
					F_activateTemporaryBasal = false;
				}

			}
			break;

		case e_opStatus_confirm:
			if (M_tmpStartResp == ACCEPT){
					c_tmpStartStatus = e_opStatus_idle;
					F_activateTemporaryBasal = true;
					StartTemporaryBasal(&p_tmpBas);
					CopyTmpBasal(&k_emptyTmp, &p_tmpBas);

				} else if(M_tmpStartResp == RETRY){
					c_tmpStartStatus = e_opStatus_idle;
					F_activateTemporaryBasal = false;
					CopyTmpBasal(&k_emptyTmp, &p_tmpBas);

				} else if (M_tmpStartResp == CANCEL){
					c_tmpStartStatus = e_opStatus_idle;
					F_activateTemporaryBasal = false;
					CopyTmpBasal(&k_emptyTmp, &p_tmpBas);
				}
				break;

		case e_opStatus_invalid:
			if(M_tmpStartResp == RETRY){
					c_tmpStartStatus = e_opStatus_idle;
					F_activateTemporaryBasal = false;
					CopyTmpBasal(&k_emptyTmp, &p_tmpBas);

				} else if (M_tmpStartResp == CANCEL){
					c_tmpStartStatus = e_opStatus_idle;
					F_activateTemporaryBasal = false;
					CopyTmpBasal(&k_emptyTmp, &p_tmpBas);

				} else {
					F_activateTemporaryBasal = false;
				}
				break;
		default: break;
		}
	} else {
		F_activateTemporaryBasal = false;
		CopyTmpBasal(&k_emptyTmp, &p_tmpBas);
	}
}

void StartTemporaryBasal(y_tmpBasal *profile){
	CopyTmpBasal(profile, &f_activeTmpBasal);
}

bool TemporaryBasalActivationCompleted(){
	if (F_activateTemporaryBasal || M_tmpStartResp == CANCEL){
		F_activateTemporaryBasal = false;
		return true;
	}

	return false;
}


