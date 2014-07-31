#include "!PrintOverlay_Master.h"
#include "DisplayOut.h"

void LoadLeftButton( tContext *context, const char * text){
	GrRectFill( context, &myRectangleBotLeft);

	GrContextForegroundSet( context, ClrWhite);
	GrContextBackgroundSet( context, ClrBlack);
	GrStringDrawCentered( context, text, AUTO_STRING_LENGTH, 14, 88, TRANSPARENT_TEXT);
	GrContextForegroundSet( context, ClrBlack);
	GrContextBackgroundSet( context, ClrWhite);
}

void LoadMiddleButton( tContext *context, const char * text){
	GrRectFill( context, &myRectangleBotMid);

	GrContextForegroundSet( context, ClrWhite);
	GrContextBackgroundSet( context, ClrBlack);
	GrStringDrawCentered( context, text, AUTO_STRING_LENGTH, 49, 88, TRANSPARENT_TEXT);
	GrContextForegroundSet( context, ClrBlack);
	GrContextBackgroundSet( context, ClrWhite);
}

void LoadRightButton( tContext *context, const char * text){
	GrRectFill( context, &myRectangleBotRight);

	GrContextForegroundSet( context, ClrWhite);
	GrContextBackgroundSet( context, ClrBlack);
	GrStringDrawCentered( context, text, AUTO_STRING_LENGTH, 82, 88, TRANSPARENT_TEXT);
	GrContextForegroundSet( context, ClrBlack);
	GrContextBackgroundSet( context, ClrWhite);
}

void ClearRightButton( tContext *context ){
	GrContextForegroundSet( context, ClrWhite);
	GrContextBackgroundSet( context, ClrBlack);
	GrRectFill( context, &myRectangleBotRight);
	GrContextForegroundSet( context, ClrBlack);
	GrContextBackgroundSet( context, ClrWhite);
}
