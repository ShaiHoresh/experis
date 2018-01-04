#include <stdio.h>
#include "../../inc/mu_test.h"
#include "Task.h"

static void printTime(struct timespec _time)
{
    printf("%ld:%09ld\n", _time.tv_sec, _time.tv_nsec);
}

int PrintTask(void* _cont)
{
    struct timespec t;
    printf("in print task\n");
    clock_gettime(CLOCK_REALTIME, &(t));
    printTime(t);
    return (int)_cont;
}

UNIT(Test_Create_Normal)
	Task* task;
	int a = 5;
	task = TaskCreate(PrintTask, &a, 200, CLOCK_REALTIME);
    ASSERT_THAT(task != NULL);
    TaskDestroy(task);
END_UNIT

UNIT(Test_Execute)
	Task* task;
	int a = 5;
	task = TaskCreate(PrintTask, &a, 200, CLOCK_REALTIME);
	TaskExecute(task);
    ASSERT_THAT(task != NULL);
    TaskDestroy(task);
END_UNIT

UNIT(Test_Calculate_Next)
	Task* task;
	int a = 5;
	task = TaskCreate(PrintTask, &a, 1000, CLOCK_REALTIME);
	TaskExecute(task);
	for(a = 5; a > 0; --a)
	{
	    TaskCalculateNext(task);
	    TaskExecute(task);
    }
    ASSERT_THAT(task != NULL);
    TaskDestroy(task);
END_UNIT

TEST_SUITE(framework test)
    TEST(Test_Create_Normal)
    TEST(Test_Execute)
    TEST(Test_Calculate_Next)
END_SUITE
