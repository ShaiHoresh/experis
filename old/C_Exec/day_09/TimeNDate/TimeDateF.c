#include <stdio.h>
#include "TimeDate.h"

int* daysInMonth(cDate_t date);
int checkTime(cTime_t time);

cTime_t newTime(cTime_t time, unsigned int hour, unsigned int minute, unsigned int second){

	
	time.hour = hour;
	time.minute = minute;
	time.second = second;
	if(checkTime(time) == 0){
		time.hour = 99;
		time.minute = 99;
		time.second = 99;
	}
	
	return time;
	
}

int checkTime(cTime_t time){

	int flag = 0;

	if(time.hour < 24 && time.minute < 60 && time.second < 60){
		flag = 1;
	}
	
	return flag;
}

void TimePrint(cTime_t time, int format){
	
	if(checkTime(time) == 0){
		printf("the time is illegal\n");
		return;
	}
	
	
	if(format == 1){
		printf("%d:%d:%d\n", time.hour, time.minute,time.second);
	} else {
		if(time.hour/12 == 0){
			printf("%d:%d:%d AM\n", time.hour, time.minute, time.second);
		}else{
			printf("%d:%d:%d PM\n", time.hour % 12, time.minute, time.second);
		}
		
	}
	
}

unsigned int GetHour(cTime_t time){
	if(checkTime(time) == 0){
		printf("the time is illegal\n");
		return 0;
	}	
	return time.hour;
}
unsigned int Getminute(cTime_t time){
	if(checkTime(time) == 0){
		printf("the time is illegal\n");
		return 0;
	}
	return time.minute;
}
unsigned int Getsecond(cTime_t time){
	if(checkTime(time) == 0){
		printf("the time is illegal\n");
		return 0;
	}
	return time.second;
}
cTime_t AddTime(cTime_t time1, cTime_t time2){
	unsigned int totSec, totMin, totHr;
	cTime_t time;
	
	if(checkTime(time1) == 0 || checkTime(time2) == 0){
		time.hour = 0;
		time.minute = 0;
		time.second = 0;
		return time;
	}
	
	cTime_t addedTime;
	
	totSec = (time1.second + time2.second) % 60;
	totMin = ((time1.second + time2.second) / 60 + (time1.minute + time2.minute)) % 60;
	totHr = (time1.minute + time2.minute) / 60 + (time1.hour + time2.hour) % 24;
	
	if((time1.minute + time2.minute) / 24 + (time1.hour + time2.hour) / 24 == 1){
		printf("next day\n");		/**/
	}
	
	addedTime = newTime(addedTime, totHr, totMin, totSec);
	return addedTime;
		
}

cDate_t ChangeDate(cDate_t oldDate,	unsigned int day, unsigned int month, unsigned int year){
	
	cDate_t newDate;
	
	newDate.day = day;
	newDate.month = month;
	newDate.year = year;
	if(CheckDate(newDate) == 1){
		return newDate;
	} else if(CheckDate(oldDate) == 1) {
		return oldDate;
	} else {
	newDate.day = 0;
	newDate.month = 0;
	newDate.year = 0;
	}
}

int isLeap(cDate_t date){

	int flag = 0;
	
//	if(CheckDate(date) == 0) return 0;

	if(date.year % 4 == 0){
		flag = 1;
	}

	return flag;
}

int CheckDate(cDate_t date){

	int flag = 1;
	int days[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	int leap;
	
	leap = isLeap(date);
	if(leap == 1){
		days[1] = 29;
	}
	
	if(date.month > 12 || date.month == 0 || date.day > days[date.month] || date.day == 0){
		flag = 0;
	}

	return flag;

}

int DatePrint(cDate_t date, unsigned int format){
	
	if(CheckDate(date) == 0){
		return 0;
	}
	
	switch (format) {
		case 1:
			printf("%d/%s/%d\n", date.day, getMonthName(date), date.year);
		break;
		case 2:
			printf("%d/%d/%d\n", date.day, date.month, date.year);
		break;
		case 3:
			printf("%d/%d/%d\n", date.month, date.day, date.year);
		break;
	}
	
	return 1;
}

char* getMonthName(cDate_t date){
	switch (date.month) {
		case 1:
			return "Jan";
		break;
		case 2:
			return "Feb";
		break;
		case 3:
			return "Mar";
		break;
		case 4:
			return "Apr";
		break;
		case 5:
			return "May";
		break;
		case 6:
			return "Jun";
		break;
		case 7:
			return "Jul";
		break;
		case 8:
			return "Aug";
		break;
		case 9:
			return "Sep";
		break;
		case 10:
			return "Oct";
		break;
		case 11:
			return "Nov";
		break;
		case 12:
			return "Dec";
		break;

	}
}

int retrieve(cDate_t date, unsigned int type){

	int numOfDays = 0, i;
	int	*days = daysInMonth(date);
	
	if(type == 0 || type > 5) return 0;
	if(CheckDate(date) == 0) return 0;
	
	switch (type) {
		case 1:
			return date.day;
		break;
		case 2:
			return date.month;
		break;
		case 3:
			return date.year;
		break;
		case 4:
			for(i = 0; i < date.month - 1; ++i){
				numOfDays += days[i];
			}
			numOfDays += date.day;
			return numOfDays;
		break;
		case 5:
			return isLeap(date);
		break;
	}
	
	return 1;
}

int* daysInMonth(cDate_t date){
	int days[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	int leap;
	int* daysPtr;
	
	leap = isLeap(date);
	if(leap == 1){
		days[1] = 29;
	}
	daysPtr = days;
	return daysPtr;
}



