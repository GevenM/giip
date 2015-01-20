#include "!PrintError_Master.h"
#include "SafetyStatus.h"

void PrintError( tContext *context ){
    // Draw top and bottom banner and buttons
	//LoadLeftButton( context , "BACK");

	//LoadRightButton("");

	// Menu options
	GrStringDrawCentered(context, "ALARM:", AUTO_STRING_LENGTH, 47, 31, OPAQUE_TEXT);

	if (OcclusionDetected()){
		LoadMiddleButton(context, "OK");
		GrStringDrawCentered(context, "Blockage Detected", AUTO_STRING_LENGTH, 47, 44, OPAQUE_TEXT);
		GrStringDrawCentered(context, "Remove Blockage", AUTO_STRING_LENGTH, 47, 57, OPAQUE_TEXT);
		GrStringDrawCentered(context, "then press OK", AUTO_STRING_LENGTH, 47, 70, OPAQUE_TEXT);

	} else if (BubbleDetected()){
		LoadMiddleButton(context, "OK");
		GrStringDrawCentered(context, "Bubble Detected", AUTO_STRING_LENGTH, 47, 44, OPAQUE_TEXT);
		GrStringDrawCentered(context, "Remove Bubble", AUTO_STRING_LENGTH, 47, 57, OPAQUE_TEXT);
		GrStringDrawCentered(context, "then press OK", AUTO_STRING_LENGTH, 47, 70, OPAQUE_TEXT);

	} else if ( GetSafetyStatus() == e_emptyReservoir ){
		LoadMiddleButton(context, "FILL");
		GrStringDrawCentered(context, "Insulin Empty", AUTO_STRING_LENGTH, 47, 44, OPAQUE_TEXT);
		GrStringDrawCentered(context, "Press Fill", AUTO_STRING_LENGTH, 47, 57, OPAQUE_TEXT);
		GrStringDrawCentered(context, "to refill now", AUTO_STRING_LENGTH, 47, 70, OPAQUE_TEXT);
	}
}
