#include "!PrintBasal_Master.h"
#include "DisplayOut.h"

void LoadRates( tContext *context, y_basal *p_profile, int scrollOffset, unsigned char *segments);

void PrintCreateBasProf_Confirm(tContext *context){
	GrStringDraw(context, "Save Profile?" , AUTO_STRING_LENGTH, 5, 16, OPAQUE_TEXT);
	GrStringDraw(context, m_basProf.Name , AUTO_STRING_LENGTH, 5, 26, OPAQUE_TEXT);

	LoadLeftButton( context , "CANC");
	LoadMiddleButton( context , "OK");
	LoadRightButton( context , "RETY");
}

void PrintCreateBasProf_Invalid(tContext *context){

	GrStringDrawCentered(context, "Invalid Profile" , AUTO_STRING_LENGTH, 46, 20, OPAQUE_TEXT);
	//GrStringDrawCentered(context, m_basActSelected.Name , AUTO_STRING_LENGTH, 46, 30, OPAQUE_TEXT);

	LoadLeftButton( context , "CANC");
	//LoadMiddleButton("OK");
	LoadRightButton( context , "RETY");
}


void PrintCreateBasProf_Idle(tContext *context, y_basal p_profile, bool nameEntered, unsigned char segmentIndex, unsigned char rateIndex, unsigned char *segments ){
	int cursorY, cursorX, cursorW, scrollOffset = 0;

	if ( nameEntered == false){
		cursorY = 34;
		cursorX = strlen( p_profile.Name ) * 6 - 1;
		cursorW = 4;
	} else {
		cursorY = 58 + segmentIndex * 10 ;
		cursorX = 35 + rateIndex * 30;
		cursorW = 23 - rateIndex * 7;
	}

	if (cursorY > 80){
		scrollOffset = cursorY - 80;

		GrContextForegroundSet( context, ClrWhite );
		GrRectFill( context, &myRectangleScreen );
		GrContextForegroundSet( context, ClrBlack );
	} else if ( cursorY > 70 ){
		// takes care of clearing the screen when returning to the top of the page.
		GrContextForegroundSet( context, ClrWhite );
		GrRectFill( context, &myRectangleScreen );
		GrContextForegroundSet( context, ClrBlack );
	}

	if ( 16-scrollOffset > 15 && 16-scrollOffset < 80 ) GrStringDraw( context, "Profile Name:" , AUTO_STRING_LENGTH, 5, 16 - scrollOffset, OPAQUE_TEXT );

	if ( 40-scrollOffset > 15 && 40-scrollOffset < 80 ) GrStringDraw( context, "Rates:   |U/hr" , AUTO_STRING_LENGTH, 5, 40 - scrollOffset, OPAQUE_TEXT );

	LoadRates( context, &p_profile, scrollOffset, segments );

	// Remove previously written letters and underline
	GrContextForegroundSet( context, ClrWhite );
	if ( 26-scrollOffset > 15 && 26-scrollOffset < 80 ) GrStringDraw( context, "xxxxxxxxxxx", AUTO_STRING_LENGTH, 5, 26 - scrollOffset, OPAQUE_TEXT );
	if ( 30-scrollOffset > 15 && 30-scrollOffset < 80 ) GrStringDraw( context, "xxxxxxxxxxx", AUTO_STRING_LENGTH, 5, 30 - scrollOffset, OPAQUE_TEXT );
	GrContextForegroundSet( context, ClrBlack );

	if ( cursorY > 13 && cursorY - scrollOffset < 81 ) GrLineDrawH( context, cursorX, cursorX + cursorW, cursorY - scrollOffset );
	if ( 26-scrollOffset > 15 && 26 - scrollOffset < 80 ) GrStringDraw( context, p_profile.Name , AUTO_STRING_LENGTH, 5, 26 - scrollOffset, OPAQUE_TEXT );

	LoadLeftButton( context , "CANC");
	if ( nameEntered == false ){
		LoadRightButton( context ,  "RATE" );
		LoadMiddleButton( context ,  "DONE" );
	}
	else {
		LoadRightButton( context ,  "NAME" );
		LoadMiddleButton( context ,  "DONE" );
	}
}

void LoadRates( tContext *context, y_basal *p_profile, int scrollOffset, unsigned char *segments){

	char buffer[10] = "";
	char rateBuffer[10] = "";
	char outString[32] = "";
	int rateDigs, hours, halfs, digits, segCount = 0;
	int i = 0;


	strcpy( outString, "0000-" );

	while( i < k_segDay && segments[ i + 1 ]!= 0 )
	{
		segCount += segments[i];
		hours = segCount/2;
		halfs = segCount%2;

		digits = UnsignedInt_To_ASCII( hours, buffer );
		strncat( outString, buffer, digits );

		if ( halfs == 1 )	strncat( outString, "30", 2 );
		else strncat( outString, "00", 2 );

		if ( digits == 1 ) strncat( outString, " ", 1 );

		rateDigs = UnsignedInt_To_ASCII( p_profile->Rate[i] / 3600, rateBuffer );
		strncat( outString, "|", 1 );
		strncat( outString, rateBuffer, rateDigs );

		if ( 50 + i * 10 - scrollOffset > 15 && 50 + i * 10 - scrollOffset < 80) GrStringDraw( context, outString , AUTO_STRING_LENGTH, 5, i * 10 + 50 - scrollOffset, OPAQUE_TEXT );

		strcpy( outString, "" );
		if ( digits == 1 ) strncat( outString, " ", 1 );

		strncat( outString, buffer,digits );

		if ( halfs == 1 )	strncat( outString, "30-", 3 );
		else strncat( outString, "00-", 3 );


		// Remove previously written underline
		GrContextForegroundSet( context, ClrWhite );
		if ( 58 + i * 10 - scrollOffset > 15 && 58 + i * 10 - scrollOffset < 81) GrLineDrawH( context, 35, 95, 58 + i * 10 - scrollOffset );
		GrContextForegroundSet( context, ClrBlack);

		i++;
	}

	// Remove previously written underline
	GrContextForegroundSet( context, ClrWhite );
	if ( 58 + i * 10 - scrollOffset > 15 && 58 + i * 10 - scrollOffset < 81) GrLineDrawH( context, 35, 95, 58 + i * 10 - scrollOffset );
	GrContextForegroundSet( context, ClrBlack );

	segCount += segments[i];
	hours = segCount / 2;
	halfs = segCount % 2;
	digits = UnsignedInt_To_ASCII( hours, buffer );

	if ( digits == 1 ) strncat( outString, " ", 1 );

	strncat( outString, buffer,digits );

	if ( halfs == 1 )	strncat( outString, "30", 2 );
	else strncat( outString, "00", 2 );

	if ( digits == 1 ) strncat( outString, " ", 1 );

	rateDigs = UnsignedInt_To_ASCII( p_profile->Rate[i] / 3600, rateBuffer );
	strncat( outString, "|", 1 );
	strncat( outString, rateBuffer, rateDigs);

	if ( 50 + i * 10 - scrollOffset > 15 && 50 + i * 10 - scrollOffset < 80) GrStringDraw( context, outString , AUTO_STRING_LENGTH, 5, 10 * i + 50 - scrollOffset, OPAQUE_TEXT );

}
