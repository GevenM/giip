#include "!PrintTmpBas_Master.h"
#include "DisplayOut.h"

void PrintStopTmpBas_All(tContext *context){
	GrStringDrawCentered(context, "Stop" , AUTO_STRING_LENGTH, 46, 20, OPAQUE_TEXT);
	GrStringDrawCentered(context, "Temporary" , AUTO_STRING_LENGTH, 46, 30, OPAQUE_TEXT);
	GrStringDrawCentered(context, "Basal?" , AUTO_STRING_LENGTH, 46, 40, OPAQUE_TEXT);

	LoadLeftButton( context , "CANC");
	LoadMiddleButton( context , "OK");
}
