#include <stdio.h>
#include "TimeDate.h"


cTime_t newTime(cTime_t time, unsigned int hour, unsigned int minute, unsigned int second){

//	unsigned int hr, mn, sc;
	
	if(hour < 24 && minute < 60 && second < 60){
		time.hour = hour;
		time.minute = minute;
		time.second = second;
	} else {
		time.hour = 0;
		time.minute = 0;
		time.second = 0;
	}
	
	return time;
	
}

void TimePrint(cTime_t time, int format){
	
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
	return time.hour;
}
unsigned int Getminute(cTime_t time){
	return time.minute;
}
unsigned int Getsecond(cTime_t time){
	return time.second;
}
cTime_t AddTime(cTime_t time1, cTime_t time2){
	unsigned int totSec, totMin, totHr;
	
	cTime_t upT;
	
	totSec = (time1.second + time2.second) % 60;
	totMin = ((time1.second + time2.second) / 60 + (time1.minute + time2.minute)) % 60;
	totHr = (time1.minute + time2.minute) / 24 + (time1.hour + time2.hour) % 24;
	
	upT = newTime(upT, totHr, totMin, totSec);
	return upT;
		
}
