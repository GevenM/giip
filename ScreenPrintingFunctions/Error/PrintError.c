#include "!PrintError_Master.h"
#include "SafetyStatus.h"

void PrintError( tContext *context ){
    // Draw top and bottom banner and buttons
	//LoadLeftButton( context , "BACK");
	LoadMiddleButton(context, "OK");
	//LoadRightButton("");

	// Menu options
	GrStringDrawCentered(context, "ALARM:", AUTO_STRING_LENGTH, 47, 31, OPAQUE_TEXT);

	if (OcclusionDetected()){
		GrStringDrawCentered(context, "Blockage Detected", AUTO_STRING_LENGTH, 47, 44, OPAQUE_TEXT);
		GrStringDrawCentered(context, "Remove Blockage", AUTO_STRING_LENGTH, 47, 57, OPAQUE_TEXT);
		GrStringDrawCentered(context, "then press OK", AUTO_STRING_LENGTH, 47, 70, OPAQUE_TEXT);

	} else if (BubbleDetected()){
		GrStringDrawCentered(context, "Bubble Detected", AUTO_STRING_LENGTH, 47, 44, OPAQUE_TEXT);
		GrStringDrawCentered(context, "Remove Bubble", AUTO_STRING_LENGTH, 47, 57, OPAQUE_TEXT);
		GrStringDrawCentered(context, "then press OK", AUTO_STRING_LENGTH, 47, 70, OPAQUE_TEXT);
	}
}
