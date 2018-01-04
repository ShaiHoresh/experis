#include <stdio.h> /*printf*/
#include <stdlib.h> /*malloc, rand, srand*/
#include <time.h> /*time*/
#include "../../inc/DoubleLL.h"

int DestroyElem(void* _element, void *_context)
{
    free(_element);
    return 0;
}

int CompareInt(void* _element, void *_context)
{
    return((*(int*)_element != *(int*)_context));
}

int LessInt(void* _a, void* _b)
{
    return *(int*)_a > *(int*)_b;
}

int ElementPrintInt(void* _element, void *_context)
{
    printf("%d ", *(int*)_element);
    return 0;
}

void TestCreate();
void TestDestroy();
void TestDoubleDestroy();

void TestPushHeadOrder();
void TestPushHeadTypes();
void TestPushTailOrder();
void TestPushTailTypes();

void TestPopHeadNormal();
void TestPopHeadEmpty();
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

void FindFirstForwardFound();
void FindFirstForwardNotFound();

void FindFirstBackwardFound();
void FindFirstBackwardNotFound();

void SortIntegers();
void SortIntegersPartly();
void TestCountIf();

void TestDoubleDestroy();

void PrintFormat(size_t _flag);

int main()
{
   /* srand(time(NULL));*/
    TestCreate();
    
    TestDestroy();
    TestDoubleDestroy();

    TestPushHeadOrder();
    TestPushHeadTypes();
    TestPushTailOrder();
    TestPushTailTypes();

    TestPopHeadNormal();
    TestPopHeadEmpty();

    TestPopTail();
    
    TestPushHeadPopTail();
    TestPushTailPopHead();

/*    TestLotsOfPops();*/
    
    TestCountReg();
    TestCountempty();
    TestCountone();

    TestIsEmptyReg();
    TestIsEmptyone();
    TestIsEmptyEmpty();
    
    FindFirstForwardFound();
    FindFirstForwardNotFound();
    
    FindFirstBackwardFound();
    FindFirstBackwardNotFound();
    
    SortIntegers();
    SortIntegersPartly();
    TestCountIf();
    

    return 0;
}
/**********************************************************/

void TestCreate()
{
    List* list = NULL;
    list = ListCreate();
    if(NULL != list)
    {
        printf("PASSED:     Test Create\n");
    }
    else
    {
        printf("FAILED:     Test Create\n");
    }
    ListDestroy(&list, DestroyElem);
}

void TestDestroy()
{
    List* list;
    list = ListCreate();
    ListDestroy(&list, DestroyElem);
    
    PrintFormat(!(NULL == list));
    printf("Test Destroy\n");
}

void TestDoubleDestroy()
{
    List* list;
    list = ListCreate();
    ListDestroy(&list, DestroyElem);
    ListDestroy(&list, DestroyElem);
    printf("PASSED:     Test Double Destroy\n");
}

void TestPushHeadTypes()
{
    ListErrors flagA, flagB, flagC;

    int *a = NULL;
    char *b = NULL;
    char** c = NULL;
    List* list;
    list = ListCreate();
    
    a = malloc(sizeof(int));
    b = malloc(sizeof(char));
    c = malloc(4 * sizeof(char));
    
    *a = 4;
    *b = 'f';
    *c = "Hey";
    
    flagA = ListPushHead(list, a);
    flagB = ListPushHead(list, b);
    flagC = ListPushHead(list, c);

    PrintFormat(flagA && flagB && flagC);
    printf("Test Push Head Types\n");
    ListDestroy(&list, DestroyElem);
}

void TestPushHeadOrder()
{
    ListErrors flagA, flagB, flagC;

    int *a = NULL, *b = NULL, *c = NULL;
    List* list = NULL;
    int* data = NULL;
    list = ListCreate();
    
    a = malloc(sizeof(int));
    b = malloc(sizeof(int));
    c = malloc(sizeof(int));
    
    *a = 4;
    *b = 6;
    *c = 5;
    
    flagA = ListPushHead(list, a);
    flagB = ListPushHead(list, b);
    flagC = ListPushHead(list, c);
    
    ListPopHead(list, (void**)&data);

    PrintFormat(flagA && flagB && flagC && *data == *c);
    printf("Test Push Head Order\n");
    ListDestroy(&list, DestroyElem);
}

