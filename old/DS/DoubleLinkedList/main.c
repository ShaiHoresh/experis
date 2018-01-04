#include <stdio.h>
#include "doubleLL.h"

void TestCreate();

void TestPushHead();
void TestPushTail();
void TestPopHead();
void TestPopTail();

 
void TestPushHeadPopTail();
void TestPushTailPopHead();

void TestLotsOfPops();

void TestCountReg();
void TestCountempty();
void TestCountone();

void TestIsEmptyReg();
void TestIsEmptyone();
void TestIsEmptyEmpty();

void TestDoubleDestroy();

void PrintFormat(size_t _flag);

int main()
{

    TestCreate();

    TestPushHead();
    TestPushTail();
    TestPopHead();
    TestPopTail();
    
    TestPushHeadPopTail();
    TestPushTailPopHead();

    TestLotsOfPops();
    
    TestCountReg();
    TestCountempty();
    TestCountone();

    TestIsEmptyReg();
    TestIsEmptyone();
    TestIsEmptyEmpty();

    TestDoubleDestroy();

    return 0;
}
/**********************************************************/

void TestCreate()
{
    List* list;
    list = ListCreate();
    if(NULL != list)
    {
        printf("PASSED:     Test Create\n");
    }
    else
    {
        printf("FAILED:     Test Create\n");
    }
    ListDestroy(list);
}

void TestDoubleDestroy()
{
    List* list;
    list = ListCreate();
    ListDestroy(list);
    ListDestroy(list);
    printf("PASSED:     Test Double Destroy\n");
}

void TestPushHead()
{
    ADTErr flag;
    int i;
    List* list;
    list = ListCreate();
    for(i = 0; i < 8; ++i)
    {
        flag = ListPushHead(list, i);
    }
    PrintFormat(flag);
    printf("Test Push Head\n");
    ListDestroy(list);
}
    
void TestPushTail()
{
    ADTErr flag;
    List* list;
    list = ListCreate();
    ListPushTail(list, 1);
    ListPushTail(list, 1);
    ListPushTail(list, 1);
    flag = ListPushTail(list, 1);
    PrintFormat(flag);
    printf("Test Push Tail\n");
    ListDestroy(list);
}

void TestPopHead()
{
    ADTErr flag;
    int data1;
    List* list;
    list = ListCreate();
    ListPushTail(list, 1);
    ListPushTail(list, 1);
    ListPushTail(list, 1);
    ListPopHead(list, &data1);
    flag = ListPopHead(list, &data1);
    if(data1 != 1)
    {
        flag = 0;
    }
    PrintFormat(flag);
    printf("Test Pop Head\n");
    ListDestroy(list);
}

void TestPopTail()
{
    ADTErr flag;
    int data1;
    List* list;
    list = ListCreate();
    ListPushTail(list, 1);
    ListPushTail(list, 1);
    ListPushTail(list, 1);
    ListPopTail(list, &data1);
    flag = ListPopTail(list, &data1);
    if(data1 != 1)
    {
        flag = 0;
    }
    PrintFormat(flag);
    printf("Test Pop Head\n");
    ListDestroy(list);
}

void TestPushHeadPopTail()
{
    List* list;
    ADTErr flag;
    int data1 = 0;
    list = ListCreate();
    ListPushHead(list, 1);
    ListPopTail(list, &data1);
    if(data1 != 1)
    {
        flag = 1;
    }
    PrintFormat(flag);
    printf("Test Push Head Pop Tail\n");
    ListDestroy(list);
}

void TestPushTailPopHead()
{
    List* list;
    ADTErr flag;
    int data1 = 0;
    list = ListCreate();
    ListPushTail(list, 1);
    ListPopHead(list, &data1);
    if(data1 != 1)
    {
        flag = 1;
    }
    PrintFormat(flag);
    printf("Test Push Tail Pop Head\n");
    ListDestroy(list);
}

void TestLotsOfPops()
{
    ADTErr flag;
    int data1;
    List* list;
    int i;
    list = ListCreate();
    ListPushTail(list, 1);
    ListPushTail(list, 1);
    ListPushTail(list, 1);
    ListPopTail(list, &data1);
    for(i = 0; i < 5; ++i)
    {
        flag = ListPopTail(list, &data1);
    }
    PrintFormat(!flag);
    printf("Test Lots Of Pops\n");
    ListDestroy(list);
}


void TestCountReg()
{
    List* list;
    size_t num;
    list = ListCreate();
    ListPushTail(list, 1);
    ListPushTail(list, 1);
    ListPushTail(list, 1);
    num = ListCountItems(list);
    if(num == 3)
    {
        PrintFormat(ERR_OK);
    }
    else
    {
        PrintFormat(!ERR_OK);
    }
    printf("Test Count Regular\n");
    ListDestroy(list);
}

void TestCountempty()
{
    List* list;
    size_t num;
    list = ListCreate();
    num = ListCountItems(list);
    if(num == 0)
    {
        PrintFormat(ERR_OK);
    }
    else
    {
        PrintFormat(!ERR_OK);
    }
    printf("Test Count Empty\n");
    ListDestroy(list);
}


void TestCountone()
{
    List* list;
    size_t num;
    list = ListCreate();
    ListPushTail(list, 1);
    num = ListCountItems(list);
    if(num == 1)
    {
        PrintFormat(ERR_OK);
    }
    else
    {
        PrintFormat(!ERR_OK);
    }
    printf("Test Count One\n");
    ListDestroy(list);
}

void TestIsEmptyReg()
{
    List* list;
    list = ListCreate();
    ListPushTail(list, 1);
    ListPushTail(list, 1);
    
    if(!ListIsEmpty(list))
    {
        PrintFormat(ERR_OK);
    }
    else
    {
        PrintFormat(!ERR_OK);
    }
    printf("Test Is Empty Regular\n");
    ListDestroy(list);
}
void TestIsEmptyone()
{
    List* list;
    list = ListCreate();
    ListPushTail(list, 1);
    if(!ListIsEmpty(list))
    {
        PrintFormat(ERR_OK);
    }
    else
    {
        PrintFormat(!ERR_OK);
    }
    printf("Test Is Empty One\n");
    ListDestroy(list);
}

void TestIsEmptyEmpty()
{
    List* list;
    list = ListCreate();
    if(ListIsEmpty(list))
    {
        PrintFormat(ERR_OK);
    }
    else
    {
        PrintFormat(!ERR_OK);
    }
    printf("Test Is Empty Empty\n");
    ListDestroy(list);
}

void PrintFormat(size_t _flag)
{
    if(_flag == 0)
    {
        printf("PASSED:     ");
    }
    else
    {
        printf("FAILED:     ");
    }
}

