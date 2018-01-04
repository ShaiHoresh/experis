#include <stdio.h> /*printf*/
#include <stdlib.h> /*free*/
#include "../../inc/HashMap.h"
#include "../../inc/mu_test.h"


int keys[] =    {2, 54, 32 ,58, 87 ,65 ,84, 12, 52, 69, 66, 258, 123, 147, 462};
int values[] =  {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};


void PrintFormat(int flag)
{
    flag ? printf("Succeeded:   ") : printf("Failed:        ");
}

int CompareInt(const void* _firstKey, const void* _secondKey)
{
    return *(int*)_firstKey == *(int*)_secondKey;
}

size_t SimpleIntHash(const void* _key)
{
    return (size_t)((*(int*)_key) * (*(int*)_key));
}

void KeyExterminator(void* _key)
{
    free(_key);
}

void ValueExterminator(void* _value)
{
    free(_value);
}

int PrintKeyAndValueInts(const void* _key, void* _value, void* _context)
{
    printf("key = %3d, value = %3d\n", *(int*)_key, *(int*)_value);
    return 1;
}
/*
void TestCreate();
void TestCreateZeroNOI();
void TestInsertFirst();
void TestInsertLotsOfElements();
void TestInsertSameKey();
void TestForEachLotsOfElements();
void TestSize();
void TestFind();
void TestFindNotExist();
void TestReHash();
void TestRemove();
void TestRemoveNotExist();
void TestStatistics();

*/
UNIT(simple_create)
    HashMap* map;
    map = HashMapCreate(10, SimpleIntHash, CompareInt);
	ASSERT_THAT(map != NULL);
    HashMapDestroy(&map, NULL, NULL);
END_UNIT

UNIT(TestCreateZeroNOI)
    HashMap* map;
    map = HashMapCreate(0, SimpleIntHash, CompareInt);
    ASSERT_THAT(map == NULL);
    HashMapDestroy(&map, NULL, NULL);
END_UNIT

UNIT(TestInsertFirst)
    HashMap* map;
    int *a, *b;
    
    a = malloc(sizeof(int));
    b = malloc(sizeof(int));
    *a = 5;
    *b = 12;
    
    map = HashMapCreate(10, SimpleIntHash, CompareInt);
    
    ASSERT_THAT(MAP_SUCCESS == HashMapInsert(map, a, b));

    HashMapDestroy(&map, KeyExterminator, ValueExterminator);    
END_UNIT


TEST_SUITE(framework test)
	TEST(simple_create)
    TEST(TestCreateZeroNOI)
    TEST(TestInsertFirst)
END_SUITE


/*
int main()
{
    TestCreate();
    TestCreateZeroNOI();
    TestInsertFirst();
    TestInsertLotsOfElements();
    TestInsertSameKey();
    TestForEachLotsOfElements();
    TestSize();
    TestFind();
    TestFindNotExist();
    TestRemove();
    TestReHash();
    TestRemoveNotExist();
    TestStatistics();
    
    return 0;
}

void TestCreate()
{
    HashMap* map;
    
    map = HashMapCreate(10, SimpleIntHash, CompareInt);
    PrintFormat(map != NULL);
    printf("Test Create\n");
    
    HashMapDestroy(&map, NULL, NULL);
}

void TestCreateZeroNOI()
{
    HashMap* map;
    
    map = HashMapCreate(0, SimpleIntHash, CompareInt);
    PrintFormat(map == NULL);
    printf("Test Create Zero NOI\n");
    
    HashMapDestroy(&map, NULL, NULL);
}

void TestInsertFirst()
{
    HashMap* map;
    int *a, *b;
    MapResult error;
    
    a = malloc(sizeof(int));
    b = malloc(sizeof(int));
    
    *a = 5;
    *b = 12;
    
    map = HashMapCreate(10, SimpleIntHash, CompareInt);
    
    error = HashMapInsert(map, a, b);
    
    PrintFormat(MAP_SUCCESS == error);
    printf("Test Insert First\n");
    
    HashMapDestroy(&map, KeyExterminator, ValueExterminator);    
}
*/
void TestInsertLotsOfElements()
{
    HashMap* map;
    int *a[15], *b[15];
    size_t i;
    MapResult error;

    map = HashMapCreate(10, SimpleIntHash, CompareInt);
    
    for(i = 0; i < 15; ++i)
    {
        a[i] = malloc(sizeof(int));
        b[i] = malloc(sizeof(int));
        *a[i] = keys[i];
        *b[i] = values[i];
        error = HashMapInsert(map, a[i], b[i]);
        if(error != MAP_SUCCESS)
        {
            break;
        }
    }
    
    PrintFormat(MAP_SUCCESS == error);
    printf("Test Insert Lots Of Elements\n");
    
    HashMapDestroy(&map, KeyExterminator, ValueExterminator); 
}

