#include "!PrintBasal_Master.h"
#include "DisplayOut.h"

void PrintNoBasProf(tContext *context){
    // Draw top and bottom banner and buttons
	LoadLeftButton("BACK");
	//LoadMiddleButton("SEL");
	//LoadRightButton("");


	// Menu options
	GrStringDrawCentered(context, "No Basal", AUTO_STRING_LENGTH, 47, 31, OPAQUE_TEXT);
	GrStringDrawCentered(context, "Profile", AUTO_STRING_LENGTH, 47, 44, OPAQUE_TEXT);
	GrStringDrawCentered(context, "Available", AUTO_STRING_LENGTH, 47, 57, OPAQUE_TEXT);
}
