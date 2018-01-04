
#include <stdio.h> /*printf*/
#include <stdlib.h> /*free*/
#include "Alloc.h"
#include "../../inc/mu_test.h"


UNIT(simple_create)
    Buffer* buffer = NULL;
    buffer = CreateBuffer(10, 10);
	ASSERT_THAT(buffer != NULL);
	DestroyBuffer(buffer);
END_UNIT

UNIT(simple_alloc)
    Buffer* buffer;
    void* chunk = NULL;
    buffer = CreateBuffer(10, 10);
	chunk = MyMalloc(buffer);
	printf("%p\n", chunk);
	ASSERT_THAT(chunk != NULL);
	DestroyBuffer(buffer);
END_UNIT

UNIT(simple_free)
    Buffer* buffer;
    void* chunk = NULL;
    buffer = CreateBuffer(10, 10);
	chunk = MyMalloc(buffer);
	buffer = MyFree(buffer, chunk);
	ASSERT_THAT(chunk != NULL);
	DestroyBuffer(buffer);
END_UNIT

UNIT(Test_alloc_a_few)
    Buffer* buffer;
    void* chunk[5];
    size_t i = 0;
    buffer = CreateBuffer(10, 10);
	for(i = 0; i < 5; ++i)
	{
		chunk[i] = MyMalloc(buffer);
		printf("%p\n", chunk[i]);
	}
	for(i = 0; i < 5; ++i)
	{
    	buffer = MyFree(buffer, chunk[i]);
	}
	printf("\n");
	ASSERT_THAT(chunk[1] + 18 == chunk[2]);
	DestroyBuffer(buffer);
END_UNIT

UNIT(Test_Free_All)
    Buffer* buffer;
    void* chunk[5], *test;
    size_t i = 0;
    buffer = CreateBuffer(10, 10);
	for(i = 0; i < 5; ++i)
	{
		chunk[i] = MyMalloc(buffer);
		printf("%d: %p\n", i, chunk[i]);
	}
	for(i = 0; i < 5; ++i)
	{
    	buffer = MyFree(buffer, chunk[i]);
    	printf("%d: %p\n", i, chunk[i]);
	}
	for(i = 0; i < 5; ++i)
	{
		chunk[i] = MyMalloc(buffer);
		printf("%d: %p\n", i, chunk[i]);
		buffer = MyFree(buffer, chunk[i]);
	}
	ASSERT_THAT(chunk[1] + 18 == chunk[2]);
	DestroyBuffer(buffer);
END_UNIT 

TEST_SUITE(framework test)
	TEST(simple_create)
	TEST(simple_alloc)
    TEST(simple_free)
    TEST(Test_alloc_a_few)
    TEST(Test_Free_All)
END_SUITE






