#include "!PrintBolus_Master.h"
#include "DisplayOut.h"

void PrintBolusCreateNotAllowed( tContext *context ){

	 // Draw top and bottom banner and buttons
	LoadLeftButton("BACK");

	// Menu options
	GrStringDrawCentered(context, "Bolus Preset", AUTO_STRING_LENGTH, 47, 31, OPAQUE_TEXT);
	GrStringDrawCentered(context, "Creation", AUTO_STRING_LENGTH, 47, 44, OPAQUE_TEXT);
	GrStringDrawCentered(context, "not Allowed", AUTO_STRING_LENGTH, 47, 57, OPAQUE_TEXT);

}