void TestPushTailTypes()
{
    ListErrors flagA, flagB, flagC;

    int *a = NULL;
    char *b = NULL;
    char** c = NULL;
    List* list;
    list = ListCreate();
    
    a = malloc(sizeof(int));
    b = malloc(sizeof(char));
    c = malloc(4 * sizeof(char));
    
    *a = 4;
    *b = 'f';
    *c = "Hey";
    
    flagA = ListPushTail(list, a);
    flagB = ListPushTail(list, b);
    flagC = ListPushTail(list, c);

    PrintFormat(flagA && flagB && flagC);
    printf("Test Push Tail Types\n");
    ListDestroy(&list, DestroyElem);
}
 
void TestPushTailOrder()
{
    ListErrors flagA, flagB, flagC;

    int *a = NULL, *b = NULL, *c = NULL;
    List* list = NULL;
    int* data = NULL;
    list = ListCreate();
    
    a = malloc(sizeof(int));
    b = malloc(sizeof(int));
    c = malloc(sizeof(int));
    
    *a = 4;
    *b = 6;
    *c = 5;
    
    flagA = ListPushTail(list, a);
    flagB = ListPushTail(list, b);
    flagC = ListPushTail(list, c);
    
    ListPopTail(list, (void**)&data);

    PrintFormat(flagA && flagB && flagC && *data == *c);
    printf("Test Push Tail Order\n");
    ListDestroy(&list, DestroyElem);
} 
 
void TestPopHeadNormal()
{
    ListErrors flag;

    int *a = NULL, *b = NULL, *c = NULL;
    void* data1;
    List* list;

    list = ListCreate();
    
    a = malloc(sizeof(int));
    b = malloc(sizeof(int));
    c = malloc(sizeof(int));
    
    *a = 4;
    *b = 6;
    *c = 3;
    
    ListPushHead(list, a);
    ListPushHead(list, b);
    ListPushHead(list, c);
    
    flag = ListPopHead(list, &data1);
    PrintFormat(flag && (*(int*)data1 == 3));
    printf("Test Pop Head Normal\n");
    ListDestroy(&list, DestroyElem);
}

void TestPopHeadEmpty()
{
    ListErrors flag;
    void* data1;
    List* list;

    list = ListCreate();

    flag = ListPopHead(list, &data1);
    PrintFormat(!flag);
    printf("Test Pop Head Empty List\n");
    ListDestroy(&list, DestroyElem);
}

void TestPopTail()
{
    ListErrors flag;

    int *a = NULL, *b = NULL, *c = NULL;
    void* data1;
    List* list;

    list = ListCreate();
    
    a = malloc(sizeof(int));
    b = malloc(sizeof(int));
    c = malloc(sizeof(int));
    
    *a = 4;
    *b = 6;
    *c = 3;
    
    ListPushTail(list, a);
    ListPushTail(list, b);
    ListPushTail(list, c);
    
    flag = ListPopTail(list, &data1);
    PrintFormat(flag && (*(int*)data1 == 3));
    printf("Test Pop Tail\n");
    ListDestroy(&list, DestroyElem);
}

void TestPushHeadPopTail()
{
    ListErrors flag;

    int *a = NULL, *b = NULL, *c = NULL;
    void* data1;
    List* list;

    list = ListCreate();
    
    a = malloc(sizeof(int));
    b = malloc(sizeof(int));
    c = malloc(sizeof(int));
    
    *a = 4;
    *b = 6;
    *c = 3;
    
    ListPushHead(list, a);
    ListPushHead(list, b);
    ListPushHead(list, c);
    
    flag = ListPopTail(list, &data1);
    PrintFormat(flag && (*(int*)data1 == 4));
    printf("Test Push Head Pop Tail\n");
    ListDestroy(&list, DestroyElem);
}

void TestPushTailPopHead()
{
    ListErrors flag;

    int *a = NULL, *b = NULL, *c = NULL;
    void* data1;
    List* list;

    list = ListCreate();
    
    a = malloc(sizeof(int));
    b = malloc(sizeof(int));
    c = malloc(sizeof(int));
    
    *a = 4;
    *b = 6;
    *c = 3;
    
    ListPushTail(list, a);
    ListPushTail(list, b);
    ListPushTail(list, c);
    
    flag = ListPopHead(list, &data1);
    PrintFormat(flag && (*(int*)data1 == 4));
    printf("Test Push Tail Pop Head\n");
    ListDestroy(&list, DestroyElem);
}
/*
void TestLotsOfPops()
{
    ListErrors flag;
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
    ListDestroy(&list, DestroyElem);
}
*/

