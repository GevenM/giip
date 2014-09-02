// following the formula from:
// http://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week#A_tabular_method_to_calculate_the_day_of_the_week

#include "DayOfWeek.h"
#include "RTC.h"
#include "DisplayOut.h"

int GetdNumber(int day);
int GetmNumber(int month, int year);
int GetyNumber(int year);
int GetcNumber(int year);


void GetDay( Calendar *date ){
	int dayNum = BCDtoInt(date->DayOfMonth);
	int month = BCDtoInt(date->Month);
	int year = BCDtoInt(date->Year);
	int dayName;
	int d, m, y, c;

	d = GetdNumber(dayNum);
	m = GetmNumber(month, year);
	y = GetyNumber(year);
	c = GetcNumber(year);

	dayName = (d + m + y + (y/4) + c) % 7;

	date->DayOfWeek = dayName;
}


int GetdNumber(int day){
	int d;

	switch (day){
	case 1:
		d = 1;
		break;
	case 2:
		d = 2;
		break;
	case 3:
		d = 3;
		break;
	case 4:
		d = 4;
		break;
	case 5:
		d = 5;
		break;
	case 6:
		d = 6;
		break;
	case 7:
		d = 0;
		break;
	case 8:
		d = 1;
		break;
	case 9:
		d = 2;
		break;
	case 10:
		d = 3;
		break;
	case 11:
		d = 4;
		break;
	case 12:
		d = 5;
		break;
	case 13:
		d = 6;
		break;
	case 14:
		d = 0;
		break;
	case 15:
		d = 1;
		break;
	case 16:
		d = 2;
		break;
	case 17:
		d = 3;
		break;
	case 18:
		d = 4;
		break;
	case 19:
		d = 5;
		break;
	case 20:
		d = 6;
		break;
	case 21:
		d = 0;
		break;
	case 22:
		d = 1;
		break;
	case 23:
		d = 2;
		break;
	case 24:
		d = 3;
		break;
	case 25:
		d = 4;
		break;
	case 26:
		d = 5;
		break;
	case 27:
		d = 6;
		break;
	case 28:
		d = 0;
		break;
	case 29:
		d = 1;
		break;
	case 30:
		d = 2;
		break;
	case 31:
		d = 3;
		break;

	}
	return d;
}

int GetmNumber(int month, int year){
	int m;
	bool leapYear = IsLeapYear(year);

	switch(month){
	case 1://jan
		if(leapYear == true)
			m = 6;
		else
			m = 0;
		break;
	case 2://feb
		if(leapYear == true)
			m = 2;
		else
			m = 3;
		break;
	case 3://mar
		m = 3;
		break;
	case 4://apr
		m = 6;
		break;
	case 5://may
		m = 1;
		break;
	case 6://jun
		m = 4;
		break;
	case 7://jul
		m = 6;
		break;
	case 8://aug
		m = 2;
		break;
	case 9://sep
		m = 5;
		break;
	case 10://oct
		m = 0;
		break;
	case 11://nov
		m = 3;
		break;
	case 12://dec
		m = 5;
		break;
	}

	return m;
}

