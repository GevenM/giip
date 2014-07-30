#include "!PrintBolus_Master.h"
#include "DisplayOut.h"

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

	// ****** NEED a getBolus to activate and then write these commented outputs
	//GrStringDraw( context, m_bolus.Name, AUTO_STRING_LENGTH, 15, 50, OPAQUE_TEXT);


	//digits = UnsignedInt_To_ASCII(m_bolus.Amount / 3600, buffer);
	//strcpy(outString, "Amount: ");
	//strncat(outString, buffer, digits);
	//strncat(outString, " IU", 3);
	//GrStringDraw( context, outString , AUTO_STRING_LENGTH, 5, 65, OPAQUE_TEXT);

	LoadLeftButton("CANC");
	LoadMiddleButton("OK");
	LoadRightButton("RETY");

}

void PrintCreateBolusPreset_Invalid( tContext *context ){
	GrContextForegroundSet( context, ClrWhite);
	GrRectFill(&g_sContext, &myRectangleScreen);
	GrContextForegroundSet( context, ClrBlack);

	GrStringDrawCentered( context, "Bolus", AUTO_STRING_LENGTH, 47, 37, OPAQUE_TEXT );
	GrStringDrawCentered( context, "Preset", AUTO_STRING_LENGTH, 47, 47, OPAQUE_TEXT );
	GrStringDrawCentered( context, "Invalid", AUTO_STRING_LENGTH, 47, 57, OPAQUE_TEXT );

	LoadLeftButton("CANC");
	LoadRightButton("RETY");

}
