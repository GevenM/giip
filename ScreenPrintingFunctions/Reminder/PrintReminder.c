#include "!PrintReminder_Master.h"
#include "DisplayOut.h"

void PrintReminder(tContext *context, y_menus f_menuChoice){
	char outString[32] = "";
	unsigned char text_start = 18;

	// Draw top and bottom banner and buttons
	LoadLeftButton("BACK");
	LoadMiddleButton("SEL");
	//LoadRightButton("");


	// Menu options
	GrStringDraw(&g_sContext, "Create Reminder", AUTO_STRING_LENGTH, 5, 18, OPAQUE_TEXT);
	GrStringDraw(&g_sContext, "Remove Reminder", AUTO_STRING_LENGTH, 5, 31, OPAQUE_TEXT);


	// Highlight selected item
	switch (f_menuChoice) {
	case Reminder_Create:
		text_start = 18;
		strcpy(outString, "Create Reminder");
		break;
	case Reminder_Remove:
		text_start = 31;
		strcpy(outString, "Remove Reminder");
		break;
	default: break;
	}

	GrContextForegroundSet(context, ClrWhite); //ClrBlack       this affects the highlight color
	GrContextBackgroundSet(context, ClrBlack);    //ClrWhite      this affects the text color in the highlight
	GrStringDraw(context, outString, AUTO_STRING_LENGTH, 5, text_start, OPAQUE_TEXT);
	GrContextForegroundSet(context, ClrBlack);
	GrContextBackgroundSet(context, ClrWhite);

	GrFlush(context);
}
