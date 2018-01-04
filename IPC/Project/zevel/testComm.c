#include <stdio.h>


#include "mu_test.h"
#include "processor.h"
#include "comm.h"


/* =============================     */

/*            DEFINITIONS            */

/* =============================     */    



/* =============================     */

/*    AUX FUNCTION DECLARATION       */

/* =============================     */    



/* =============================     */

/*              TESTS                */

/* =============================     */    

UNIT(TestCreate)
    CommData* comm = CommCreate(NULL);
    ASSERT_THAT(comm != NULL);
    CommClose(comm);
END_UNIT

UNIT(TestPush)
    int res;
    CommData* comm;
    CDRData context;
    
    comm = CommCreate(NULL);
    context = CDRGenerator(1);
    
    res = PushData(comm, &context);
    CommClose(comm);
    ASSERT_THAT(res == 0);
END_UNIT

UNIT(TestPull)
    int res;
    CommData* comm;
    CDRData context, context2;
    
    comm = CommCreate(NULL);
    context = CDRGenerator(2);
    PushData(comm, &context);
    CDRprint(context);
    res = PullData(comm, &context2);
    CDRprint(context2);
    CommClose(comm);
    ASSERT_THAT(res == 0);
END_UNIT

/* =============================     */

/*            TEST SUIT              */

/* =============================     */    



TEST_SUITE(title)

    TEST(TestCreate)
    TEST(TestPush)
    TEST(TestPull)

END_SUITE

    

/* =============================     */

/*        AUX FUNCTION DEFINITION        */

/* =============================     */
