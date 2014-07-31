#include "!PrintBasal_Master.h"
#include "DisplayOut.h"

void PrintStopBas_All(tContext *context){
	GrStringDrawCentered(context, "Stop Profile?" , AUTO_STRING_LENGTH, 46, 20, OPAQUE_TEXT);
	GrStringDrawCentered(context, f_activeBasal.Name , AUTO_STRING_LENGTH, 46, 30, OPAQUE_TEXT);

	LoadLeftButton("CANC");
	LoadMiddleButton("OK");
}
