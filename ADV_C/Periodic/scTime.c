#include <time.h>       /* clockid_t, clock_gettime... */
#include <stdlib.h>     /* malloc */
#include <stdio.h>      /* printf (debugging) */
#include <unistd.h>     /* usleep */

#include "scTime.h"

#define MILLION 1000000
#define BILLION 1000000000

/*************************/
/*TIME API FUNCTIONS*/
/*************************/

struct Time
{
    struct timespec m_time;
    clockid_t       m_clockID;
};



static void printTime(Time* _time)
{
    printf("\n%ld:%09ld\n", _time->m_time.tv_sec, _time->m_time.tv_nsec);
}

Time* TimeCreate(int _milliSecs)
{
    Time* time;
    
    time = malloc(sizeof(Time));
    if(NULL == time)
    {
        return NULL;
    }
    
    time->m_time.tv_sec = _milliSecs / 1000;
    time->m_time.tv_nsec = (_milliSecs % 1000) * MILLION;
    
    return time;
}

Time* TimeCreateCurrent(const clockid_t _clockID)
{
    Time* time;
    int flag;
    
    time = malloc(sizeof(Time));
    if(NULL == time)
    {
        return NULL;
    }
    
    flag = clock_gettime(_clockID, &(time->m_time));
    if(flag)
    {
        return NULL;
    }
    
    return time;
}

void TimeDestroy(Time* _time)
{
    if(_time)
    {
        free(_time);
    }
    return;
}

int	TimeCompare(const Time* _first, const Time* _second)
{
    /* TODO checks */
    int res = 0;
    res = subtract(_first, _second);
    return (res < 0) ? 0 : 1;
}

void TimeSleepUntil(const Time* _targetTime)
{
    Time* curTime;
    int flag = 0;
    int diff = 0;
    
    curTime = malloc(sizeof(Time));
    if(NULL == curTime)
    {
        return;
    }
    
    flag = clock_gettime(_targetTime->m_clockID, &(curTime->m_time));
    if(flag)
    {
        return;
    }

    diff = subtract(curTime, _targetTime);
    if(diff > 0)
    {
        usleep((unsigned int)diff);
    }

    free(curTime);
    return;
}

void TimeAdd(Time* _result, Time* _added)
{
    _result->m_time.tv_sec += _added->m_time.tv_sec;
    _result->m_time.tv_nsec += _added->m_time.tv_nsec;

    if(_result->m_time.tv_nsec >= BILLION)
    {
        _result->m_time.tv_sec++;
        _result->m_time.tv_nsec -= BILLION;
    }
    
    return;
}
/*
Time timeAdd(Time t1, Time t2)
{
    long sec = t2.tv_sec + t1.tv_sec;
    long nsec = t2.tv_nsec + t1.tv_nsec;
    if (nsec >= BILLION) {
        nsec -= BILLION;
        sec++;
    }
    return (Time){ .tv_sec = sec, .tv_nsec = nsec };
}
*/

/* return in microsec */
int subtract(const Time* _first, const Time* _second)
{
    long nano, sec, res = 0;
    if((_second->m_time.tv_nsec - _first->m_time.tv_nsec) > 0)
    {
        sec = _second->m_time.tv_sec - _first->m_time.tv_sec - 1;
        nano = _second->m_time.tv_nsec - _first->m_time.tv_nsec + BILLION;
    }
    else
    {
        sec = _second->m_time.tv_sec - _first->m_time.tv_sec;
        nano = _second->m_time.tv_nsec - _first->m_time.tv_nsec;
    }
    res = sec * MILLION + nano / 1000;
    return (int)res;
}

/*
void timespec_diff(struct timespec *start, struct timespec *stop,
                   struct timespec *result)
{
    if ((stop->tv_nsec - start->tv_nsec) < 0) {
        result->tv_sec = stop->tv_sec - start->tv_sec - 1;
        result->tv_nsec = stop->tv_nsec - start->tv_nsec + 1000000000;
    } else {
        result->tv_sec = stop->tv_sec - start->tv_sec;
        result->tv_nsec = stop->tv_nsec - start->tv_nsec;
    }

    return;
}
*/





