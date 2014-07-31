#include "!PrintSettings_Master.h"
#include "DisplayOut.h"

void PrintSettings_DateTime_NotAllowed(tContext *context){
	GrStringDrawCentered(context, "Cannot edit", AUTO_STRING_LENGTH, 47, 27, OPAQUE_TEXT);
	GrStringDrawCentered(context, "while insulin", AUTO_STRING_LENGTH, 47, 38, OPAQUE_TEXT);
	GrStringDrawCentered(context, "delivery is", AUTO_STRING_LENGTH, 47, 49, OPAQUE_TEXT);
	GrStringDrawCentered(context, "in progress", AUTO_STRING_LENGTH, 47, 60, OPAQUE_TEXT);

	LoadMiddleButton("OK");
}
