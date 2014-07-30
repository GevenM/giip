/*
 * Testing file to have anything you need to see show up on the settings screen.
 */

#include "TestSettings.h"
#include "RTC.h"
#include "DisplayOut.h"


void ShowDay(){
	char outDay[32] = "";
	int day = GetCurrentDayOfWeek();
	char name[10];

	switch(day){
	case 0:
		strcpy(name, "Sunday");
		break;
	case 1:
		strcpy(name, "Monday");
		break;
	case 2:
		strcpy(name, "Tuesday");
		break;
	case 3:
		strcpy(name, "Wednesday");
		break;
	case 4:
		strcpy(name, "Thursday");
		break;
	case 5:
		strcpy(name, "Friday");
		break;
	case 6:
		strcpy(name, "Saturday");
		break;
	}

	strcpy(outDay, "Day: ");
	strcat(outDay, name);
	GrStringDraw(&g_sContext, outDay, AUTO_STRING_LENGTH, 5, 74, OPAQUE_TEXT);
}
