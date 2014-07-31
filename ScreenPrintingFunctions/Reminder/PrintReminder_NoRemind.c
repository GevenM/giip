#include "!PrintReminder_Master.h"
#include "DisplayOut.h"

void PrintNoRemind(tContext *context){
	GrStringDrawCentered(context, "No Reminder" , AUTO_STRING_LENGTH, 46, 20, OPAQUE_TEXT);
	GrStringDrawCentered(context, "Exists" , AUTO_STRING_LENGTH, 46, 30, OPAQUE_TEXT);
	//GrStringDrawCentered(context, m_basActSelected.Name , AUTO_STRING_LENGTH, 46, 30, OPAQUE_TEXT);

	LoadLeftButton( context , "BACK");
}
