#include "!PrintSettings_Master.h"
#include "DisplayOut.h"

void  PrintSettings_DateTime(tContext *context, Calendar calendar, unsigned char calendarIndex){
	// Clear previous entries from screen
	GrContextForegroundSet(context, ClrWhite);
	GrRectFill(context, &myRectangleScreen);
	GrContextForegroundSet(context, ClrBlack);

	int digits = 0, domDigits = 0;
	char buffer[10] = "";
	char outString[32] = "";

	/* DRAW TIME */
	strcpy( outString, "Time: " );

	// Get Hours
	digits = UnsignedInt_To_ASCII( calendar.Hours >> 4, buffer ); // Read upper half of byte by bitshifting four places
	strncat(outString, buffer, digits);
	digits = UnsignedInt_To_ASCII( calendar.Hours & 0xF, buffer ); // Read lower half of byte by overwriting the upper half with 0s
	strncat(outString, buffer, digits);
	strncat(outString, ":", 1);

	// Get Minutes
	digits = UnsignedInt_To_ASCII( calendar.Minutes >> 4, buffer );
	strncat(outString, buffer, digits);
	digits = UnsignedInt_To_ASCII( calendar.Minutes & 0xF, buffer );
	strncat(outString, buffer, digits);
	strncat(outString, ":", 1);

	// Get Seconds
	digits = UnsignedInt_To_ASCII( calendar.Seconds >> 4, buffer );
	strncat(outString, buffer, digits);
	digits = UnsignedInt_To_ASCII( calendar.Seconds & 0xF, buffer );
	strncat(outString, buffer, digits);

	GrStringDraw(context, outString, AUTO_STRING_LENGTH, 5 , 40, TRANSPARENT_TEXT);


	/* DRAW DATE */
	strcpy( outString, "Dt: " );

	// Get Day of month
	domDigits = UnsignedInt_To_ASCII( BCDtoInt( calendar.DayOfMonth ), buffer ); // Read upper half of byte by bitshifting four places
	strncat(outString, buffer, domDigits);

	// Get Month
	switch ( BCDtoInt( calendar.Month ) ){
	case 1: strncat(outString, " Jan ", 5); break;
	case 2: strncat(outString, " Feb ", 5); break;
	case 3: strncat(outString, " Mar ", 5); break;
	case 4: strncat(outString, " Apr ", 5); break;
	case 5: strncat(outString, " May ", 5); break;
	case 6: strncat(outString, " Jun ", 5); break;
	case 7: strncat(outString, " Jul ", 5); break;
	case 8: strncat(outString, " Aug ", 5); break;
	case 9: strncat(outString, " Sep ", 5); break;
	case 10:strncat(outString, " Oct ", 5); break;
	case 11:strncat(outString, " Nov ", 5); break;
	case 12:strncat(outString, " Dec ", 5); break;
	default: break;
	}

	// Get Year
	digits = UnsignedInt_To_ASCII( calendar.Year >> 12, buffer );
	strncat(outString, buffer, digits);
	digits = UnsignedInt_To_ASCII( calendar.Year >> 8 & 0xF, buffer );
	strncat(outString, buffer, digits);
	digits = UnsignedInt_To_ASCII( calendar.Year >> 4 & 0xF, buffer );
	strncat(outString, buffer, digits);
	digits = UnsignedInt_To_ASCII( calendar.Year & 0xF, buffer );
	strncat(outString, buffer, digits);



	/* Draw Cursor */
	int cursorY, cursorX, cursorW;
	switch ( calendarIndex ){
	case SEC: 		cursorX = 77; 					cursorY = 48; cursorW = 10;					break;
	case MIN: 		cursorX = 59;				 	cursorY = 48; cursorW = 10;					break;
	case HR: 		cursorX = 41; 					cursorY = 48; cursorW = 10;					break;
	case MON:		cursorX = 35 + (domDigits * 6); cursorY = 63; cursorW = 16;					break;
	case DOM:		cursorX = 29; 					cursorY = 63; cursorW = (domDigits * 5);	break;
	case YEAR_1:	cursorX = 59 + (domDigits * 6); cursorY = 63; cursorW = 10;					break;
	case YEAR_2:	cursorX = 71 + (domDigits * 6); cursorY = 63; cursorW = 10;					break;
	}

	GrLineDrawH(context, cursorX, cursorX+cursorW, cursorY);


	GrStringDraw(context, outString, AUTO_STRING_LENGTH, 5 , 55, TRANSPARENT_TEXT);

	GrStringDrawCentered(context, "Edit Calendar", AUTO_STRING_LENGTH, 46 , 27, TRANSPARENT_TEXT);

	LoadLeftButton("BACK");
	LoadMiddleButton("SET");
}
