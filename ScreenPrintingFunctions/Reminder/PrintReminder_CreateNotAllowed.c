#include "!PrintReminder_Master.h"
#include "DisplayOut.h"

void PrintRemindCreateNotAllowed(tContext *context){
	GrStringDrawCentered(context, "Reminder" , AUTO_STRING_LENGTH, 46, 30, OPAQUE_TEXT);
	GrStringDrawCentered(context, "Creation" , AUTO_STRING_LENGTH, 46, 40, OPAQUE_TEXT);
	GrStringDrawCentered(context, "Not Allowed" , AUTO_STRING_LENGTH, 46, 50, OPAQUE_TEXT);
	//GrStringDrawCentered(context, m_basActSelected.Name , AUTO_STRING_LENGTH, 46, 30, OPAQUE_TEXT);

	LoadLeftButton("BACK");
}
