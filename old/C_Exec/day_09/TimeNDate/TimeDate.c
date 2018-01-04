#include <stdio.h>
#include "TimeDate.h"

int main(){

	unsigned int h1 = 15, m1 = 60, s1 = 50, h2 = 10, m2 = 40, s2 = 40, day = 23, month = 8, year = 2017;
	cTime_t newtime, time2;
	cDate_t date;


	TimePrint(newtime, 1);

	printf("please enter 1st hour: ");
	scanf("%d", &h1);
	printf("please enter 1st minute: ");
	scanf("%d", &m1);
	printf("please enter 1st seconds: ");
	scanf("%d", &s1);
	printf("please enter 2nd hour: ");
	scanf("%d", &h2);
	printf("please enter 2nd minute: ");
	scanf("%d", &m2);
	printf("please enter 2nd seconds: ");
	scanf("%d", &s2);
	printf("please enter day: ");
	scanf("%d", &day);
	printf("please enter month: ");
	scanf("%d", &month);
	printf("please enter year: ");
	scanf("%d", &year);						
	   	
   	newtime = newTime(newtime, h1, m1, s1);
   	time2 = newTime(time2, h2, m2, s2);
   	printf("time1 = ");
   	TimePrint(newtime, 1);
   	TimePrint(newtime, 2);
   	printf("\nhour: %d\n", GetHour(newtime));
   	printf("minute: %d\n", Getminute(newtime));
   	printf("second: %d\n", Getsecond(newtime));
   	printf("\ntime2 = ");	
   	TimePrint(time2, 1);
   	time2 = AddTime(time2, newtime);
   	printf("\nadded time: ");
   	TimePrint(time2, 2);
   	
	date.day = day;
	date.month = month;
	date.year = year;
   	
   	date = ChangeDate(date, day, month, year);
   	DatePrint(date, 1);
   	DatePrint(date, 2);
   	DatePrint(date, 3);
   	printf("\nthe day (in month) is:%d\n" ,retrieve(date, 1));
   	printf("the month:%d\n" ,retrieve(date, 2));
   	printf("the year is:%d\n" ,retrieve(date, 3));
   	printf("num of days in the year unti the date entered: %d\n" ,retrieve(date, 4));
   	printf("Year is leap? if %d = 1, it is leap\n" ,retrieve(date, 5));
   	
}



