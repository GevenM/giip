#include "!PrintReminder_Master.h"
#include "DisplayOut.h"


void PrintRemoveReminder_Idle(tContext *context){
	int numberOfReminders;
	numberOfReminders = GetNumberOfReminders();

	y_remindName *Name;
	Name = (y_remindName *) malloc( sizeof( y_remindName ));

	int i;
	for ( i = 0; i < numberOfReminders; i++ ){
		GetReminderName( Name, i );
		GrStringDraw( context, *Name, AUTO_STRING_LENGTH, 5, 16 + ( 10 * i ), OPAQUE_TEXT );
	}
	free(Name);

	// highlight the selected profile
    unsigned char text_start = 18;
    int index = GetReminderIndex( &m_reminder );
	text_start = 16 + 10 * index;

    GrContextForegroundSet(context, ClrWhite); //ClrBlack       this affects the highlight color
    GrContextBackgroundSet(context, ClrBlack); //ClrWhite      this affects the text color in the highlight
    GrStringDraw(context, m_reminder.Name, AUTO_STRING_LENGTH, 5, text_start, OPAQUE_TEXT);
	GrContextForegroundSet(context, ClrBlack);
	GrContextBackgroundSet(context, ClrWhite);

	LoadLeftButton( "CANC" );
	LoadMiddleButton( "SEL" );
}


void PrintRemoveReminder_Confirm(tContext *context){
	GrContextForegroundSet(context, ClrWhite);
	GrRectFill(context, &myRectangleScreen);
	GrContextForegroundSet(context, ClrBlack);

	GrStringDrawCentered(context, "Remove", AUTO_STRING_LENGTH, 47, 20, OPAQUE_TEXT);
	GrStringDrawCentered(context, "Reminder?", AUTO_STRING_LENGTH, 47, 30, OPAQUE_TEXT);

	GrStringDraw(context, "Name: " , AUTO_STRING_LENGTH, 5, 40, OPAQUE_TEXT);
	GrStringDraw(context, m_reminder.Name, AUTO_STRING_LENGTH, 15, 50, OPAQUE_TEXT);


	LoadLeftButton("CANC");
	LoadMiddleButton("OK");
	LoadRightButton("RETY");
}
