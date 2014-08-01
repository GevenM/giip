#include "!PrintReminder_Master.h"
#include "TriggerReminder.h"
#include "RTC.h"
#include "DisplayOut.h"

void PrintPendingReminder( tContext *context ){

	GPIO_setOutputHighOnPin( GPIO_PORT_P1, GPIO_PIN0);

	char buffer[10] = "";
	char outString[32] = "";
	int digits;

	ClearScreenContent( context );

	y_reminder reminder = GetPendingReminder();

	//GrStringDraw( context, "Reminder:" , AUTO_STRING_LENGTH, 5, 25, OPAQUE_TEXT );

	GrStringDrawCentered( context, "REMINDER" , AUTO_STRING_LENGTH, 46, 20, OPAQUE_TEXT);

	GrStringDraw( context, "Name:" , AUTO_STRING_LENGTH, 3, 30, OPAQUE_TEXT);
	GrStringDraw(context, reminder.Name , AUTO_STRING_LENGTH, 33, 30, OPAQUE_TEXT);


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
	strncat(outString, " - ", 1);

	// Get Day of month
	digits = UnsignedInt_To_ASCII( BCDtoInt( reminder.Time.DayOfMonth ), buffer ); // Read upper half of byte by bitshifting four places
	strncat(outString, buffer, digits);
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

	GrStringDraw(context, outString, AUTO_STRING_LENGTH, 3 , 42, TRANSPARENT_TEXT);



	strcpy(outString, "");

	// split message over as many lines as needed
	if ( strlen( reminder.Message ) < 14){
		GrStringDraw(context, reminder.Message , AUTO_STRING_LENGTH, 3, 56, OPAQUE_TEXT);
	} else if ( strlen( reminder.Message ) < 28 ){
		strcpy( outString, "" );
		strncat( outString, reminder.Message, 14 );
		if ( reminder.Message[13] != 32 && reminder.Message[14] != 32 && strlen( reminder.Message ) > 14){
			strncat( outString, "-", 1 );
		}

		GrStringDraw( context, outString , AUTO_STRING_LENGTH, 3, 56, OPAQUE_TEXT);

		strcpy( outString, "" );
		strcat( outString, reminder.Message + 14 );
		GrStringDraw(context, outString , AUTO_STRING_LENGTH, 3, 66, OPAQUE_TEXT);
	}

	LoadMiddleButton(  context , "OK" );
}
