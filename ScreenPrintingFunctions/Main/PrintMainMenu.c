#include "!Main_Master.h"
#include "DisplayOut.h"

void PrintMainMenu( tContext *context, y_menus f_menuChoice ){
    char outString[32];
    unsigned char text_start = 18;

    // Draw bottom buttons
	LoadLeftButton("BACK");
	LoadMiddleButton("SEL");
	//LoadRightButton("");


	// Menu options
	GrStringDraw( context, "Basal Menu", AUTO_STRING_LENGTH, 5, 18, OPAQUE_TEXT);
	GrStringDraw( context, "Bolus Menu", AUTO_STRING_LENGTH, 5, 31, OPAQUE_TEXT);
	GrStringDraw( context, "Reminder", AUTO_STRING_LENGTH, 5, 44, OPAQUE_TEXT);
	GrStringDraw( context, "Settings", AUTO_STRING_LENGTH, 5, 57, OPAQUE_TEXT);
	GrStringDraw( context, "Shut Down", AUTO_STRING_LENGTH, 5, 70, OPAQUE_TEXT);


    // Highlight selected item
    switch (f_menuChoice) {
    case Basal:
        text_start = 18;
        strcpy(outString, "Basal Menu");
        break;
    case Bolus:
        text_start = 31;
        strcpy(outString, "Bolus Menu");
        break;
    case Reminder:
        text_start = 44;
        strcpy(outString, "Reminder");
        break;
    case Settings:
        text_start = 57;
        strcpy(outString, "Settings");
        break;
    case ShutDown:
        text_start = 70;
        strcpy(outString, "Shut Down");
        break;

    default: break;
    }

    GrContextForegroundSet( context, ClrWhite); //ClrBlack       this affects the highlight color
    GrContextBackgroundSet( context, ClrBlack);    //ClrWhite      this affects the text color in the highlight
    GrStringDraw( context, outString, AUTO_STRING_LENGTH, 5, text_start, OPAQUE_TEXT);
	GrContextForegroundSet( context, ClrBlack);
	GrContextBackgroundSet( context, ClrWhite);

}