int GetyNumber(int year){
	int y;
	int yearMod = year % 100;

	switch (yearMod){
	case 0:
		y = 0;
		break;
	case 1:
		y = 1;
		break;
	case 2:
		y = 2;
		break;
	case 3:
		y = 3;
		break;
	case 4:
		y = 5;
		break;
	case 5:
		y = 6;
		break;
	case 6:
		y = 0;
		break;
	case 7:
		y = 1;
		break;
	case 8:
		y = 3;
		break;
	case 9:
		y = 4;
		break;
	case 10:
		y = 5;
		break;
	case 11:
		y = 6;
		break;
	case 12:
		y = 1;
		break;
	case 13:
		y = 2;
		break;
	case 14:
		y = 3;
		break;
	case 15:
		y = 4;
		break;
	case 16:
		y = 6;
		break;
	case 17:
		y = 0;
		break;
	case 18:
		y = 1;
		break;
	case 19:
		y = 2;
		break;
	case 20:
		y = 4;
		break;
	case 21:
		y = 5;
		break;
	case 22:
		y = 6;
		break;
	case 23:
		y = 0;
		break;
	case 24:
		y = 2;
		break;
	case 25:
		y = 3;
		break;
	case 26:
		y = 4;
		break;
	case 27:
		y = 5;
		break;
	case 28:
		y = 0;
		break;
	case 29:
		y = 1;
		break;
	case 30:
		y = 2;
		break;
	case 31:
		y = 3;
		break;
	case 32:
		y = 5;
		break;
	case 33:
		y = 6;
		break;
	case 34:
		y = 0;
		break;
	case 35:
		y = 1;
		break;
	case 36:
		y = 3;
		break;
	case 37:
		y = 4;
		break;
	case 38:
		y = 5;
		break;
	case 39:
		y = 6;
		break;
	case 40:
		y = 1;
		break;
	case 41:
		y = 2;
		break;
	case 42:
		y = 3;
		break;
	case 43:
		y = 4;
		break;
	case 44:
		y = 6;
		break;
	case 45:
		y = 0;
		break;
	case 46:
		y = 1;
		break;
	case 47:
		y = 2;
		break;
	case 48:
		y = 4;
		break;
	case 49:
		y = 5;
		break;
	case 50:
		y = 6;
		break;
	case 51:
		y = 0;
		break;
	case 52:
		y = 2;
		break;
	case 53:
		y = 3;
		break;
	case 54:
		y = 4;
		break;
	case 55:
		y = 5;
		break;
	case 56:
		y = 0;
		break;
	case 57:
		y = 1;
		break;
	case 58:
		y = 2;
		break;
	case 59:
		y = 3;
		break;
	case 60:
		y = 5;
		break;
	case 61:
		y = 6;
		break;
	case 62:
		y = 0;
		break;
	case 63:
		y = 1;
		break;
	case 64:
		y = 3;
		break;
	case 65:
		y = 4;
		break;
	case 66:
		y = 5;
		break;
	case 67:
		y = 6;
		break;
	case 68:
		y = 1;
		break;
	case 69:
		y = 2;
		break;
	case 70:
		y = 3;
		break;
	case 71:
		y = 4;
		break;
	case 72:
		y = 6;
		break;
	case 73:
		y = 0;
		break;
	case 74:
		y = 1;
		break;
	case 75:
		y = 2;
		break;
	case 76:
		y = 4;
		break;
	case 77:
		y = 5;
		break;
	case 78:
		y = 6;
		break;
	case 79:
		y = 0;
		break;
	case 80:
		y = 2;
		break;
	case 81:
		y = 3;
		break;
	case 82:
		y = 4;
		break;
	case 83:
		y = 5;
		break;
	case 84:
		y = 0;
		break;
	case 85:
		y = 1;
		break;
	case 86:
		y = 2;
		break;
	case 87:
		y = 3;
		break;
	case 88:
		y = 5;
		break;
	case 89:
		y = 6;
		break;
	case 90:
		y = 0;
		break;
	case 91:
		y = 1;
		break;
	case 92:
		y = 3;
		break;
	case 93:
		y = 4;
		break;
	case 94:
		y = 5;
		break;
	case 95:
		y = 6;
		break;
	case 96:
		y = 1;
		break;
	case 97:
		y = 2;
		break;
	case 98:
		y = 3;
		break;
	case 99:
		y = 4;
		break;
	}

	return y;
}

int GetcNumber(int year){
	int c, i;

	i = (year / 100);
	i = i % 4;
	switch (i){
	case 1:
		c = 4;
		break;
	case 2:
		c = 2;
		break;
	case 3:
		c = 0;
		break;
	case 0:
		c = 6;
		break;
	}

	return c;
}

void DateToDay(int date, char *day){

	if(date > 6 || date < 0){ //checking if there is no error and date is within realm of possibility
		char buffer[10] = "";
		int digits;
		digits = UnsignedInt_To_ASCII(date, buffer);
		strncat(day, buffer, digits);
	}
	else { //date number is valid
		switch(date){
			case 0:
				strcpy(day, "Sunday");
				break;
			case 1:
				strcpy(day, "Monday");
				break;
			case 2:
				strcpy(day, "Tuesday");
				break;
			case 3:
				strcpy(day, "Wednesday");
				break;
			case 4:
				strcpy(day, "Thursday");
				break;
			case 5:
				strcpy(day, "Friday");
				break;
			case 6:
				strcpy(day, "Saturday");
				break;
		}
	}

}

bool IsLeapYear(int year){
	 bool leapYear = false;

	if ( year % 4 == 0) { // If year is divisible by 4
		leapYear = true;

			if ( year % 100 == 0 ){ // Year divisible by 100
				leapYear = false;

				if ( year % 400 == 0 ){ // Year divisible by 400
					leapYear = true;
				}
			}
	}

	return leapYear;
}
