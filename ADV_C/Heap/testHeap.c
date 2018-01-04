#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, size_t, rand */

#include "../../inc/Heap.h"

/*********************AUX / USER FUNCTIONS******************/
void PrintFormat(int flag)
{
    flag ? printf("Succeeded:   ") : printf("Failed:        ");
}

int	CompInt(const void *_left, const void *_right)
{
    return *(int*)_left > *(int*)_right;
}

int DestroyInt(void* _element, void* _context)
{
    free(_element);
    return 0;
}

int PrintInt(const void* _elem, void* _context)
{
    printf("%3d", *(int*)_elem);
}

void VectorPrintInt(Vector* vector)
{
    size_t i, size;
    void* data;
    size = VectorSize(vector); 
    for(i = 1; i <= size; ++i)
    {
        VectorGet(vector, i, &data);
        printf("%3d", *(int*)data);
    }
    printf("\n");
    return;
}

/********************DECLARATIONS***************************/
void TestHeapBuildNormal();
void TestHeapBuildNullVector();
void TestHeapBuildNullCompFunction();
void TestHeapBuildOddItems();
void TestHeapBuildEvenItems();

void TestHeapInsertNormal();
void TestHeapInsertNullHeap();
void TestHeapInsertNullelement();
void TestHeapInsertToEmptyheap();

void TestHeapPeekNormal();
void TestHeapPeekNullHeap();
void TestHeapPeekFromEmptyheap();

void TestHeapExtractNormal();


void TestHeapForEachNormal();


void TestHeapSortNormal();

int main()
{
    TestHeapBuildNormal();
    TestHeapBuildNullVector();
    TestHeapBuildNullCompFunction();
    TestHeapBuildOddItems();
    TestHeapBuildEvenItems();

    TestHeapInsertNormal();
    TestHeapInsertNullHeap();
    TestHeapInsertNullelement();
    TestHeapInsertToEmptyheap();
    
    TestHeapPeekNormal();
    TestHeapPeekNullHeap();
    TestHeapPeekFromEmptyheap();

    TestHeapExtractNormal();
    TestHeapForEachNormal();
    TestHeapSortNormal();
    
    return 0;
}

void TestHeapBuildNormal()
{
    Vector* vector = NULL;
    Heap* heap = NULL;
    int* arr[10];
    int i = 0;
    void* item;
    int data[] = {3};
    vector = VectorCreate(8, 4);
    if(NULL == vector)
    {
        printf("vector aloccation failed\n");
        return;
    }

    arr[0] = malloc(sizeof(int));
    if(NULL == arr[0])
    {
        printf("int aloccation failed\n");
        return;
    }
    *arr[0] = data[0];
    VectorAppend(vector, arr[0]);
    VectorPrintInt(vector); 

    heap = HeapBuild(vector, CompInt);
    HeapDestroy(&heap);

    VectorDestroy(&vector, DestroyInt);
    PrintFormat(!heap);
    printf("TestHeapBuildNormal\n");
    return;
}

void TestHeapBuildNullVector()
{
    Vector* vector = NULL;
    Heap* heap = NULL;
    heap = HeapBuild(vector, CompInt);
    PrintFormat(!heap);
    printf("TestHeapBuildNullVector\n");
}

void TestHeapBuildNullCompFunction()
{
    Vector* vector = NULL;
    Heap* heap = NULL;
    vector = VectorCreate(8, 4);
    heap = HeapBuild(vector, NULL);
    PrintFormat(!heap);
    printf("TestHeapBuildNullCompFunction\n");
}

void TestHeapBuildOddItems()
{
    Vector* vector = NULL;
    Heap* heap = NULL;
    int* arr[10];
    int i = 0;
    void* item;
    int data[] = {3, 5, 0, 7, 32, 51, 65, 12, 32};
    vector = VectorCreate(10, 4);
    if(NULL == vector)
    {
        printf("vector aloccation failed\n");
        return;
    }
    for(i = 0; i < sizeof(data) / sizeof(int); ++i)
    {
        arr[i] = malloc(sizeof(int));
        if(NULL == arr[i])
        {
            break;
        }
        *arr[i] = data[i];
        VectorAppend(vector, arr[i]);
    }

    heap = HeapBuild(vector, CompInt);
    PrintFormat(heap != NULL);
    printf("TestHeapBuildOddItems\n");
    HeapDestroy(&heap);
    VectorDestroy(&vector, DestroyInt);

    return;
}

