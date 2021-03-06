/*
 * Testing file to have anything you need to see show up on the settings screen.
 */

#include "TestSettings.h"
#include "RTC.h"
#include "DisplayOut.h"


void ShowDay( tContext *context ){
	char outDay[32] = "";
	int date = GetCurrentDayOfWeek();
	char name[10];

	DateToDay(date, name);

	strcpy(outDay, "Day: ");
	strcat(outDay, name);
	GrStringDraw( context, outDay, AUTO_STRING_LENGTH, 5, 74, OPAQUE_TEXT);
}