void TestInsertSameKey()
{
    HashMap* map;
    int *a[2], *b[2];
    size_t i;
    MapResult error;

    map = HashMapCreate(10, SimpleIntHash, CompareInt);
    
    for(i = 0; i < 2; ++i)
    {
        a[i] = malloc(sizeof(int));
        b[i] = malloc(sizeof(int));
        *a[i] = 7;
        *b[i] = values[i];
        error = HashMapInsert(map, a[i], b[i]);
    }
    
    PrintFormat(MAP_KEY_DUPLICATE_ERROR == error);
    printf("Test Insert Same Key\n");
    
    HashMapDestroy(&map, KeyExterminator, ValueExterminator); 
}

void TestForEachLotsOfElements()
{
    HashMap* map;
    int *a[15], *b[15];
    size_t i, counter = 0;
    MapResult error;

    map = HashMapCreate(10, SimpleIntHash, CompareInt);
    
    for(i = 0; i < 15; ++i)
    {
        a[i] = malloc(sizeof(int));
        b[i] = malloc(sizeof(int));
        *a[i] = keys[i];
        *b[i] = values[i];
        error = HashMapInsert(map, a[i], b[i]);
        if(error != MAP_SUCCESS)
        {
            break;
        }
    }
    counter = HashMapForEach(map, PrintKeyAndValueInts, NULL);
    PrintFormat(counter == 15);
    printf("Test For Each\n");
    
    HashMapDestroy(&map, KeyExterminator, ValueExterminator); 
}

void TestSize()
{
    HashMap* map;
    int *a[15], *b[15];
    size_t i, numOfItems = 0;
    MapResult error;

    map = HashMapCreate(10, SimpleIntHash, CompareInt);
    
    for(i = 0; i < 15; ++i)
    {
        a[i] = malloc(sizeof(int));
        b[i] = malloc(sizeof(int));
        *a[i] = keys[i];
        *b[i] = values[i];
        error = HashMapInsert(map, a[i], b[i]);
        if(error != MAP_SUCCESS)
        {
            break;
        }
    }
    
    numOfItems = HashMapSize(map);
    PrintFormat(numOfItems == 15);
    printf("Test Size\n");
    
    HashMapDestroy(&map, KeyExterminator, ValueExterminator); 
}

void TestFind()
{
    HashMap* map;
    int *a[15], *b[15];
    size_t i;
    MapResult error;
    void* value = NULL;

    map = HashMapCreate(10, SimpleIntHash, CompareInt);
    
    for(i = 0; i < 15; ++i)
    {
        a[i] = malloc(sizeof(int));
        b[i] = malloc(sizeof(int));
        *a[i] = keys[i];
        *b[i] = values[i];
        error = HashMapInsert(map, a[i], b[i]);
        if(error != MAP_SUCCESS)
        {
            break;
        }
    }
    error = HashMapFind(map, a[7], &value);
    PrintFormat(error == MAP_SUCCESS && *(int*)value == values[7]);
    printf("Test Find\n");
    
    HashMapDestroy(&map, KeyExterminator, ValueExterminator); 
}

void TestFindNotExist()
{
    HashMap* map;
    int *a[15], *b[15];
    size_t i;
    MapResult error;
    void* value = NULL;

    map = HashMapCreate(10, SimpleIntHash, CompareInt);
    
    for(i = 0; i < 15; ++i)
    {
        a[i] = malloc(sizeof(int));
        b[i] = malloc(sizeof(int));
        *a[i] = keys[i];
        *b[i] = values[i];
        error = HashMapInsert(map, a[i], b[i]);
        if(error != MAP_SUCCESS)
        {
            break;
        }
    }
    a[15] = malloc(sizeof(int));
    *a[15] = 33;
    error = HashMapFind(map, a[15], value);
    free(a[15]);
    PrintFormat(error == MAP_KEY_NOT_FOUND_ERROR && value == NULL);
    printf("Test Find Not Exist\n");
    
    HashMapDestroy(&map, KeyExterminator, ValueExterminator); 
}