void TestHeapBuildEvenItems()
{
    Vector* vector = NULL;
    Heap* heap = NULL;
    int* arr[10];
    int i = 0;
    void* item;
    int data[] = {3, 5, 0, 7, 32, 65, 12, 32};
    vector = VectorCreate(10, 4);
    if(NULL == vector)
    {
        printf("vector aloccation failed\n");
        return;
    }
    for(i = 0; i < sizeof(data) / sizeof(int); ++i)
    {
        arr[i] = malloc(sizeof(int));
        if(NULL == arr[i])
        {
            break;
        }
        *arr[i] = data[i];
        VectorAppend(vector, arr[i]);
    }

    heap = HeapBuild(vector, CompInt);
    PrintFormat(heap != NULL);
    printf("TestHeapBuildEvenItems\n");
    HeapDestroy(&heap);
    VectorDestroy(&vector, DestroyInt);

    return;
}

void TestHeapInsertNormal()
{
    Vector* vector = NULL;
    Heap* heap = NULL;
    int* arr[10];
    int i = 0;
    void* item;
    int data[] = {3, 5, 0, 7, 51, 65, 12, 32};
    vector = VectorCreate(8, 4);
    if(NULL == vector)
    {
        printf("vector aloccation failed\n");
        return;
    }
    for(i = 0; i < 4; ++i)
    {
        arr[i] = malloc(sizeof(int));
        if(NULL == arr[i])
        {
            break;
        }
        *arr[i] = data[i];
        VectorAppend(vector, arr[i]);
    }

    heap = HeapBuild(vector, CompInt);
    
    for(i = 4; i < 8; ++i)
    {
        arr[i] = malloc(sizeof(int));
        if(NULL == arr[i])
        {
            break;
        }
        *arr[i] = data[i];
        HeapInsert(heap, arr[i]);
    }
    PrintFormat(heap != NULL);
    printf("TestHeapInsertNormal\n");

    HeapDestroy(&heap);
    VectorDestroy(&vector, DestroyInt);

    return;
}


void TestHeapInsertNullHeap()
{
    Heap* heap = NULL;
    int* a;
    HeapResult err = 0;
    int c = 7;
    
    a = &c;
    
    err = HeapInsert(heap, a);
    
    PrintFormat(err == HEAP_NOT_INITIALIZED);
    printf("TestHeapInsertNullHeap\n");
}

void TestHeapInsertNullelement()
{
    Heap* heap = NULL;
    Vector* vector;
    int* a = NULL;
    HeapResult err;
    
    vector = VectorCreate(2, 1);
    heap = HeapBuild(vector,  CompInt);
    
    err = HeapInsert(heap, a);
    
    PrintFormat(err == HEAP_INV_ARG);
    printf("TestHeapInsertNullelement\n");
    HeapDestroy(&heap);
    VectorDestroy(&vector, DestroyInt);
}

void TestHeapInsertToEmptyheap()
{
    Vector* vector;
    Heap* heap;
    int* a;
    HeapResult err;
    int b = 7;
    
    a = &b;
    vector = VectorCreate(2, 1);
    heap = HeapBuild(vector,  CompInt);
    err = HeapInsert(heap, a);
    
    PrintFormat(err == HEAP_SUCCESS);
    printf("TestHeapInsertEmptyHeap\n");
}

