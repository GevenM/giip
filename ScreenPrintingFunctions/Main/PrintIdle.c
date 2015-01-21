#include "!Main_Master.h"
#include "ScreenPrintingFunctions/Overlay/!PrintOverlay_Master.h"
#include "DisplayOut.h"

#include "TemporaryBasalFunctions/TemporaryBasal.h"
#include "BasalFunctions/BasalFunctions.h"
#include "BolusFunctions/BolusPresets.h"
#include "RTC.h"
#include "TriggerReminder.h"
#include "InsulinDeliveryMechanism.h"

void PrintIdle( tContext *context ){
	char buffer[10] = "";
	char outString[32] = "";
	int digits;

	// Clear previous entries from screen
	ClearScreenContent( context );

	// Print basal status
	if ( TemporaryBasalIsActive() ){
		UnsignedInt_To_ASCII( f_activeTmpBasal.Rate / 3600, outString );
		strncat( outString, " IU/hr", 6 );

		GrStringDraw( context, "Temporary Basal:" , AUTO_STRING_LENGTH, 5, 25, OPAQUE_TEXT );
		GrStringDraw( context, outString , AUTO_STRING_LENGTH, 15, 35, OPAQUE_TEXT );

		// Draw duration in hours and minutes
		// get hours
		memset( outString, 0, sizeof( outString ) );
		digits = UnsignedInt_To_ASCII( f_activeTmpBasal.Duration / 60, buffer );
		strncpy( outString, buffer, digits );
		strncat( outString, ":", 1 );

		// get minutes
		digits = UnsignedInt_To_ASCII( f_activeTmpBasal.Duration % 60, buffer );
		if ( digits == 1 ) strncat( outString, "0", 1 );
		strncat( outString, buffer, digits );

		strncat( outString, " Remain", 7 );

		GrStringDraw( context, outString , AUTO_STRING_LENGTH, 15, 45, OPAQUE_TEXT );


	} else if( BasalIsActive() ){

		int currentHour = GetCurrentHour();
		currentHour = BCDtoInt( currentHour );

		int currentMin = GetCurrentMin();
		currentMin = BCDtoInt( currentMin );

		int currentSegment = ( k_segDay / 24 ) * currentHour;
		currentSegment = currentSegment + ( currentMin / (60 / ( k_segDay / 24 )));

		UnsignedInt_To_ASCII( f_activeBasal.Rate[ currentSegment ] / 3600, outString );
		strncat( outString, " IU/hr", 6 );

		GrStringDraw( context, "Basal:" , AUTO_STRING_LENGTH, 5, 25, OPAQUE_TEXT );
		GrStringDraw( context, outString , AUTO_STRING_LENGTH, 15, 35, OPAQUE_TEXT );

	} else {
		GrStringDraw( context, "No Basal" , AUTO_STRING_LENGTH, 5, 25, OPAQUE_TEXT );
	}


	// Print bolus status
	if( BolusIsActive() ){

		UnsignedInt_To_ASCII( (f_activeBolus.Amount + (int)(GetInsulinOutputBuffer()+0.5)) / 3600, outString );

		UnsignedInt_To_ASCII( (( f_activeBolus.Amount + (int)(GetInsulinOutputBuffer()+0.5)) % 3600 ) / 360, buffer );
		strncat( outString, ".", 1 );
		strncat( outString, buffer, 1 );
		strncat( outString, " IU Remain", 10 );

		GrStringDraw( context, "Bolus: " , AUTO_STRING_LENGTH, 5, 55, OPAQUE_TEXT );
		GrStringDraw( context, outString , AUTO_STRING_LENGTH, 15, 65, OPAQUE_TEXT );

	} else {
		GrStringDraw( context, "No Bolus" , AUTO_STRING_LENGTH, 5, 55, OPAQUE_TEXT );
	}

	// Load bottom buttons
	LoadMiddleButton(  context , "MENU" );

}
