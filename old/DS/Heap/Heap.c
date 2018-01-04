#include <stdio.h>
#include <stdlib.h>

#include "Heap.h"


#define PARENT(i) (((i)-1)/2)
#define LEFT(i) (2*(i)+1)
#define RIGHT(i) (2*(i)+2)

#define MAGIC 477213

struct Heap
{
    Vector* m_vec;
    size_t m_heapSize;
    unsigned int m_test;
};

static ADTErr Check(void* _struct);
static void BubbleUp(Heap* _heap, size_t _index);
static void Heapify(Heap* _heap, int i);
static void Swap(Heap* _heap, int _i, int _k);

Heap* HeapBuild(Vector* _vec)
{
    Heap* heap;
    int numOfItems, i;
    
    if(Check((void*)_vec) != ERR_OK)
    {
        return NULL;
    }
    
    heap = malloc(sizeof(Heap));
    if(Check((void*)heap) != ERR_OK)
    {
        return NULL;
    }
    
    VectorItemsNum(_vec, &numOfItems);
    heap->m_heapSize = numOfItems;
    heap->m_vec = _vec;
    heap->m_test = MAGIC;
    
    for(i = numOfItems; i > 0; --i)
    {
        Heapify(heap, (i - 1) / 2);
    }
    return heap;
}

void HeapDestroy(Heap* _heap)
{
    if(_heap->m_test == MAGIC)
    {
        _heap->m_test = 0;
        free(_heap);
    }
}

ADTErr HeapInsert(Heap* _heap, int _data)
{
    int numOfItems;
    if(NULL == _heap)
    {
        return ERR_NOT_INITIALIZED;
    }
    if(VectorAdd(_heap->m_vec, _data) != ERR_OK)
    {
        return ERR_INSERT_FAILED;
    }
    VectorItemsNum(_heap->m_vec, &numOfItems);
    _heap->m_heapSize = numOfItems;
    BubbleUp(_heap, numOfItems-1);
    return ERR_OK;
}

ADTErr HeapMax(Heap* _heap, int* _data)
{
    if(Check((void*)_heap) != ERR_OK || Check((void*)_data) != ERR_OK)
    {
        return ERR_NOT_INITIALIZED;
    }
    VectorGet(_heap->m_vec, 0, _data);
    return ERR_OK;
}

ADTErr HeapExtractMax(Heap* _heap, int* _data)
{
    int numOfItems, temp, i;
    if(Check((void*)_heap) != ERR_OK || Check((void*)_data) != ERR_OK)
    {
        return ERR_NOT_INITIALIZED;
    }
    VectorGet(_heap->m_vec, 0, _data);
    VectorDelete(_heap->m_vec, &temp);
    VectorItemsNum(_heap->m_vec, &numOfItems);
    _heap->m_heapSize = numOfItems;
    VectorSet(_heap->m_vec, 0, temp);
    for(i = numOfItems; i > 0; --i)
    {
        Heapify(_heap, i / 2 -1);
    }
    return ERR_OK;
}



size_t HeapItemsNum(Heap* _heap)
{
    if(Check((void*)_heap) == ERR_OK)
    {
        return _heap->m_heapSize;
    }
    return 0;
}

void HeapPrint(Heap* _heap)
{
    if(Check((void*)_heap) != ERR_OK)
    {
        return;
    }
    VectorPrint(_heap->m_vec);
}

static void BubbleUp(Heap* _heap, size_t _index)
{
    int father, son;
    VectorGet(_heap->m_vec, _index, &son);
    VectorGet(_heap->m_vec, ((_index - 1) / 2), &father);
    while(0 < _index && father < son)
    {
        Swap(_heap, _index, ((_index - 1) / 2));
        _index = ((_index - 1) / 2);
        VectorGet(_heap->m_vec, _index, &son);
        VectorGet(_heap->m_vec, ((_index - 1) / 2), &father);  
    }
}

static ADTErr Check(void* _struct)
{
    if(NULL == _struct)
    {
        return ERR_NOT_INITIALIZED;
    }
    return ERR_OK;
}

static void Heapify(Heap* _heap, int i)
{
    int largest, right, left, largeVal;
    
    VectorGet(_heap->m_vec, RIGHT(i), &right);
    VectorGet(_heap->m_vec, LEFT(i), &left);
    largest = i;
    VectorGet(_heap->m_vec, largest, &largeVal);
    
    if(i > _heap->m_heapSize)
    {
        return;
    }
    
    if(LEFT(i) <= _heap->m_heapSize && left > largeVal)
    {
        largest = LEFT(i);
        Swap(_heap, i, largest);
        Heapify(_heap, largest);
    }
    if(RIGHT(i) <= _heap->m_heapSize && right > largeVal)
    {
        largest = RIGHT(i);
        Swap(_heap, i, largest);
        Heapify(_heap, largest);
    }
}

static void Swap(Heap* _heap, int _i, int _k)
{
    int a, b;
    
    VectorGet(_heap->m_vec, _i, &a);
    VectorGet(_heap->m_vec, _k, &b);
    
    VectorSet(_heap->m_vec, _k, a);
    VectorSet(_heap->m_vec, _i, b);    
}





















