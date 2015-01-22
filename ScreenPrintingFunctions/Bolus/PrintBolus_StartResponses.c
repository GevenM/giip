#include "!PrintBolus_Master.h"
#include "DisplayOut.h"
#include "BolusFunctions/BolusFunctions.h"

void PrintStartBolus_Confirm( tContext *context ){
	// Draw Header
	GrStringDrawCentered( context, "Activate Bolus?", AUTO_STRING_LENGTH, 47, 21, OPAQUE_TEXT);

	// Get names of saved presets and draw them
	y_bolus *bolus;
	bolus = (y_bolus *) malloc( sizeof( y_bolus ));

	// Get the bolus to activate
	*bolus = GetBolusToActivate();

	// Draw bolus name
	GrStringDraw( context, "Name: " , AUTO_STRING_LENGTH, 5, 37, OPAQUE_TEXT);
	GrStringDraw( context, bolus->Name, AUTO_STRING_LENGTH, 15, 47, OPAQUE_TEXT);

	// Draw bolus amount
	char buffer[10] = "";
	char outString[32] = "";
	int digits = 0;
	digits = UnsignedInt_To_ASCII(bolus->Amount / 3600, buffer);

	strcpy(outString, "Amount: ");
	strncat(outString, buffer, digits);
	strncat(outString, " IU", 3);
	GrStringDraw( context, outString, AUTO_STRING_LENGTH, 5, 60, OPAQUE_TEXT);

	free( bolus );

	// Draw Buttons
	LoadLeftButton( context , "CANC");
	LoadMiddleButton( context , "DONE");
	LoadRightButton( context , "RETY");

}

void PrintStartBolus_Invalid( tContext *context ){
	GrStringDrawCentered( context, "Provided", AUTO_STRING_LENGTH, 47, 37, OPAQUE_TEXT );
	GrStringDrawCentered( context, "Bolus is", AUTO_STRING_LENGTH, 47, 47, OPAQUE_TEXT );
	GrStringDrawCentered( context, "Invalid", AUTO_STRING_LENGTH, 47, 57, OPAQUE_TEXT );

	LoadLeftButton( context , "CANC");
	LoadRightButton( context , "RETY");
}

void PrintStartBolus_Idle( tContext *context, unsigned char p_selectedMethod ){
	char outString[32];
	unsigned char text_start = 18;


	// Draw top and bottom banner and buttons
	LoadLeftButton( context , "CANC");
	LoadMiddleButton( context , "SEL");
	//LoadRightButton("");


	// Menu options
	GrStringDraw( context, "Calculator", AUTO_STRING_LENGTH, 5, 18, OPAQUE_TEXT);
	GrStringDraw( context, "Preset", AUTO_STRING_LENGTH, 5, 31, OPAQUE_TEXT);
	GrStringDraw( context, "Manual", AUTO_STRING_LENGTH, 5, 44, OPAQUE_TEXT);

	// Highlight selected item
	switch ( p_selectedMethod ) {
	case e_bolMethod_calculator:
		text_start = 18;
		strcpy(outString, "Calculator");
		break;
	case e_bolMethod_preset:
		text_start = 31;
		strcpy(outString, "Preset");
		break;
	case e_bolMethod_manual:
		text_start = 44;
		strcpy(outString, "Manual");
		break;

	default: break;
	}

	GrContextForegroundSet( context, ClrWhite); //ClrBlack       this affects the highlight color
	GrContextBackgroundSet( context, ClrBlack);  //ClrWhite      this affects the text color in the highlight
	GrStringDraw( context, outString, AUTO_STRING_LENGTH, 5, text_start, OPAQUE_TEXT);
	GrContextForegroundSet( context, ClrBlack);
	GrContextBackgroundSet( context, ClrWhite);
}

