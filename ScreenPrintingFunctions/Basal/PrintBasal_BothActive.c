#include "!PrintBasal_Master.h"
#include "DisplayOut.h"

void PrintBasBothActive(tContext *context, y_menus f_menuChoice){
    char outString[32];
    unsigned char text_start = 18;

    // Draw top and bottom banner and buttons
	LoadLeftButton("BACK");
	LoadMiddleButton("SEL");
	//LoadRightButton("");


	// Menu options
	GrStringDraw(context, "Stop Profile", AUTO_STRING_LENGTH, 5, 18, OPAQUE_TEXT);
	GrStringDraw(context, "Stop Temporary", AUTO_STRING_LENGTH, 5, 31, OPAQUE_TEXT);
	GrStringDraw(context, "Manage Profiles", AUTO_STRING_LENGTH, 5, 44, OPAQUE_TEXT);

    // Highlight selected item
    switch (f_menuChoice) {
    case Basal_StopProfile:
        text_start = 18;
        strcpy(outString, "Stop Profile");
        break;
    case Basal_StopTmp:
        text_start = 31;
        strcpy(outString, "Stop Temporary");
        break;
    case Basal_Manage:
        text_start = 44;
        strcpy(outString, "Manage Profiles");
        break;

    default: break;
    }

    GrContextForegroundSet(context, ClrWhite); //ClrBlack       this affects the highlight color
    GrContextBackgroundSet(context, ClrBlack);    //ClrWhite      this affects the text color in the highlight
    GrStringDraw(context, outString, AUTO_STRING_LENGTH, 5, text_start, OPAQUE_TEXT);
	GrContextForegroundSet(context, ClrBlack);
	GrContextBackgroundSet(context, ClrWhite);
}
