#include "!PrintOverlay_Master.h"

void ClearScreenContent( tContext *context ){
	tRectangle rectangleScreen = { 0, 14, 95, 81};

	GrContextForegroundSet( context, ClrWhite );
	GrRectFill( context, &rectangleScreen );
	GrContextForegroundSet( context, ClrBlack );
}
