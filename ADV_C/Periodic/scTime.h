#ifndef __SCTIME_H__
#define __SCTIME_H__

/*************************/
/*TIME API FUNCTIONS*/
/*************************/

#include <time.h>


typedef struct Time Time;


/**
 *
 *
 * @warning be aware to use a valid clockid_t
 */
Time* TimeCreate(int _milliSecs);

Time* TimeCreateCurrent(const clockid_t _clockID);

void TimeDestroy(Time*);

/**
 *
 * @retval 0 if first sooner (smaller)/ 1 if second sooner
 */

int	TimeCompare(const Time* _first, const Time* _second);

void TimeSleepUntil(const Time*);

void TimeAdd(Time* _result, Time* _added);


/* TEMPORARY HERE */
int subtract(const Time* _first, const Time* _second);

#endif /* #ifndef __SCTIME_H__ */