void PrintStartBolus_Calculator( tContext *context, bool carbsEnteredFlag, y_carbs enteredCarbs, y_glucose enteredGlucose ){
	// Clear previous entries from screen
	GrContextForegroundSet( context, ClrWhite);
	GrRectFill( context, &myRectangleScreen);
	GrContextForegroundSet( context, ClrBlack);

	// Print header
	GrStringDrawCentered( context, "Use < > arrows", AUTO_STRING_LENGTH, 47, 20, OPAQUE_TEXT);
	GrStringDrawCentered( context, "to select input", AUTO_STRING_LENGTH, 47, 30, OPAQUE_TEXT);

	// Draw carbs header and user entered carbs
	char buffer[10] = "";
	char outString[32] = "";
	int digitsCarb = 0;

	digitsCarb = UnsignedInt_To_ASCII( enteredCarbs, buffer);
	strcpy( outString, "Carb: ");
	strncat( outString, buffer, digitsCarb);
	strncat( outString, " g", 2);
	GrStringDraw( context, outString, AUTO_STRING_LENGTH, 5, 45, OPAQUE_TEXT);


	// Draw glucose header and user entered glucose
	int digitsGluc = 0;
	digitsGluc = UnsignedInt_To_ASCII( enteredGlucose, buffer);
	strcpy( outString, "BG: ");
	strncat( outString, buffer, digitsGluc);
	strncat( outString, " mmol/L", 7);
	GrStringDraw( context, outString, AUTO_STRING_LENGTH, 5, 58, OPAQUE_TEXT);

	// Draw Cursor
	int cursorY, cursorX, cursorW;
	if ( carbsEnteredFlag == false){
		cursorY = 53; // y location
		cursorW = digitsCarb * 5;; // width
		cursorX = 41; // x location is under last entered letter
	}
	else {
		cursorY = 66;
		cursorX = 29;
		cursorW = digitsGluc * 5;
	}
	GrLineDrawH( context, cursorX, cursorX+cursorW, cursorY);

	// Draw Buttons
	LoadLeftButton( context , "CANC");
	LoadMiddleButton( context , "DONE");
	LoadRightButton( context , "RETY");
}

void PrintStartBolus_Preset( tContext *context, y_bolus selectedPreset ){
	if( BolusPresetExists() ){
		int numberOfPresets = GetNumberOfBolusPresets();

		// Get names of saved presets and draw them
		y_bolusName *Name;
		Name = (y_bolusName *) malloc( sizeof( y_bolusName ));

		int i;
		for ( i = 0; i < numberOfPresets; i++ ){
			GetPresetName( Name, i );
			GrStringDraw( context, *Name, AUTO_STRING_LENGTH, 5, 16 + ( 10 * i ), OPAQUE_TEXT );
		}
		free(Name);

		// highlight the selected profile
		unsigned char text_start = 18;
		int index = GetPresetIndex( &selectedPreset );
		text_start = 16 + 10 * index;

		GrContextForegroundSet( context, ClrWhite); //ClrBlack       this affects the highlight color
		GrContextBackgroundSet( context, ClrBlack); //ClrWhite      this affects the text color in the highlight
		GrStringDraw( context, selectedPreset.Name, AUTO_STRING_LENGTH, 5, text_start, OPAQUE_TEXT);
		GrContextForegroundSet( context, ClrBlack);
		GrContextBackgroundSet( context, ClrWhite);

		LoadMiddleButton( context , "SEL" );

	} else {
		GrStringDrawCentered(context, "No Presets", AUTO_STRING_LENGTH, 47, 20, OPAQUE_TEXT);
		GrStringDrawCentered( context, "Available", AUTO_STRING_LENGTH, 47, 30, OPAQUE_TEXT);
	}

	LoadLeftButton( context ,  "CANC" );
	LoadRightButton( context ,  "RETY" );

}

void PrintStartBolus_Manual( tContext *context, y_bolus enteredBolus ){
	// Clear previous entries from screen
	GrContextForegroundSet( context, ClrWhite);
	GrRectFill( context, &myRectangleScreen);
	GrContextForegroundSet( context, ClrBlack);

	// Draw Header
	GrStringDrawCentered( context, "Enter Bolus", AUTO_STRING_LENGTH, 47, 21, OPAQUE_TEXT);
	GrStringDrawCentered( context, "Amount", AUTO_STRING_LENGTH, 47, 31, OPAQUE_TEXT);


	// Draw  header and user entered amount
	char buffer[10] = "";
	char outString[32] = "";
	int digits = 0;
	digits = UnsignedInt_To_ASCII( enteredBolus.Amount / 3600, buffer);

	strcpy(outString, "Amount: ");
	strncat(outString, buffer, digits);
	strncat(outString, " IU", 3);
	GrStringDraw( context, outString, AUTO_STRING_LENGTH, 5, 45, OPAQUE_TEXT);


	// Draw Cursor
	int cursorY, cursorX, cursorW;
	cursorY = 53; // y location
	cursorW = digits * 5;; // width
	cursorX = 53; // x location is under last entered letter
	GrLineDrawH( context, cursorX, cursorX+cursorW, cursorY);

	// Draw Buttons
	LoadLeftButton( context , "CANC");
	LoadMiddleButton( context , "DONE");
	LoadRightButton( context , "RETY");

}
