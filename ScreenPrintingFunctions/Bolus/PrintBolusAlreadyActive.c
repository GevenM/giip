#include "!PrintBolus_Master.h"
#include "DisplayOut.h"

void PrintBolusAlreadyActive( tContext *context ){
	 // Draw top and bottom banner and buttons
	LoadLeftButton("BACK");

	// Menu options
	GrStringDrawCentered(context, "A bolus", AUTO_STRING_LENGTH, 47, 31, OPAQUE_TEXT);
	GrStringDrawCentered(context, "is already ", AUTO_STRING_LENGTH, 47, 44, OPAQUE_TEXT);
	GrStringDrawCentered(context, "in progress", AUTO_STRING_LENGTH, 47, 57, OPAQUE_TEXT);

}