void TestReHash()
{
    HashMap* map;
    int *a[15], *b[15];
    size_t i;
    MapResult error;

    map = HashMapCreate(6, SimpleIntHash, CompareInt);
    
    for(i = 0; i < 15; ++i)
    {
        a[i] = malloc(sizeof(int));
        b[i] = malloc(sizeof(int));
        *a[i] = keys[i];
        *b[i] = values[i];
        error = HashMapInsert(map, a[i], b[i]);
    }
   /* HashMapForEach(map, PrintKeyAndValueInts, NULL);*/
    error = HashMapRehash(map, 15);
  /*  counter = HashMapForEach(map, PrintKeyAndValueInts, NULL);*/
    PrintFormat(error == MAP_SUCCESS);
    printf("Test ReHash\n");
    
    HashMapDestroy(&map, KeyExterminator, ValueExterminator); 
}


void TestRemove()
{
    HashMap* map;
    int *a[15], *b[15];
    size_t i;
    MapResult error;
    void* key = NULL;
    void* value = NULL;

    map = HashMapCreate(6, SimpleIntHash, CompareInt);
    
    for(i = 0; i < 15; ++i)
    {
        a[i] = malloc(sizeof(int));
        b[i] = malloc(sizeof(int));
        *a[i] = keys[i];
        *b[i] = values[i];
        error = HashMapInsert(map, a[i], b[i]);
        if(error != MAP_SUCCESS)
        {
            break;
        }
    }
    error = HashMapRemove(map, a[2], &key, &value);
   /* HashMapForEach(map, PrintKeyAndValueInts, NULL);*/
    PrintFormat(error == MAP_SUCCESS);
    printf("Test Remove\n");
    
    HashMapDestroy(&map, KeyExterminator, ValueExterminator); 
}

void TestRemoveNotExist()
{
    HashMap* map;
    int *a[15], *b[15], *c, *d;
    size_t i;
    MapResult error;
    void* key = NULL;
    void* value = NULL;

    map = HashMapCreate(6, SimpleIntHash, CompareInt);
    
    for(i = 0; i < 14; ++i)
    {
        a[i] = malloc(sizeof(int));
        b[i] = malloc(sizeof(int));
        *a[i] = keys[i];
        *b[i] = values[i];
        error = HashMapInsert(map, a[i], b[i]);
        if(error != MAP_SUCCESS)
        {
            break;
        }
    }
    c = malloc(sizeof(int));
    d = malloc(sizeof(int));
    *c = keys[15];
    *d = values[15];
    error = HashMapRemove(map, c, &key, &value);
   /* HashMapForEach(map, PrintKeyAndValueInts, NULL);*/
    PrintFormat(error == MAP_KEY_NOT_FOUND_ERROR);
    printf("Test Remove Not Exist\n");
    
    free(c);
    free(d);
    
    HashMapDestroy(&map, KeyExterminator, ValueExterminator); 
}

void TestStatistics()
{
    HashMap* map;
    int *a[15], *b[15];
    size_t i;
    MapResult error;
    MapStats stats;

    map = HashMapCreate(5, SimpleIntHash, CompareInt);
    
    for(i = 0; i < 15; ++i)
    {
        a[i] = malloc(sizeof(int));
        b[i] = malloc(sizeof(int));
        *a[i] = keys[i];
        *b[i] = values[i];
        error = HashMapInsert(map, a[i], b[i]);
        if(error != MAP_SUCCESS)
        {
            break;
        }
    }
    
    stats = HashMapGetStatistics(map);
    
    printf("pairs# = %u\ncollisions = %u\nbuckets = %u\nchains = %u\nmaxChainLength = %u\naverage = %u\n", stats.m_pairs, stats.m_collisions, stats.m_buckets, stats.m_chains, stats.m_maxChainLength, stats.m_averageChainLength);
    
    PrintFormat(MAP_SUCCESS == error);
    printf("Test Insert Lots Of Elements\n");
    
    HashMapDestroy(&map, KeyExterminator, ValueExterminator); 
}