void TestCountReg()
{
    size_t num;
    int *a = NULL, *b = NULL, *c = NULL;
    List* list;

    list = ListCreate();
    
    a = malloc(sizeof(int));
    b = malloc(sizeof(int));
    c = malloc(sizeof(int));
    
    *a = 4;
    *b = 6;
    *c = 3;
    
    ListPushTail(list, a);
    ListPushTail(list, b);
    ListPushTail(list, c);
    num = ListCountItems(list);
    
    PrintFormat(num != 3);

    printf("Test Count Regular\n");
    ListDestroy(&list, DestroyElem);
}

void TestCountempty()
{
    List* list;
    size_t num;
    list = ListCreate();
    num = ListCountItems(list);
    PrintFormat(num != 0);

    printf("Test Count Empty\n");
    ListDestroy(&list, DestroyElem);
}


void TestCountone()
{
    size_t num;
    int *a = NULL;
    List* list;

    list = ListCreate();
    
    a = malloc(sizeof(int));

    *a = 4;

    ListPushTail(list, a);

    num = ListCountItems(list);
    PrintFormat(num != 1);
    printf("Test Count One\n");
    ListDestroy(&list, DestroyElem);
}

void TestIsEmptyReg()
{
    int *a = NULL, *b = NULL, *c = NULL;
    List* list;

    list = ListCreate();
    
    a = malloc(sizeof(int));
    b = malloc(sizeof(int));
    c = malloc(sizeof(int));
    
    *a = 4;
    *b = 6;
    *c = 3;
    
    ListPushTail(list, a);
    ListPushTail(list, b);
    ListPushTail(list, c);
    
    PrintFormat((size_t)ListIsEmpty(list));
    
    printf("Test Is Empty Regular\n");
    ListDestroy(&list, DestroyElem);
}

void TestIsEmptyone()
{
    int *a = NULL;
    List* list;

    list = ListCreate();
    
    a = malloc(sizeof(int));

    *a = 4;
    
    ListPushTail(list, a);

    PrintFormat((size_t)ListIsEmpty(list));
    printf("Test Is Empty One\n");
    ListDestroy(&list, DestroyElem);
}

void TestIsEmptyEmpty()
{
    List* list;
    list = ListCreate();
    PrintFormat(!(size_t)ListIsEmpty(list));
    printf("Test Is Empty Empty\n");
    ListDestroy(&list, DestroyElem);
}

void FindFirstForwardFound()
{
    int *a = NULL, *b = NULL, *c = NULL;
    List* list = NULL;
    ListErrors errFlag = LIST_OK;
    void* item = NULL;
    int g = 3;

    item = &g;

    list = ListCreate();
    
    a = malloc(sizeof(int));
    b = malloc(sizeof(int));
    c = malloc(sizeof(int));
    
    *a = 4;
    *b = 6;
    *c = 3;
    
    ListPushTail(list, a);
    ListPushTail(list, b);
    ListPushTail(list, c);
    
    errFlag = FindFirstForward(list, CompareInt, b, item);
    
    PrintFormat(errFlag || (item == b));

    printf("Test find First Forward exist data\n");
    ListDestroy(&list, DestroyElem);
}

void FindFirstForwardNotFound()
{
    int *a = NULL, *b = NULL, *c = NULL, *d = NULL;
    ListErrors errFlag = LIST_OK;
    List* list = NULL;
    void* item = NULL;
    int g = 19;

    item = &g;
    
    list = ListCreate();
    
    a = malloc(sizeof(int));
    b = malloc(sizeof(int));
    c = malloc(sizeof(int));
    d = malloc(sizeof(int));
    
    *a = 4;
    *b = 6;
    *c = 3;
    *d = 8;
    
    ListPushTail(list, a);
    ListPushTail(list, b);
    ListPushTail(list, c);
    
    errFlag = FindFirstForward(list, CompareInt, d, &item);
    
    PrintFormat(errFlag || (item == NULL));
    printf("Test find not exist data\n");
    ListDestroy(&list, DestroyElem);
}


void FindFirstBackwardFound()
{
    int *a = NULL, *b = NULL, *c = NULL;
    List* list = NULL;
    ListErrors errFlag = LIST_OK;
    void* item = NULL;
    int g = 3;

    item = &g;

    list = ListCreate();
    
    a = malloc(sizeof(int));
    b = malloc(sizeof(int));
    c = malloc(sizeof(int));
    
    *a = 4;
    *b = 6;
    *c = 3;
    
    ListPushTail(list, a);
    ListPushTail(list, b);
    ListPushTail(list, c);
    
    errFlag = FindFirstBackward(list, CompareInt, b, item);
    
    PrintFormat(errFlag || (item == b));

    printf("Test find First Backward exist data\n");
    ListDestroy(&list, DestroyElem);
}

