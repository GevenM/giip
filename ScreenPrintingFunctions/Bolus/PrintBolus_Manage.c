#include "!PrintBolus_Master.h"
#include "DisplayOut.h"

void PrintBolus_Manage( tContext *context, y_menus f_menuChoice ){
	char outString[32];
	unsigned char text_start = 18;

	// Draw top and bottom banner and buttons
	LoadLeftButton("BACK");
	LoadMiddleButton("SEL");
	//LoadRightButton("");


	// Menu options
	GrStringDraw(context, "Create Preset", AUTO_STRING_LENGTH, 5, 18, OPAQUE_TEXT);
	GrStringDraw(context, "Remove Preset", AUTO_STRING_LENGTH, 5, 31, OPAQUE_TEXT);


	// Highlight selected item
	switch (f_menuChoice) {
	case Bolus_Manage_Create:
		text_start = 18;
		strcpy(outString, "Create Preset");
		break;
	case Bolus_Manage_Remove:
		text_start = 31;
		strcpy(outString, "Remove Preset");
		break;
	default: break;
	}

	GrContextForegroundSet(context, ClrWhite); //ClrBlack       this affects the highlight color
	GrContextBackgroundSet(context, ClrBlack);    //ClrWhite      this affects the text color in the highlight
	GrStringDraw(context, outString, AUTO_STRING_LENGTH, 5, text_start, OPAQUE_TEXT);
	GrContextForegroundSet(context, ClrBlack);
	GrContextBackgroundSet(context, ClrWhite);
}
