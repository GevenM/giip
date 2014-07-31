#include "!PrintBasal_Master.h"
#include "DisplayOut.h"

void PrintRemoveBasProf_Confirm(tContext *context){

	GrStringDrawCentered(context, "Remove Profile?" , AUTO_STRING_LENGTH, 46, 20, OPAQUE_TEXT);
	GrStringDrawCentered(context, m_basRemSelected.Name , AUTO_STRING_LENGTH, 46, 30, OPAQUE_TEXT);

	LoadLeftButton( context , "CANC");
	LoadMiddleButton( context , "OK");
	LoadRightButton( context , "RETY");
}

void PrintRemoveBasProf_Invalid(tContext *context){

	GrStringDrawCentered(context, "Profile Active" , AUTO_STRING_LENGTH, 46, 20, OPAQUE_TEXT);
	GrStringDrawCentered(context, "Cannot Remove" , AUTO_STRING_LENGTH, 46, 30, OPAQUE_TEXT);
	//GrStringDrawCentered(context, m_basActSelected.Name , AUTO_STRING_LENGTH, 46, 30, OPAQUE_TEXT);

	LoadLeftButton( context , "CANC");
	//LoadMiddleButton("OK");
	LoadRightButton( context , "RETY");
}


void PrintRemoveBasProf_Idle( tContext *context, y_basal selectedProfile ){
	int numberOfProfiles;
	numberOfProfiles = GetNumberBasalProfiles();

	y_basalName *Name;
	Name = (y_basalName *) malloc( sizeof( y_basalName ));

	int i;
	for ( i = 0; i < numberOfProfiles; i++ ){
		GetProfileName( Name, i );
		GrStringDraw( context, *Name, AUTO_STRING_LENGTH, 5, 16 + ( 10 * i ), OPAQUE_TEXT );
	}
	free(Name);

	// highlight the selected profile
    unsigned char textStart = 18;
    int index = GetProfileIndex( &selectedProfile );
	textStart = 16 + 10 * index;

    GrContextForegroundSet( context, ClrWhite); //ClrBlack       this affects the highlight color
    GrContextBackgroundSet( context, ClrBlack); //ClrWhite      this affects the text color in the highlight
    GrStringDraw( context, selectedProfile.Name, AUTO_STRING_LENGTH, 5, textStart, OPAQUE_TEXT);
	GrContextForegroundSet( context, ClrBlack);
	GrContextBackgroundSet( context, ClrWhite);

	LoadLeftButton( context , "CANC" );
	LoadMiddleButton( context , "SEL" );

}
