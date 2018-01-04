#include <stdio.h>
#include "TimeDate.h"

int main(){

	time_t 	time_date;
   	struct tm* 	current_time;
	unsigned int h = 15, m = -35, s = 28;
	cTime_t newtime, time2;
	
 //  	time_date = time(0);	// current time in seconds
 //  	current_time = localtime(&time_date);

	//newtime.hour = 15;	
  // 	newtime.minute = 35;
//   	newtime.second = 25;
   	
   	newtime = newTime(newtime, h, m, s);
   	time2 = newTime(time2, 14, 30, 45);
   	printf("time1 = ");
   	TimePrint(newtime, 1);
   	TimePrint(newtime, 2);
   	printf("hour: %d\n", GetHour(newtime));
   	printf("minute: %d\n", Getminute(newtime));
   	printf("second: %d\n", Getsecond(newtime));
   	printf("time2 = ");	
   	TimePrint(time2, 1);
   	time2 = AddTime(newtime, time2);
   	TimePrint(time2, 2);

}




/*
cTime_t newTime(cTime_t time, unsigned int hour, unsigned int minute, unsigned int second);
void TimePrint(cTime_t time, int format);
unsigned int GetHour(cTime_t time);
unsigned int Getminute(cTime_t time);
unsigned int Getsecond(cTime_t time);
cTime_t* AddTime(cTime_t time1, cTime_t time2);
*/
