#ifndef TIMEnDATE_H
#define TIMEnDATE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct{
	unsigned int	hour;
	unsigned int	minute;
	unsigned int	second;
}cTime_t;

typedef cTime_t* timePtr;

typedef struct{
	unsigned int	day;
	unsigned int	month;
	unsigned int	year;
}cDate_t;

cTime_t newTime(cTime_t time, unsigned int hour, unsigned int minute, unsigned int second);
void TimePrint(cTime_t time, int format);
unsigned int GetHour(cTime_t time);
unsigned int Getminute(cTime_t time);
unsigned int Getsecond(cTime_t time);
cTime_t AddTime(cTime_t time1, cTime_t time2);




#endif
