#include "!PrintBolus_Master.h"
#include "DisplayOut.h"

void PrintRemoveBolusPreset_Confirm( tContext *context ){
	//char buffer[10] = "";
	//char outString[32] = "";
	//int digits = 0;

	GrContextForegroundSet( context, ClrWhite);
	GrRectFill( context, &myRectangleScreen);
	GrContextForegroundSet( context, ClrBlack);

	GrStringDrawCentered( context, "Remove Bolus", AUTO_STRING_LENGTH, 47, 20, OPAQUE_TEXT );
	GrStringDrawCentered( context, "Preset?", AUTO_STRING_LENGTH, 47, 30, OPAQUE_TEXT );

	// ***** Needs a call to get bolus preset to remove!! then update these commented lines
//	GrStringDraw(&g_sContext, "Name: " , AUTO_STRING_LENGTH, 5, 40, OPAQUE_TEXT);
//	GrStringDraw(&g_sContext, m_bolSelected.Name, AUTO_STRING_LENGTH, 15, 50, OPAQUE_TEXT);


//	digits = UnsignedInt_To_ASCII(m_bolSelected.Amount, buffer);
//	strcpy(outString, "Amount: ");
//	strncat(outString, buffer, digits);
//	strncat(outString, " IU", 3);
//	GrStringDraw(&g_sContext, outString , AUTO_STRING_LENGTH, 5, 65, OPAQUE_TEXT);

	LoadLeftButton("CANC");
	LoadMiddleButton("OK");
	LoadRightButton("RETY");
}

void PrintRemoveBolusPreset_Invalid( tContext *context ){
	GrStringDrawCentered( context, "Selected", AUTO_STRING_LENGTH, 47, 37, OPAQUE_TEXT );
	GrStringDrawCentered( context, "Preset", AUTO_STRING_LENGTH, 47, 47, OPAQUE_TEXT );
	GrStringDrawCentered( context, "is Active", AUTO_STRING_LENGTH, 47, 57, OPAQUE_TEXT );

	LoadLeftButton("CANC");
	LoadRightButton("RETY");

}
