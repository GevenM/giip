#include "!PrintSettings_Master.h"
#include "DisplayOut.h"
#include "TestSettings.h" // Needed for ShowDay Function

void PrintSettings( tContext *context, y_menus f_menuChoice ){
	char outString[32] = "";
	unsigned char text_start = 18;

	// Draw top and bottom banner and buttons
	LoadLeftButton( context , "BACK");
	LoadMiddleButton( context , "SEL");
	//LoadRightButton("");

	//Test Prints to show in settings screen
	ShowDay();

	// Menu options
	GrStringDraw( context, "Clear Flash", AUTO_STRING_LENGTH, 5, 18, OPAQUE_TEXT);
	GrStringDraw( context, "Edit Calendar", AUTO_STRING_LENGTH, 5, 31, OPAQUE_TEXT);
	GrStringDraw( context, "Test Motor", AUTO_STRING_LENGTH, 5, 44, OPAQUE_TEXT);


	// Highlight selected item
	switch (f_menuChoice) {
	case Settings_ClearFlash:
		text_start = 18;
		strcpy(outString, "Clear Flash");
		break;
	case Settings_DateTime:
		text_start = 31;
		strcpy(outString, "Edit Calendar");
		break;
	case Settings_MotorTest:
		text_start = 44;
		strcpy(outString, "Test Motor");
		break;
	default: break;
	}

	GrContextForegroundSet( context, ClrWhite); //ClrBlack       this affects the highlight color
	GrContextBackgroundSet( context, ClrBlack);    //ClrWhite      this affects the text color in the highlight
	GrStringDraw( context, outString, AUTO_STRING_LENGTH, 5, text_start, OPAQUE_TEXT);
	GrContextForegroundSet( context, ClrBlack);
	GrContextBackgroundSet( context, ClrWhite);

	GrFlush( context);
}
