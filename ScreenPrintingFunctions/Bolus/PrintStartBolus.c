#include "!PrintBolus_Master.h"
#include "DisplayOut.h"
#include "ActivateBolus.h"

void PrintStartBolus_Confirm( tContext *context ){
	// Draw Header
	GrStringDrawCentered( context, "Activate Bolus?", AUTO_STRING_LENGTH, 47, 21, OPAQUE_TEXT);

	// Get names of saved presets and draw them
	y_bolus *bolus;
	bolus = (y_bolus *) malloc( sizeof( y_bolus ));

	// Get the bolus to activate
	BolusToActivate( bolus );

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
	LoadLeftButton("CANC");
	LoadMiddleButton("DONE");
	LoadRightButton("RETY");

}

void PrintStartBolus_Invalid( tContext *context ){
	GrStringDrawCentered( context, "Provided", AUTO_STRING_LENGTH, 47, 37, OPAQUE_TEXT );
	GrStringDrawCentered( context, "Bolus is", AUTO_STRING_LENGTH, 47, 47, OPAQUE_TEXT );
	GrStringDrawCentered( context, "Invalid", AUTO_STRING_LENGTH, 47, 57, OPAQUE_TEXT );

	LoadLeftButton("CANC");
	LoadRightButton("RETY");
}
