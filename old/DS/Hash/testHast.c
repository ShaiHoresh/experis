#include <stdio.h>
#include "Hash.h"

void TestCreateNormal();
void TestCreateSizeZero();
void TestInsertnormal();
void TestInsertOverFlow();
void TestInsertExisting();
void TestInsertZeroAndNegative();
void TestRemoveNormal();
void TestRemoveNotExisting();
void TestRemoveToNULL();
void TestFindExist();
void TestFindNotExist();
void TestFindZeroAndNegative();
void TestHashNumOfItemsZero();
void TestHashNumOfItemsNormal();
void TestHashNumOfItemsAfterEmptying();
void TestHashCapacity();
void TestHashAverageCollisionsEmpty();
void TestHashAverageCollisionsNormal();
void TestHashMaxCollisionsEmpty();
void TestHashMaxCollisionsNormal();


void PrintFormat(size_t _flag);

int main()
{

    TestCreateNormal();
    TestCreateSizeZero();
    TestInsertnormal();
    TestInsertOverFlow();
    TestInsertExisting();
    TestInsertZeroAndNegative();
    TestRemoveNormal();
    TestRemoveNotExisting();
    TestRemoveToNULL();
    TestFindExist();
    TestFindNotExist();
    TestFindZeroAndNegative();
    TestHashNumOfItemsZero();
    TestHashNumOfItemsNormal();
    TestHashNumOfItemsAfterEmptying();
    TestHashCapacity();
    TestHashAverageCollisionsEmpty();
    TestHashAverageCollisionsNormal();
    TestHashMaxCollisionsEmpty();
    TestHashMaxCollisionsNormal();
    return 0;
}

void TestCreateNormal()
{
    Hash* hash;
    hash = HashCreate(5);
    PrintFormat((size_t)hash);
    printf("TestCreateNormal\n");
    HashDestroy(hash);
}


void TestCreateSizeZero()
{
    Hash* hash;
    hash = HashCreate(0);
    PrintFormat(!(size_t)hash);
    printf("TestCreateSizeZero\n");
    HashDestroy(hash);
}

void TestInsertnormal()
{
    Hash* hash;
    ADTErr flag;
    hash = HashCreate(6);
    flag = HashInsert(hash, 43);
    flag = HashInsert(hash, 34);
    PrintFormat(!(size_t)flag);
    printf("TestInsertnormal\n");
    HashDestroy(hash);
}

void TestInsertOverFlow()
{
    Hash* hash;
    ADTErr flag;
    hash = HashCreate(6);
    flag = HashInsert(hash, 43);
    flag = HashInsert(hash, 34);
    flag = HashInsert(hash, 23);
    flag = HashInsert(hash, 37);
    flag = HashInsert(hash, 45);
    flag = HashInsert(hash, 345);
    flag = HashInsert(hash, 123);
    flag = HashInsert(hash, 534);
    PrintFormat((size_t)flag);
    printf("TestInsertOverFlow\n");
    HashDestroy(hash);
}
void TestInsertExisting()
{
    Hash* hash;
    ADTErr flag;
    hash = HashCreate(6);
    flag = HashInsert(hash, 43);
    flag = HashInsert(hash, 34);
    flag = HashInsert(hash, 23);
    flag = HashInsert(hash, 37);
    flag = HashInsert(hash, 45);
    flag = HashInsert(hash, 37);
    flag = HashInsert(hash, 45);
    PrintFormat((size_t)flag);
    printf("TestInsertExisting\n");
    HashDestroy(hash);
}
void TestInsertZeroAndNegative()
{
    Hash* hash;
    ADTErr flag1, flag2;
    hash = HashCreate(6);
    HashInsert(hash, 43);
    flag1 = HashInsert(hash, -5);
    PrintFormat((size_t)flag1);
    printf("TestInsertNegative\n");
    flag2 = HashInsert(hash, 0);

    PrintFormat((size_t)flag2);
    printf("TestInsertZero\n");
    HashDestroy(hash);
}

void TestRemoveNormal()
{
    Hash* hash;
    ADTErr flag;
    
    hash = HashCreate(6);
    HashInsert(hash, 43);
    HashInsert(hash, 34);
    HashInsert(hash, 23);
    HashInsert(hash, 37);
    HashInsert(hash, 45);
    HashInsert(hash, 345);
    flag = HashRemove(hash, 34);
    PrintFormat((size_t)flag);
    printf("TestRemoveNormal\n");
    HashDestroy(hash);
}    
    
void TestRemoveNotExisting()
{
    Hash* hash;
    ADTErr flag;
    
    hash = HashCreate(6);
    HashInsert(hash, 43);
    HashInsert(hash, 34);
    HashInsert(hash, 23);
    HashInsert(hash, 37);
    HashInsert(hash, 45);
    HashInsert(hash, 345);
    flag = HashRemove(hash, 156);
    PrintFormat(!(size_t)flag);
    printf("TestRemoveNotExisting\n");
    HashDestroy(hash);
}    

