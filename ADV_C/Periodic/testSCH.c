#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../../inc/Scheduler.h"
#include "../../inc/mu_test.h"

int g_counter = 5;

typedef struct Data
{
    int                 m_counter;
    PeriodicExecutor*   m_pe;
    int                 m_pauseRet;
} Data;


static void printTime(struct timespec _time)
{
    printf("%ld:%09ld\n", _time.tv_sec, _time.tv_nsec);
}

int PrintTask(Data* _cont)
{
    struct timespec t;
    printf("in print task : %d\n", _cont->m_counter);
    clock_gettime(CLOCK_REALTIME, &(t));
    printTime(t);
    usleep((unsigned int)_cont->m_counter * 500);
    clock_gettime(CLOCK_REALTIME, &(t));
    printTime(t);
    _cont->m_counter--;
    if(1 == _cont->m_counter)
    {
        _cont->m_pauseRet = PeriodicExecutorPause(_cont->m_pe);
    }
    return 1;
}

UNIT(PrintTime)
    struct timespec t;
    clock_gettime(CLOCK_REALTIME, &(t));
    printTime(t);
END_UNIT
/*
UNIT(Test_Create_Normal)
    PeriodicExecutor* pe;
    pe = PeriodicExecutorCreate("module1", CLOCK_REALTIME);
    ASSERT_THAT(pe != NULL);
END_UNIT

UNIT(Test_ADD)
    PeriodicExecutor* pe;
    int res, a = 5;
    pe = PeriodicExecutorCreate("module1", CLOCK_REALTIME);
    res = PeriodicExecutorAdd(pe, PrintTask, &a, 50);
    ASSERT_THAT(1 == res);
END_UNIT
*/
UNIT(Test_Run)
    Data* data;
    PeriodicExecutor* pe;
    int res;
    data = malloc(sizeof(Data));
    data->m_counter = 5;
    pe = PeriodicExecutorCreate("module1", CLOCK_REALTIME);
    data->m_pe = pe;
    PeriodicExecutorAdd(pe, PrintTask, data, 1000);
/*    PeriodicExecutorAdd(pe, PrintTask, a, 1000);
    PeriodicExecutorAdd(pe, PrintTask, a, 950);
*/
    res = PeriodicExecutorRun(pe);
    ASSERT_THAT(4 == res && data->m_pauseRet == 0);
END_UNIT



TEST_SUITE(framework test)
/*    TEST(Test_Create_Normal)
    TEST(Test_ADD)
 */   TEST(PrintTime)
    TEST(Test_Run)
    TEST(PrintTime)
END_SUITE
