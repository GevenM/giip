#include "!PrintBolus_Master.h"
#include "DisplayOut.h"

void PrintNoBolusPreset( tContext *context ){
	 // Draw top and bottom banner and buttons
	LoadLeftButton("BACK");

	// Menu options
	GrStringDrawCentered( context, "No Bolus", AUTO_STRING_LENGTH, 47, 31, OPAQUE_TEXT);
	GrStringDrawCentered( context, "Presets", AUTO_STRING_LENGTH, 47, 44, OPAQUE_TEXT);
	GrStringDrawCentered( context, "Available", AUTO_STRING_LENGTH, 47, 57, OPAQUE_TEXT);

}
