#include "!PrintSettings_Master.h"
#include "DisplayOut.h"

void  PrintSettings_MotorTest( tContext *context ){
	// Clear previous entries from screen
	GrContextForegroundSet(context, ClrWhite);
	GrRectFill(context, &myRectangleScreen);
	GrContextForegroundSet(context, ClrBlack);

	GrStringDrawCentered(context, "Press LEFT or RIGHT", AUTO_STRING_LENGTH, 46 , 25, TRANSPARENT_TEXT);
	GrStringDrawCentered(context, "to move backward", AUTO_STRING_LENGTH, 46 , 37, TRANSPARENT_TEXT);
	GrStringDrawCentered(context, "or forward. ", AUTO_STRING_LENGTH, 46 , 49, TRANSPARENT_TEXT);
	GrStringDrawCentered(context, "DOWN to stop.", AUTO_STRING_LENGTH, 46 , 61, TRANSPARENT_TEXT);

	LoadLeftButton( context , "BACK");
}
