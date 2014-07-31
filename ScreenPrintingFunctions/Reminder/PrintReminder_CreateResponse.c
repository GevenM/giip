#include "!PrintReminder_Master.h"
#include "DisplayOut.h"

void PrintCreateReminder_Idle(tContext *context, char remindEntryIndex, y_reminder reminder, char remindSubIndex){
	int digits = 0, domDigits = 0;
	char buffer[10] = "";
	char outString[32] = "";

	// Clear previous entries from screen
	GrContextForegroundSet(context, ClrWhite);
	GrRectFill(context, &myRectangleScreen);
	GrContextForegroundSet(context, ClrBlack);

	GrStringDraw(context, "Name:" , AUTO_STRING_LENGTH, 3, 16, OPAQUE_TEXT);
	GrStringDraw(context, reminder.Name , AUTO_STRING_LENGTH, 33, 16, OPAQUE_TEXT);


	// Get Day of month
	domDigits = UnsignedInt_To_ASCII( BCDtoInt( reminder.Time.DayOfMonth ), buffer ); // Read upper half of byte by bitshifting four places
	strncpy(outString, buffer, domDigits);
	strncat( outString, "/", 1 );

	// Get Month
	digits = UnsignedInt_To_ASCII( reminder.Time.Month >> 4, buffer );
	strncat( outString, buffer, digits );
	digits = UnsignedInt_To_ASCII( reminder.Time.Month & 0xF, buffer );
	strncat( outString, buffer, digits );
	strncat( outString, "/", 1 );

	// Get Year
	digits = UnsignedInt_To_ASCII( reminder.Time.Year >> 12, buffer );
	strncat(outString, buffer, digits);
	digits = UnsignedInt_To_ASCII( reminder.Time.Year >> 8 & 0xF, buffer );
	strncat(outString, buffer, digits);
	digits = UnsignedInt_To_ASCII( reminder.Time.Year >> 4 & 0xF, buffer );
	strncat(outString, buffer, digits);
	digits = UnsignedInt_To_ASCII( reminder.Time.Year & 0xF, buffer );
	strncat(outString, buffer, digits);

	GrStringDraw(context, "Date:" , AUTO_STRING_LENGTH, 3, 36, OPAQUE_TEXT);
	GrStringDraw(context, outString, AUTO_STRING_LENGTH, 33 , 36, TRANSPARENT_TEXT);


	// Get Hours
	strcpy(outString, "");
	digits = UnsignedInt_To_ASCII( reminder.Time.Hours >> 4, buffer ); // Read upper half of byte by bitshifting four places
	strncat(outString, buffer, digits);
	digits = UnsignedInt_To_ASCII( reminder.Time.Hours & 0xF, buffer ); // Read lower half of byte by overwriting the upper half with 0s
	strncat(outString, buffer, digits);
	strncat(outString, ":", 1);

	// Get Minutes
	digits = UnsignedInt_To_ASCII( reminder.Time.Minutes >> 4, buffer );
	strncat(outString, buffer, digits);
	digits = UnsignedInt_To_ASCII( reminder.Time.Minutes & 0xF, buffer );
	strncat(outString, buffer, digits);
//	strncat(outString, ":", 1);

	// Get Seconds
//	digits = UnsignedInt_To_ASCII( reminder.Time.Seconds >> 4, buffer );
//	strncat(outString, buffer, digits);
//	digits = UnsignedInt_To_ASCII( reminder.Time.Seconds & 0xF, buffer );
//	strncat(outString, buffer, digits);

	GrStringDraw(context, "Time:" , AUTO_STRING_LENGTH, 3, 26, OPAQUE_TEXT);
	GrStringDraw(context, outString, AUTO_STRING_LENGTH, 33 , 26, OPAQUE_TEXT);



	strcpy(outString, "");
	switch ( reminder.Frequency ){
	case e_remindFreq_oneTime: strcpy( outString, "One Time" ); break;
	case e_remindFreq_daily: strcpy( outString, "Daily" ); break;
	case e_remindFreq_weekly: strcpy( outString, "Weekly" ); break;
	case e_remindFreq_weekdays: strcpy( outString, "Weekdays" ); break;
	case e_remindFreq_weekends: strcpy( outString, "Weekends" ); break;
	default: break;
	}

	GrStringDraw(context, "Freq:" , AUTO_STRING_LENGTH, 3, 46, OPAQUE_TEXT);
	GrStringDraw(context, outString, AUTO_STRING_LENGTH, 33 , 46, OPAQUE_TEXT);

	GrStringDraw(context, "Msg:" , AUTO_STRING_LENGTH, 3, 56, OPAQUE_TEXT);

	// split message over as many lines as needed
	if ( strlen( reminder.Message ) < 10){
		GrStringDraw(context, reminder.Message , AUTO_STRING_LENGTH, 30, 56, OPAQUE_TEXT);
	} else if ( strlen( reminder.Message ) < 25 ){
		strcpy( outString, "" );
		strncat( outString, reminder.Message, 10 );
		if ( reminder.Message[9] != 32 && reminder.Message[10] != 32 && strlen( reminder.Message ) > 10){
			strncat( outString, "-", 1 );
		}

		GrStringDraw(context, outString , AUTO_STRING_LENGTH, 30, 56, OPAQUE_TEXT);

		strcpy( outString, "" );
		strcat( outString, reminder.Message + 10 );
		GrStringDraw(context, outString , AUTO_STRING_LENGTH, 3, 66, OPAQUE_TEXT);

	}



	/* Draw Cursor */
	int cursorY, cursorX, cursorW;
	switch ( remindEntryIndex ){
	case NAME: 							cursorX = 27 + strlen( reminder.Name ) * 6;	cursorY = 24; 	cursorW = 4; 	break;
	case DATETIME:
		switch ( remindSubIndex ){
		//case SEC:						cursorX = 69;	cursorY = 34; 	cursorW = 10; 	break;
		case MIN:						cursorX = 51;	cursorY = 34; 	cursorW = 10; 	break;
		case HR:						cursorX = 33;	cursorY = 34; 	cursorW = 10; 	break;
		case DOM:						cursorX = 33;	cursorY = 44; 	cursorW = 10; 	break;
		case MON: 						cursorX = 51;	cursorY = 44; 	cursorW = 10; 	break;
		case YEAR_1:					cursorX = 69;	cursorY = 44; 	cursorW = 10; 	break;
		case YEAR_2:					cursorX = 80;	cursorY = 44; 	cursorW = 10; 	break;
		}
		break;
	case FREQ: 							cursorX = 33; 	cursorY = 54; 	cursorW = 50;	break;
	case MSG:
		if ( strlen( reminder.Message ) <= 10){
			cursorX = 24 + strlen( reminder.Message ) * 6; 	cursorY = 64; 	cursorW = 4;	break;
		} else if ( strlen( reminder.Message ) < 25 ){
			cursorX = (strlen( reminder.Message )-10) * 6 - 3; 	cursorY = 74; 	cursorW = 4;	break;
		}
	}
	GrLineDrawH(context, cursorX, cursorX+cursorW, cursorY);

	LoadLeftButton( context , "CANC");
	LoadMiddleButton( context , "DONE");
	if( remindEntryIndex == NAME ) LoadRightButton( context , "TIME");
	else if ( remindEntryIndex == MSG ) LoadRightButton( context , "FREQ");
	else ClearRightButton( context );
}

void PrintCreateReminder_Confirm(tContext *context){
	GrStringDraw(context, "Save Reminder?" , AUTO_STRING_LENGTH, 5, 16, OPAQUE_TEXT);

	LoadLeftButton( context , "CANC");
	LoadMiddleButton( context , "OK");
	LoadRightButton( context , "RETY");
}

void PrintCreateReminder_Invalid(tContext *context){

	GrStringDrawCentered(context, "Invalid Reminder" , AUTO_STRING_LENGTH, 46, 20, OPAQUE_TEXT);
	//GrStringDrawCentered(context, m_basActSelected.Name , AUTO_STRING_LENGTH, 46, 30, OPAQUE_TEXT);

	LoadLeftButton( context , "CANC");
	//LoadMiddleButton("OK");
	LoadRightButton( context , "RETY");
}
