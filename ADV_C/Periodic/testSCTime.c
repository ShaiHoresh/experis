#include <stdio.h>
#include <unistd.h>
#include "../../inc/mu_test.h"
#include "scTime.h"

UNIT(Test_Create_Normal)
	Time* time;
	time = TimeCreate(200);
    ASSERT_THAT(time != NULL);
    TimeDestroy(time);
END_UNIT

UNIT(Test_Create_Current)
	Time* time;
	time = TimeCreateCurrent(CLOCK_REALTIME);
    ASSERT_THAT(time != NULL);
    TimeDestroy(time);
END_UNIT

UNIT(Test_Time_Compare_First_Smaller)
	Time *time1, *time2;
	int res;
	
	time1 = TimeCreate(500);
	time2 = TimeCreateCurrent(CLOCK_REALTIME);
	TimeAdd(time1, time2);
	res = TimeCompare(time1, time2);

    ASSERT_THAT(res == 0);
    TimeDestroy(time1);
    TimeDestroy(time2);
END_UNIT

UNIT(Test_Time_Compare_First_Bigger)
	Time *time1, *time2;
	int res;
	
	time1 = TimeCreate(500);
	time2 = TimeCreateCurrent(CLOCK_REALTIME);
	TimeAdd(time1, time2);
	res = TimeCompare(time2, time1);
	
    ASSERT_THAT(res == 1);
    TimeDestroy(time1);
    TimeDestroy(time2);
END_UNIT

UNIT(Test_Time_Sleep_Until)
Time *time1, *time2;
	int res;
	
	time1 = TimeCreate(10000);
	time2 = TimeCreateCurrent(CLOCK_REALTIME);
	TimeAdd(time1, time2);
	TimeSleepUntil(time1);
    ASSERT_THAT(time1 != NULL);
    TimeDestroy(time1);
    TimeDestroy(time2);
END_UNIT


TEST_SUITE(framework test)
	TEST(Test_Create_Normal)
	TEST(Test_Create_Current)
	TEST(Test_Time_Compare_First_Smaller)
	TEST(Test_Time_Compare_First_Bigger)
	TEST(Test_Time_Sleep_Until)

END_SUITE
