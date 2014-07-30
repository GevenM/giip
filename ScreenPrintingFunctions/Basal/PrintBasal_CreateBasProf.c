#include "!PrintBasal_Master.h"
#include "DisplayOut.h"

void PrintCreateBasProf(tContext *context){
	// Print basal status

		GrStringDrawCentered(context, "Create Basal " , AUTO_STRING_LENGTH, 48, 25, OPAQUE_TEXT);
	//	GrStringDrawCentered(&context, "Temp Basal: " , AUTO_STRING_LENGTH, 48, 25, TRANSPARENT_TEXT);
		//GrStringDrawCentered(&context, "No Basal" , AUTO_STRING_LENGTH, 48, 25, TRANSPARENT_TEXT);



		//LoadBanner();
		// Load bottom buttons
		LoadLeftButton("BACK");
		//LoadMiddleButton("MENU");
		//LoadRightButton("");

}