void FindFirstBackwardNotFound()
{
    int *a = NULL, *b = NULL, *c = NULL, *d = NULL;
    ListErrors errFlag = LIST_OK;
    List* list = NULL;
    void* item = NULL;
    int g = 19;

    item = &g;
    
    list = ListCreate();
    
    a = malloc(sizeof(int));
    b = malloc(sizeof(int));
    c = malloc(sizeof(int));
    d = malloc(sizeof(int));
    
    *a = 4;
    *b = 6;
    *c = 3;
    *d = 8;
    
    ListPushTail(list, a);
    ListPushTail(list, b);
    ListPushTail(list, c);
    
    errFlag = FindFirstBackward(list, CompareInt, d, &item);
    
    PrintFormat(errFlag || (item == NULL));
    printf("Test find Backward not exist data\n");
    ListDestroy(&list, DestroyElem);
}

void SortIntegers()
{
    int *a = NULL, *b = NULL, *c = NULL, *d = NULL, *e = NULL;
    List* list;
    ListItr begin, end;

    list = ListCreate();
    
    a = malloc(sizeof(int));
    b = malloc(sizeof(int));
    c = malloc(sizeof(int));
    d = malloc(sizeof(int));
    e = malloc(sizeof(int));
    
    *a = 4;
    *b = 6;
    *c = 10;
    *d = 8;
    *e = 5;
    
    ListPushTail(list, a);
    ListPushTail(list, b);
    ListPushTail(list, c);
    ListPushTail(list, d);
    ListPushTail(list, e);
    begin = ListItrBegin(list);
    end = ListItrEnd(list);
    ListItrSort(begin, end, LessInt);
    /*ListForEach(list, ElementPrintInt, NULL);
    printf("\n");*/
    PrintFormat(0);
    printf("Test Sort Integers Normal\n");
    ListDestroy(&list, DestroyElem);
}

void SortIntegersPartly()
{
    int *a = NULL, *b = NULL, *c = NULL, *d = NULL, *e = NULL;
    List* list;
    ListItr begin, end;

    list = ListCreate();
    
    a = malloc(sizeof(int));
    b = malloc(sizeof(int));
    c = malloc(sizeof(int));
    d = malloc(sizeof(int));
    e = malloc(sizeof(int));
    
    *a = 4;
    *b = 6;
    *c = 10;
    *d = 8;
    *e = 5;
    
    ListPushTail(list, a);
    ListPushTail(list, b);
    ListPushTail(list, c);
    ListPushTail(list, d);
    ListPushTail(list, e);
    begin = ListItrBegin(list);
    begin = ListItrNext(begin);
    begin = ListItrNext(begin);
    end = ListItrEnd(list);
    ListItrSort(begin, end, LessInt);
    /*ListForEach(list, ElementPrintInt, NULL);
    printf("\n");*/
    PrintFormat(0);
    printf("Test Sort Integers Partly Normal\n");
    ListDestroy(&list, DestroyElem);
}

void TestCountIf()
{
    int *a = NULL, *b = NULL, *c = NULL, *d = NULL, *e = NULL;
    List* list = NULL;
    ListItr begin = NULL, end = NULL;
    int* comp = NULL;
    size_t noe = 0;

    list = ListCreate();
    
    a = malloc(sizeof(int));
    b = malloc(sizeof(int));
    c = malloc(sizeof(int));
    d = malloc(sizeof(int));
    e = malloc(sizeof(int));
    comp = malloc(sizeof(int));
    
    *a = rand() % 10;
    *b = rand() % 10;
    *c = rand() % 10;
    *d = rand() % 10;
    *e = rand() % 10;
    
    *comp = rand() % 10;
    
    ListPushTail(list, a);
    ListPushTail(list, b);
    ListPushTail(list, c);
    ListPushTail(list, d);
    ListPushTail(list, e);
    begin = ListItrBegin(list);
    end = ListItrEnd(list);
    noe = ListItrCountIf(begin, end, CompareInt, (void*)comp);
 /*   ListForEach(list, ElementPrintInt, NULL);
    
    printf("the num %d appears %lu times\n", *comp, noe);*/
    PrintFormat(0);
    printf("Test Count If Normal\n");
    ListDestroy(&list, DestroyElem);
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

