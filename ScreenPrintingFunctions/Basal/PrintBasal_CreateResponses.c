#include "!PrintBasal_Master.h"
#include "DisplayOut.h"

void PrintStartBasProf_Confirm(tContext *context){

	GrStringDrawCentered(context, "Start Profile?" , AUTO_STRING_LENGTH, 46, 20, OPAQUE_TEXT);
	GrStringDrawCentered(context, m_basActSelected.Name , AUTO_STRING_LENGTH, 46, 30, OPAQUE_TEXT);

	LoadLeftButton("CANC");
	LoadMiddleButton("OK");
	LoadRightButton("RETY");
}


void PrintCreateBasProf_Invalid(tContext *context){

	GrStringDrawCentered(context, "Invalid Profile" , AUTO_STRING_LENGTH, 46, 20, OPAQUE_TEXT);
	//GrStringDrawCentered(context, m_basActSelected.Name , AUTO_STRING_LENGTH, 46, 30, OPAQUE_TEXT);

	LoadLeftButton("CANC");
	//LoadMiddleButton("OK");
	LoadRightButton("RETY");
}