void TestHeapPeekNormal()
{
    Vector* vector = NULL;
    Heap* heap = NULL;
    int* arr[10];
    int i = 0;
    void* item;
    const void* peekData;
    int data[] = {3, 5, 0, 7, 51, 65, 12, 32};

    vector = VectorCreate(8, 4);
    if(NULL == vector)
    {
        printf("vector aloccation failed\n");
        return;
    }
    for(i = 0; i < sizeof(data) / sizeof(int); ++i)
    {
        arr[i] = malloc(sizeof(int));
        if(NULL == arr[i])
        {
            break;
        }
        *arr[i] = data[i];
        VectorAppend(vector, arr[i]);
    }
    
    heap = HeapBuild(vector, CompInt);
    peekData = HeapPeek(heap);
    PrintFormat(*(int*)peekData = 65);
    printf("TestHeapPeekNormal\n");
    HeapDestroy(&heap);
    VectorDestroy(&vector, DestroyInt);

    return;
}

void TestHeapPeekNullHeap()
{
    Heap* heap = NULL;
    
    PrintFormat(!HeapPeek(heap));
    printf("TestHeapPeekNullHeap\n");
}

void TestHeapPeekFromEmptyheap()
{
    Vector* vector;
    Heap* heap;
    const void* peekData;
    
    vector = VectorCreate(2, 1);
    heap = HeapBuild(vector, CompInt);
    
    PrintFormat(!HeapPeek(heap));
    printf("TestHeapPeekEmptyHeap\n");
    
    HeapDestroy(&heap);
    VectorDestroy(&vector, DestroyInt);

    return;
}


void TestHeapExtractNormal()
{
    Vector* vector = NULL;
    Heap* heap = NULL;
    int* arr[10];
    int i = 0;
    void* item;
    void* extractedData;
    int data[] = {3, 5, 0, 7, 51, 23, 65, 12, 32};
    printf("TestHeapExtractNormal\n");
    vector = VectorCreate(8, 4);
    if(NULL == vector)
    {
        printf("vector aloccation failed\n");
        return;
    }
    for(i = 0; i < sizeof(data) / sizeof(int); ++i)
    {
        arr[i] = malloc(sizeof(int));
        if(NULL == arr[i])
        {
            break;
        }
        *arr[i] = data[i];
        VectorAppend(vector, arr[i]);
    }
    heap = HeapBuild(vector, CompInt);
    VectorPrintInt(vector);    
    extractedData = HeapExtract(heap);
    VectorPrintInt(vector);    
    printf("extracted = %d\n", *(int*)extractedData);

    HeapDestroy(&heap);
    VectorDestroy(&vector, DestroyInt);

    return;
}

void TestHeapForEachNormal()
{
    Vector* vector = NULL;
    Heap* heap = NULL;
    int* arr[10];
    int i = 0;
    void* item;
    int data[] = {3, 5, 0, 7, 51, 23, 65, 12, 32};
    printf("TestHeapForEachNormal\n");
    vector = VectorCreate(8, 4);
    if(NULL == vector)
    {
        printf("vector aloccation failed\n");
        return;
    }
    for(i = 0; i < sizeof(data) / sizeof(int); ++i)
    {
        arr[i] = malloc(sizeof(int));
        if(NULL == arr[i])
        {
            break;
        }
        *arr[i] = data[i];
        VectorAppend(vector, arr[i]);
    }

    HeapForEach(heap, PrintInt, NULL);    

    heap = HeapBuild(vector, CompInt);
    HeapDestroy(&heap);

    VectorPrintInt(vector);
    VectorDestroy(&vector, DestroyInt);

    return;
}

void TestHeapSortNormal()
{
    Vector* vector = NULL;
    Heap* heap = NULL;
    int* arr[10];
    int i = 0;
    void* item;
    int data[] = {3, 5, 0, 7, 51, 23, 65, 12, 32};
    printf("TestHeapSortNormal\n");
    vector = VectorCreate(8, 4);
    if(NULL == vector)
    {
        printf("vector aloccation failed\n");
        return;
    }
    for(i = 0; i < sizeof(data) / sizeof(int); ++i)
    {
        arr[i] = malloc(sizeof(int));
        if(NULL == arr[i])
        {
            break;
        }
        *arr[i] = data[i];
        VectorAppend(vector, arr[i]);
    }

    VectorPrintInt(vector);

    HeapSort(vector, CompInt);
    VectorPrintInt(vector);
    HeapDestroy(&heap);

    VectorDestroy(&vector, DestroyInt);

    return;
}

