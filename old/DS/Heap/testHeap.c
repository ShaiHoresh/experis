#include <stdio.h>
#include "Heap.h"
/*
void TestHeapBuildNormal
void TestHeapBuildNULL
void TestHeapInsertNormal
void TestHeapInsertNULL
void TestHeapInsertExistingNum
void TestMaxNormal
void TestMaxempty
void TestMaxNULL*/

int main()
{
    int i, max;
    Heap* heap;
    Vector* vector;
    size_t num;
    int data[] = {20, 5, 10, 12, 32, 45, 8, 6, 2, 9};
    vector = VectorCreate(8, 4);
    
    for(i = 0; i < sizeof(data) / sizeof(int); ++i)
    {
        VectorAdd(vector, data[i]);
    }
    heap = HeapBuild(vector);
    VectorItemsNum(vector, &i);
    printf("num of items until now is %d\n", i);
    HeapPrint(heap);
    
    for(i = 0; i < 6; ++i)
    {
        HeapInsert(heap, 3*i+1);
    }
    HeapPrint(heap);
    
    HeapMax(heap, &max);
    printf("Max value in heap: %d\n", max);
    
    for(i = 0; i < 10; ++i)
    {
        HeapExtractMax(heap, &max);
        HeapPrint(heap);
    }
    
    HeapMax(heap, &max);
    printf("Max value in heap: %d\n", max);
    
    num = HeapItemsNum(heap);
    printf("the num of nodes in this heap is: %u\n", num);
    HeapDestroy(heap);
    VectorDestroy(vector);
    return 0;
}
