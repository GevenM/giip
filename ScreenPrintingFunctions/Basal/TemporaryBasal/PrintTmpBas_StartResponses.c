#include "!PrintTmpBas_Master.h"
#include "DisplayOut.h"

void PrintStartTmpBas_Confirm(tContext *context){
	char buffer[10] = "";
	char outString[32] = "";
	int digits = 0;

	GrContextForegroundSet(context, ClrWhite);
	GrRectFill(context, &myRectangleScreen);
	GrContextForegroundSet(context, ClrBlack);

	GrStringDrawCentered(context, "Start Temporary", AUTO_STRING_LENGTH, 47, 19, OPAQUE_TEXT);
	GrStringDrawCentered(context, "Basal?", AUTO_STRING_LENGTH, 47, 29, OPAQUE_TEXT);

	digits = UnsignedInt_To_ASCII(m_tmpBas.Duration / 60, buffer);
	strcpy(outString, "Duration: ");
	strncat(outString, buffer, digits);

	GrStringDraw(context, outString , AUTO_STRING_LENGTH, 5, 39, OPAQUE_TEXT);

	digits = UnsignedInt_To_ASCII(m_tmpBas.Rate / 3600, buffer);
	strcpy(outString, "Rate: ");
	strncat(outString, buffer, digits);

	GrStringDraw(context, outString , AUTO_STRING_LENGTH, 5, 49, OPAQUE_TEXT);

	LoadLeftButton("CANC");
	LoadMiddleButton("OK");
	LoadRightButton("RETY");
}

void PrintStartTmpBas_Invalid(tContext *context){

	GrContextForegroundSet(context, ClrWhite);
	GrRectFill(context, &myRectangleScreen);
	GrContextForegroundSet(context, ClrBlack);

	GrStringDrawCentered(context, "Temporary", AUTO_STRING_LENGTH, 47, 37, OPAQUE_TEXT);
	GrStringDrawCentered(context, "Basal", AUTO_STRING_LENGTH, 47, 47, OPAQUE_TEXT);
	GrStringDrawCentered(context, "Invalid", AUTO_STRING_LENGTH, 47, 57, OPAQUE_TEXT);

	LoadLeftButton("CANC");
	LoadRightButton("RETY");
}
