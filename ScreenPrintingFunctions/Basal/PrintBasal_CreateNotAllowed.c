#include "!PrintBasal_Master.h"
#include "DisplayOut.h"

void PrintBasCreateNotAllowed(tContext *context){
    // Draw top and bottom banner and buttons
	LoadLeftButton( context , "BACK");
	//LoadMiddleButton("SEL");
	//LoadRightButton("");


	// Menu options
	GrStringDrawCentered(context, "Basal Profile", AUTO_STRING_LENGTH, 47, 31, OPAQUE_TEXT);
	GrStringDrawCentered(context, "Creation", AUTO_STRING_LENGTH, 47, 44, OPAQUE_TEXT);
	GrStringDrawCentered(context, "not Allowed", AUTO_STRING_LENGTH, 47, 57, OPAQUE_TEXT);
}