void TestRemoveToNULL()
{
    Hash* hash;
    ADTErr flag;
    
    hash = NULL;
    flag = HashRemove(hash, 156);
    PrintFormat((size_t)flag);
    printf("TestRemoveToNULL\n");
    HashDestroy(hash);
}    

void TestFindExist()
{
    Hash* hash;
    int flag;
    
    hash = HashCreate(6);
    HashInsert(hash, 43);
    HashInsert(hash, 34);
    HashInsert(hash, 23);
    HashInsert(hash, 37);
    HashInsert(hash, 45);
    HashInsert(hash, 345);
    flag = HashIsFound(hash, 23);
    PrintFormat((size_t)flag);
    printf("TestFindExist\n");
    HashDestroy(hash);
}    

void TestFindNotExist()
{
    Hash* hash;
    int flag;
    
    hash = HashCreate(6);
    HashInsert(hash, 43);
    HashInsert(hash, 34);
    HashInsert(hash, 23);
    HashInsert(hash, 37);
    HashInsert(hash, 45);
    HashInsert(hash, 345);
    flag = HashIsFound(hash, 465);
    PrintFormat(!(size_t)flag);
    printf("TestFindNotExist\n");
    HashDestroy(hash);
}  

void TestFindZeroAndNegative()
{
    Hash* hash;
    int flag1, flag2;
    hash = HashCreate(6);
    HashInsert(hash, 43);
    flag1 = HashIsFound(hash, -5);
    PrintFormat(!(size_t)flag1);
    printf("TestFindZero\n");
    flag2 = HashIsFound(hash, 0);

    PrintFormat(!(size_t)flag2);
    printf("TestFindNegative\n");
    HashDestroy(hash);
}

void TestHashNumOfItemsZero()
{
    Hash* hash;
    size_t flag;
    hash = HashCreate(6);
    flag = HashNumOfItems(hash);
    PrintFormat(0 == flag);
    printf("TestHashNumOfItemsZero\n");
    HashDestroy(hash);
}

void TestHashNumOfItemsNormal()
{
    Hash* hash;
    size_t flag;
    hash = HashCreate(6);
    HashInsert(hash, 34);
    HashInsert(hash, 23);
    flag = HashNumOfItems(hash);
    PrintFormat(2 == flag);
    printf("TestHashNumOfItemsNormal\n");
    HashDestroy(hash);
}

void TestHashNumOfItemsAfterEmptying()
{
    Hash* hash;
    size_t flag;
    hash = HashCreate(6);
    HashInsert(hash, 34);
    HashInsert(hash, 23);
    HashRemove(hash, 34);
    HashRemove(hash, 23 );
    flag = HashNumOfItems(hash);
    PrintFormat(0 == flag);
    printf("TestHashNumOfItemsAfterEmptying\n");
    HashDestroy(hash);
}

void TestHashCapacity()
{
    Hash* hash;
    size_t flag;
    hash = HashCreate(6);
    HashInsert(hash, 34);
    HashInsert(hash, 23);
    flag = HashCapacity(hash);
    PrintFormat(6 == flag);
    printf("TestHashCapacity\n");
    HashDestroy(hash);
}

void TestHashAverageCollisionsEmpty()
{
    Hash* hash;
    double flag;
    hash = HashCreate(6);
    flag = HashAverageCollisions(hash);
    PrintFormat(0 == flag);
    printf("TestHashAverageCollisionsEmpty\n");
    HashDestroy(hash);
}

void TestHashAverageCollisionsNormal()
{
    Hash* hash;
    double flag;
    hash = HashCreate(6);
    HashInsert(hash, 43);
    HashInsert(hash, 34);
    HashInsert(hash, 23);
    HashInsert(hash, 37);
    HashInsert(hash, 45);
    HashInsert(hash, 345);
    flag = HashAverageCollisions(hash);
    PrintFormat(0 != flag);
    printf("TestHashAverageCollisionsNormal\n");
    HashDestroy(hash);
}

void TestHashMaxCollisionsEmpty()
{
    Hash* hash;
    size_t flag;
    hash = HashCreate(6);
    flag = HashMaxCollisions(hash);
    PrintFormat(0 == flag);
    printf("TestHashMaxCollisionsEmpty\n");
    HashDestroy(hash);
}
void TestHashMaxCollisionsNormal()
{
    Hash* hash;
    size_t flag;
    hash = HashCreate(6);
    HashInsert(hash, 43);
    HashInsert(hash, 34);
    HashInsert(hash, 23);
    HashInsert(hash, 37);
    HashInsert(hash, 45);
    HashInsert(hash, 345);
    flag = HashMaxCollisions(hash);
    PrintFormat(0 != flag);
    printf("TestHashMaxCollisionsNormal\n");
    HashDestroy(hash);
}

void PrintFormat(size_t _flag)
{
    if(_flag != 0)
    {
        printf("PASSED:     ");
    }
    else
    {
        printf("FAILED:     ");
    }
}
