#include "../../inc/Heap.h"
#include "../../inc/vector.h"

#include <stdlib.h> /* malloc */
#include <stdio.h> /* printf - for debugging*/

#define MAGIC 0xDEADBEEE

#define PARENT(i) (((i)-1)/2)
#define LEFT(i) (2*(i))
#define RIGHT(i) (2*(i)+1)

#define IS_A_HEAP(H)     ((H) && (H)->m_magic == MAGIC)
#define IS_HEAP_EMPTY(H)    ((H)->m_heapSize == 0)

struct Vector{
    void**  m_items;
    size_t  m_originalSize;
    size_t  m_size;
    size_t  m_nItems;
    size_t  m_blockSize;
    unsigned int m_secNumber;
};

struct Heap
{
    Vector*             m_vec;
    size_t              m_heapSize;
    unsigned int        m_magic;
    LessThanComparator  m_pfLess;
};

static void Swap(Heap* _heap, size_t _i, size_t _k);

static void Heapify(Heap* _heap, size_t _index);

static void BubbleUp(Heap* _heap, size_t _index);

/**  
 * @brief Apply a heap policy over a Vector container.  
 * @param[in] _vector - Vector that hold the elements, must be initialized
 * @param[in] _pfLess - A less than comparator to be used to compare elements 
 * @return Heap * - on success
 * @retval NULL on fail 
 *
 * @warning allocating and freeing the underlying vector is user responsibility. 
 * as long as vector is under the heap control, user should not access the vector directly
 */
Heap* HeapBuild(Vector* _vector, LessThanComparator _pfLess)
{
    Heap* heap;
    size_t numOfItems, i;
    
    if(NULL == _vector  || NULL == _pfLess)
    {
        return NULL;
    }
    
    heap = malloc(sizeof(Heap));
    if(NULL == heap)
    {
        return NULL;
    }
    
    numOfItems = VectorSize(_vector);
    heap->m_heapSize = numOfItems;
    heap->m_vec = _vector;
    heap->m_magic = MAGIC;
    heap->m_pfLess = _pfLess;

    for(i = numOfItems; i > 0; --i)
    {
        Heapify(heap, PARENT(i));
    }
/*   
    for(i = PARENT(heap->m_heapSize); i > 0; --i)
    {
        Heapify(heap, i);
    }    
*/    
    return heap;
}

/**  
 * @brief Deallocate a previously allocated heap
 * Frees the heap but not the underlying vector  
 * @param[in] _heap - Heap to be deallocated.  On success will be nulled.
 * @return Underlying vector
 */
Vector* HeapDestroy(Heap** _heap)
{
    Vector* vector = NULL;
    
    if(IS_A_HEAP(*_heap))
    {
        vector = (*_heap)->m_vec;
        (*_heap)->m_magic = 0;
        free(*_heap);
        *_heap = NULL;
    }

    return vector;
}

/**  
 * @brief Add an element to the Heap preserving heap property.  
 * @param[in] _heap - Heap to insert element to.
 * @param[in] _element - Element to insert. can't be null
 * @return success or error code 
 * @retval HeapOK  on success
 * @retval HeapNOT_INITIALIZED  error, heap not initilized
 * @retval HeapREALLOCATION_FAILED error, heap could not reallocate underlying vector 
 */
HeapResult HeapInsert(Heap* _heap, void* _element)
{
    size_t size;
    
    if(!IS_A_HEAP(_heap))
    {
        return HEAP_NOT_INITIALIZED;
    }
    if(NULL == _element)
    {
        return HEAP_INV_ARG;
    }

    if(VectorAppend(_heap->m_vec, _element) != ERR_OK)
    {
        return HEAP_REALLOCATION_FAILED;
    }
    
    size = VectorSize(_heap->m_vec);

    BubbleUp(_heap, size - 1);
    _heap->m_heapSize++;
    
    return HEAP_SUCCESS;
}

/**  
 * @brief Peek at element on top of heap without extracting it.  
 * @param[in] _heap - Heap to peek at.
 * @return pointer to element, can be null if heap is empty or on error
 */
const void* HeapPeek(const Heap* _heap)
{
    void* data = NULL;
    if(!IS_A_HEAP(_heap))
    {
        return NULL;
    }
    
    VectorGet(_heap->m_vec, 1, &data);
    return data;
}

/**  
 * @brief Extract element on top of heap and remove it.  
 * @param[in] _heap - Heap to extract from.
 * @return pointer to element, can be null if heap is empty. 
 */
