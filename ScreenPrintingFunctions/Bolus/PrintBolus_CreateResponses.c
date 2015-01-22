#include "!PrintBolus_Master.h"
#include "DisplayOut.h"
#include "BolusFunctions/BolusFunctions.h"


void PrintCreateBolusPreset_Confirm( tContext *context ){
	//char buffer[10] = "";
	//char outString[32] = "";
	//int digits = 0;

	GrContextForegroundSet( context, ClrWhite);
	GrRectFill( context, &myRectangleScreen);
	GrContextForegroundSet( context, ClrBlack);

	GrStringDrawCentered( context, "Save Bolus", AUTO_STRING_LENGTH, 47, 20, OPAQUE_TEXT );
	GrStringDrawCentered( context, "Preset?", AUTO_STRING_LENGTH, 47, 30, OPAQUE_TEXT );

	GrStringDraw( context, "Name: " , AUTO_STRING_LENGTH, 5, 40, OPAQUE_TEXT );


	y_bolus *p_bolusPtr;
	p_bolusPtr = ( y_bolus * ) malloc ( sizeof( y_bolus ));

	*p_bolusPtr = GetBolusToCreate();

	GrStringDraw( context, p_bolusPtr->Name, AUTO_STRING_LENGTH, 15, 50, OPAQUE_TEXT);

	free(p_bolusPtr);
	//digits = UnsignedInt_To_ASCII(m_bolus.Amount / 3600, buffer);
	//strcpy(outString, "Amount: ");
	//strncat(outString, buffer, digits);
	//strncat(outString, " IU", 3);
	//GrStringDraw( context, outString , AUTO_STRING_LENGTH, 5, 65, OPAQUE_TEXT);

	LoadLeftButton( context , "CANC");
	LoadMiddleButton( context , "OK");
	LoadRightButton( context , "RETY");

}

void PrintCreateBolusPreset_Invalid( tContext *context ){
	GrContextForegroundSet( context, ClrWhite);
	GrRectFill( context, &myRectangleScreen);
	GrContextForegroundSet( context, ClrBlack);

	GrStringDrawCentered( context, "Bolus", AUTO_STRING_LENGTH, 47, 37, OPAQUE_TEXT );
	GrStringDrawCentered( context, "Preset", AUTO_STRING_LENGTH, 47, 47, OPAQUE_TEXT );
	GrStringDrawCentered( context, "Invalid", AUTO_STRING_LENGTH, 47, 57, OPAQUE_TEXT );

	LoadLeftButton( context , "CANC");
	LoadRightButton( context , "RETY");

}

void PrintCreateBolusPreset_Idle( tContext *context, y_bolus enteredBolus, bool nameEntered ){

	// Clear previous entries from screen
	GrContextForegroundSet( context, ClrWhite);
	GrRectFill( context, &myRectangleScreen);
	GrContextForegroundSet( context, ClrBlack);

	// Draw name header and user entered name
	GrStringDraw( context, "Preset Name:" , AUTO_STRING_LENGTH, 5, 16, OPAQUE_TEXT);
	GrStringDraw( context, enteredBolus.Name , AUTO_STRING_LENGTH, 5, 26, OPAQUE_TEXT);

	// Draw Amount header and user entered amount
	char buffer[10] = "";
	char outString[32] = "";
	int digits = 0;
	digits = UnsignedInt_To_ASCII( enteredBolus.Amount / 3600, buffer );
	strcpy( outString, "Amount: ");
	strncat( outString, buffer, digits );
	strncat( outString, " IU", 3 );
	GrStringDraw( context, outString, AUTO_STRING_LENGTH, 5, 43, OPAQUE_TEXT );

	// Draw Cursor
	int cursorY, cursorX, cursorW;
	if ( nameEntered == false ){
		cursorY = 35; // y location
		cursorW = 4; // width
		cursorX = ( 6 * strlen( enteredBolus.Name )) - 1; // x location is under last entered letter
	}
	else {
		cursorY = 51;
		cursorX = 53;
		cursorW = digits * 5;
	}
	GrLineDrawH( context, cursorX, cursorX+cursorW, cursorY );

	// Draw Buttons
	LoadLeftButton( context , "CANC");
	LoadMiddleButton( context , "DONE");
	if ( nameEntered == false ) LoadRightButton( context , "AMNT");
	else LoadRightButton( context , "NAME");

}
