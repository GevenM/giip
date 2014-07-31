#include "!PrintTmpBas_Master.h"
#include "DisplayOut.h"

void PrintStartTmpBas_Confirm(tContext *context, y_tmpBasal tmpBas){
	char buffer[10] = "";
	char outString[32] = "";
	int digits = 0;

	GrContextForegroundSet(context, ClrWhite);
	GrRectFill(context, &myRectangleScreen);
	GrContextForegroundSet(context, ClrBlack);

	GrStringDrawCentered(context, "Start Temporary", AUTO_STRING_LENGTH, 47, 19, OPAQUE_TEXT);
	GrStringDrawCentered(context, "Basal?", AUTO_STRING_LENGTH, 47, 29, OPAQUE_TEXT);

	digits = UnsignedInt_To_ASCII(tmpBas.Duration / 60, buffer);
	strcpy(outString, "Duration: ");
	strncat(outString, buffer, digits);

	GrStringDraw(context, outString , AUTO_STRING_LENGTH, 5, 39, OPAQUE_TEXT);

	digits = UnsignedInt_To_ASCII(tmpBas.Rate / 3600, buffer);
	strcpy(outString, "Rate: ");
	strncat(outString, buffer, digits);

	GrStringDraw(context, outString , AUTO_STRING_LENGTH, 5, 49, OPAQUE_TEXT);

	LoadLeftButton( context , "CANC");
	LoadMiddleButton( context , "OK");
	LoadRightButton( context , "RETY");
}

void PrintStartTmpBas_Invalid(tContext *context){

	GrContextForegroundSet(context, ClrWhite);
	GrRectFill(context, &myRectangleScreen);
	GrContextForegroundSet(context, ClrBlack);

	GrStringDrawCentered(context, "Temporary", AUTO_STRING_LENGTH, 47, 37, OPAQUE_TEXT);
	GrStringDrawCentered(context, "Basal", AUTO_STRING_LENGTH, 47, 47, OPAQUE_TEXT);
	GrStringDrawCentered(context, "Invalid", AUTO_STRING_LENGTH, 47, 57, OPAQUE_TEXT);

	LoadLeftButton( context , "CANC");
	LoadRightButton( context , "RETY");
}

void PrintStartTmpBas_Idle(tContext *context, bool tmpBasal_DurationEntered, y_tmpBasal tmpBas){
	char buffer[10] = "";
	char outString[32] = "";
	int digits = 0;
	int cursorY, cursorX, cursorW;

		if (tmpBasal_DurationEntered == false){
			LoadRightButton( context , "RATE");
			cursorY = 38;
			cursorX = 65;

			if (tmpBas.Duration / 60 <= 9)
				cursorW = 4;
			else if (tmpBas.Duration / 60 > 9)
				cursorW = 10;
		}
		else {
			LoadRightButton( context , "DUR");
			cursorY = 48;
			cursorX = 65;
			if(tmpBas.Rate / 3600 <= 9)
				cursorW = 4;
			else if (tmpBas.Rate / 3600 > 9)
				cursorW = 10;
		}

	GrContextForegroundSet(context, ClrWhite);
	GrRectFill(context, &myRectangleScreen);
	GrContextForegroundSet(context, ClrBlack);

	GrStringDraw(context, "Temporary Basal" , AUTO_STRING_LENGTH, 5, 20, OPAQUE_TEXT);

	digits = UnsignedInt_To_ASCII(tmpBas.Duration / 60, buffer);
	strcpy(outString, "Duration: ");
	strncat(outString, buffer, digits);


	GrStringDraw(context, outString , AUTO_STRING_LENGTH, 5, 30, OPAQUE_TEXT);

	digits = UnsignedInt_To_ASCII(tmpBas.Rate / 3600, buffer);
	strcpy(outString, "Rate:     ");
	strncat(outString, buffer, digits);

	GrStringDraw(context, outString , AUTO_STRING_LENGTH, 5, 40, OPAQUE_TEXT);

	GrLineDrawH(context, cursorX, cursorX+cursorW, cursorY);

	LoadLeftButton( context , "CANC");
	LoadMiddleButton( context , "DONE");
}
