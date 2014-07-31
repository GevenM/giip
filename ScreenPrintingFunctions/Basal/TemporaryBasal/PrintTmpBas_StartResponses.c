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

void PrintStartTmpBas_Idle(){
	char buffer[10] = "";
	char outString[32] = "";
	int digits = 0;
	int cursorY, cursorX, cursorW;

		if (tmpBasal_DurationEntered == false){
			LoadRightButton("RATE");
			cursorY = 38;
			cursorX = 65;

			if (m_tmpBas.Duration / 60 <= 9)
				cursorW = 4;
			else if (m_tmpBas.Duration / 60 > 9)
				cursorW = 10;
		}
		else {
			LoadRightButton("DUR");
			cursorY = 48;
			cursorX = 65;
			if(m_tmpBas.Rate / 3600 <= 9)
				cursorW = 4;
			else if (m_tmpBas.Rate / 3600 > 9)
				cursorW = 10;
		}

	GrContextForegroundSet(&g_sContext, ClrWhite);
	GrRectFill(&g_sContext, &myRectangleScreen);
	GrContextForegroundSet(&g_sContext, ClrBlack);

	GrStringDraw(&g_sContext, "Temporary Basal" , AUTO_STRING_LENGTH, 5, 20, OPAQUE_TEXT);

	digits = UnsignedInt_To_ASCII(m_tmpBas.Duration / 60, buffer);
	strcpy(outString, "Duration: ");
	strncat(outString, buffer, digits);


	GrStringDraw(&g_sContext, outString , AUTO_STRING_LENGTH, 5, 30, OPAQUE_TEXT);

	digits = UnsignedInt_To_ASCII(m_tmpBas.Rate / 3600, buffer);
	strcpy(outString, "Rate:     ");
	strncat(outString, buffer, digits);

	GrStringDraw(&g_sContext, outString , AUTO_STRING_LENGTH, 5, 40, OPAQUE_TEXT);

	GrLineDrawH(&g_sContext, cursorX, cursorX+cursorW, cursorY);

	LoadLeftButton("CANC");
	LoadMiddleButton("DONE");

	GrFlush(&g_sContext);

}
