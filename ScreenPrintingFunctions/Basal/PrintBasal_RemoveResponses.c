#include "!PrintBasal_Master.h"
#include "DisplayOut.h"

void PrintRemoveBasProf_Confirm(tContext *context){

	GrStringDrawCentered(context, "Remove Profile?" , AUTO_STRING_LENGTH, 46, 20, OPAQUE_TEXT);
	GrStringDrawCentered(context, m_basRemSelected.Name , AUTO_STRING_LENGTH, 46, 30, OPAQUE_TEXT);

	LoadLeftButton("CANC");
	LoadMiddleButton("OK");
	LoadRightButton("RETY");
}

void PrintRemoveBasProf_Invalid(tContext *context){

	GrStringDrawCentered(context, "Profile Active" , AUTO_STRING_LENGTH, 46, 20, OPAQUE_TEXT);
	GrStringDrawCentered(context, "Cannot Remove" , AUTO_STRING_LENGTH, 46, 30, OPAQUE_TEXT);
	//GrStringDrawCentered(context, m_basActSelected.Name , AUTO_STRING_LENGTH, 46, 30, OPAQUE_TEXT);

	LoadLeftButton("CANC");
	//LoadMiddleButton("OK");
	LoadRightButton("RETY");
}
