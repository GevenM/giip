#include "!PrintOverlay_Master.h"
#include "DisplayOut.h"
#include "InsulinOutputCalculator.h"
#include "InsulinReservoir.h"

void LoadBanner( tContext *context ){

	int hour = GetCurrentHour();
	int min = GetCurrentMin();
	int sec = GetCurrentSec();

	int digits = 0;
	char buffer[10] = "";
    char outString[10] = "";

    // Get Hours
	digits = UnsignedInt_To_ASCII( hour >> 4, buffer ); // Read upper half of byte by bitshifting four places
	strncpy(outString, buffer, digits);
	digits = UnsignedInt_To_ASCII( hour & 0xF, buffer ); // Read lower half of byte by overwriting the upper half with 0s
	strncat(outString, buffer, digits);
	strncat(outString, ":", 1);

	// Get Minutes
	digits = UnsignedInt_To_ASCII( min >> 4, buffer );
	strncat(outString, buffer, digits);
	digits = UnsignedInt_To_ASCII( min & 0xF, buffer );
	strncat(outString, buffer, digits);

	// Draw top banner
	GrRectFill( context, &myRectangleTopBan);
	GrContextForegroundSet( context, ClrWhite);
	GrContextBackgroundSet( context, ClrBlack);

	GrStringDrawCentered( context, outString, AUTO_STRING_LENGTH, 75 , 7, TRANSPARENT_TEXT);
	//GrStringDrawCentered(&g_sContext, "bat%", AUTO_STRING_LENGTH, 15, 7, TRANSPARENT_TEXT);

	// write insulin reservoir level
	digits = UnsignedInt_To_ASCII( GetInsulinReservoirLevelInPercent(), buffer );
	strcpy(outString, "");
	strncat(outString, buffer, digits);
	strncat(outString, "%", 1);
	GrStringDrawCentered( context, outString, AUTO_STRING_LENGTH, 48, 7, TRANSPARENT_TEXT);

	GrContextForegroundSet( context, ClrBlack);
	GrContextBackgroundSet( context, ClrWhite);




	// TEMPORARY CODE TO BE ABLE TO SEE OUTPUT RATES
	// Get basal and bolus rate
	strcpy(outString, "");
	digits = UnsignedInt_To_ASCII( f_basalOut, buffer );
	strncat(outString, buffer, digits);
	strncat(outString, "/", 1);
	digits = UnsignedInt_To_ASCII( f_bolusOut, buffer );
	strncat(outString, buffer, digits);
	//strncat(outString, ":", 1);

	// Draw top banner
	GrContextForegroundSet( context, ClrWhite);
	GrContextBackgroundSet( context, ClrBlack);
	GrStringDrawCentered( context, outString, AUTO_STRING_LENGTH, 20 , 7, TRANSPARENT_TEXT);
	//GrStringDrawCentered(&g_sContext, "bat%", AUTO_STRING_LENGTH, 15, 7, TRANSPARENT_TEXT);
	//GrStringDrawCentered(&g_sContext, "res%", AUTO_STRING_LENGTH, 48, 7, TRANSPARENT_TEXT);
	GrContextForegroundSet( context, ClrBlack);
	GrContextBackgroundSet( context, ClrWhite);
}