void* HeapExtract(Heap* _heap)
{
    /*declarations*/
    void* data = NULL, *datachild = NULL;
    size_t i;
    
    /*data check*/
    if(!IS_A_HEAP(_heap))
    {
        return NULL;
    }
    
    /*swapping first and last elements in VECTOR*/
    /*removing last (biggest) element from VECTOR (and saving the data)*/
    VectorGet(_heap->m_vec, 1, &data);
    VectorRemove(_heap->m_vec, &datachild);
    VectorSet(_heap->m_vec, 1, datachild);

    /*heapifying */
    _heap->m_heapSize--;
    Heapify(_heap, 0);

    /*return data*/
    return data;
}

/**  
 * @brief Get the current size (number of elements) in the heap.  
 * @param[in] _heap - the Heap.
 * @return number of elements or zero if empty. 
 */
size_t HeapSize(const Heap* _heap)
{
    if(!IS_A_HEAP(_heap))
    {
        return 0;
    }
    return _heap->m_heapSize;
}

/**  
 * @brief Iterate over all elements  in the heap from top to bottom.
 * @details The user provided ActionFunction _act will be called for each element. 
 * iteration will stop at the first element where _act(e) returns zero
 * @param[in] _heap - Heap to iterate over.
 * @param[in] _act - User provided function pointer to be invoked for each element
 * @returns number of times the user functions was invoked
 */
size_t HeapForEach(const Heap* _heap, ActionFunction _act, void* _context)
{
    size_t i;
    if(!IS_A_HEAP(_heap))
    {
        return 0;
    }
    
    for(i = 0; i < _heap->m_heapSize; ++i)
    {
        if(_act(_heap->m_vec->m_items[i], _context) == 0)
        {
            break;
        }
    }
    return i;
}


/**  
 * @brief Sort a given vector of elments using a heap sort.
 * @param[in] _vector - vector to sort.
 * @param[in] _pfLess
 */
void HeapSort(Vector* _vec, LessThanComparator _pfLess)
{
    size_t i;
    Heap* heap;
    if(NULL == _vec || NULL == _pfLess)
    {
        return;
    }
    
    heap = HeapBuild(_vec, _pfLess);
    if(NULL == heap)
    {
        return;
    }
    
    for(i = heap->m_heapSize ; i > 0; --i)
    {
        Swap(heap, 1, i);
        heap->m_heapSize--;
        Heapify(heap, 0);
    }
    HeapDestroy(&heap);
}

/****************AUX FUNCTIONS*****************************/

static void Heapify(Heap* _heap, size_t _index)
{
    size_t leftIndex, rightIndex, parIndex;
    void *leftData = NULL, *rightData = NULL, *parData = NULL;
    
    parIndex = _index;
    leftIndex = _index * 2 + 1;
    rightIndex = leftIndex + 1;
    VectorGet(_heap->m_vec, parIndex + 1, &parData);
    
    if(leftIndex < _heap->m_heapSize)
    {
        VectorGet(_heap->m_vec, leftIndex + 1, &leftData);
        if(!_heap->m_pfLess(parData, leftData))
        {
            parIndex = leftIndex;
            Swap(_heap, parIndex + 1, _index + 1);
            Heapify(_heap, parIndex);
        }
    }
    
    if(rightIndex < _heap->m_heapSize)
    {
        VectorGet(_heap->m_vec, rightIndex + 1, &rightData);
        if(!_heap->m_pfLess(parData, rightData))
        {
            parIndex = rightIndex;
            Swap(_heap, parIndex + 1, _index + 1);
            Heapify(_heap, parIndex);
        }
    }
}
/*
static void Heapify2(Heap* _heap, size_t _index)
{
*/    /*declarations*/
    
/*    if(IS_LEAF())
    {
        return;
    }
*/    /*
    if((max = find max()) != _index)
    {
        Swap(_index, max)
        Heapify(_heap, max)
    }
    */
/*    
}
*/
static void Swap(Heap* _heap, size_t _i, size_t _k)
{
    void *a, *b;
    
    VectorGet(_heap->m_vec, _i, &a);
    VectorGet(_heap->m_vec, _k, &b);
    
    VectorSet(_heap->m_vec, _k, a);
    VectorSet(_heap->m_vec, _i, b);    
}

static void BubbleUp(Heap* _heap, size_t _index)
{
    void *parent, *child;
    
    VectorGet(_heap->m_vec, _index + 1, &child);
    VectorGet(_heap->m_vec, PARENT(_index) + 1, &parent);
    
    while(0 < _index && !_heap->m_pfLess(parent, child))
    {
        Swap(_heap, _index + 1, PARENT(_index) + 1);
        _index = PARENT(_index);
        VectorGet(_heap->m_vec, _index + 1, &child);
        VectorGet(_heap->m_vec, PARENT(_index) + 1, &parent);  
    }
}
















