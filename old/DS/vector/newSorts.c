#include "Sorts.h"

#include <stdio.h>

#define INIT_SIZE 12
#define BLOCK_SIZE 6

/*inputs _left and _right in their new places in _vec -> _right to _rightIndex */
static int Swap(Vector* _vec, size_t _leftIndex, size_t _rightIndex, int _left, int _right);

/* recursive core of the quick sort */
static void SortRec(Vector* _vec, size_t _begin, size_t _end);
/*static void SortIterative(Vector* _vec, int _numOfItems); */

/* partitions the array for quick sort */
static int Partition(Vector* _vec, size_t _begin, size_t _end);

/* checking if swap is needed and placing if needed. returning 1 if swap accured */
static int InsertInPlace(Vector* _vec, SortingType _isSwapNeeded, unsigned int _left, unsigned int _right);

/* */
static void RecMerge(Vector* _vec, int* _arr, size_t _left, size_t _right);

static void Merge(Vector* _vec, int* _arr, size_t _left, size_t _middle, size_t _right);

/* used in counting sort for countint the appearances of each number in the vector
input: original vector to be sorted (_vec), array in the size of the range (bArray), and num of Items in original vec(numOfItems).
*/
static void CountAppereance(Vector* _vec, int* _bArray, int* _indexArray, int _numOfItems);

static void Cumulate(int* _bArray, int _maxValue);

static void PutInPlace(Vector* _vec, int* bArray, int* cArray, int numOfItems);

static void CopyToOriginalVector(Vector* _vec, int* cArray, int numOfItems);

ADTErr BubbleSort(Vector* _vec)
{
    int numOfItems, prev, cur, sortedFlag = 1;
    unsigned int i, j;
    ADTErr errorFlag;
    
    if(NULL == _vec)
    {
        return ERR_NOT_INITIALIZED;
    }
    
    errorFlag = VectorItemsNum(_vec, &numOfItems);
    if(errorFlag != ERR_OK)
    {
        return errorFlag;
    }
    
    for(i = 0; i < numOfItems; ++i)
    {
        VectorGet(_vec, 0, &prev);
        for(j = 1; j < numOfItems; ++j)
        {
            VectorGet(_vec, j, &cur);
            if(prev > cur)
            {
                Swap(_vec, j - 1, j, cur, prev);
                sortedFlag = 0;
            }
            else
            {
                prev = cur;
            }
        }
        if(sortedFlag == 1)
        {
            break;
        }
        sortedFlag = 1;
    }
    return ERR_OK;
}

ADTErr ShakeSort(Vector* _vec)
{
    int numOfItems, sortedFlag = 1;
    int prev, cur;
    unsigned int i, j, k;
    ADTErr errorFlag;
    
    if(NULL == _vec)
    {
        return ERR_NOT_INITIALIZED;
    }
    errorFlag = VectorItemsNum(_vec, &numOfItems);
    if(errorFlag != ERR_OK)
    {
        return errorFlag;
    }
    
    for(i = 0; i < numOfItems / 2; ++i)
    {
        VectorGet(_vec, 0, &prev);
        for(j = 1; j < numOfItems - i; ++j)
        {
            VectorGet(_vec, j, &cur);
            if(prev > cur)
            {
                Swap(_vec, j - 1, j, cur, prev);
                sortedFlag = 0;
            }
            else
            {
                prev = cur;
            }
        }
        if(sortedFlag == 1)
        {
            break;
        }
        for(k = numOfItems - i - 1; k > i; --k)
        {
            VectorGet(_vec, k - 1, &prev);
            if(cur < prev)
            {
                Swap(_vec, k - 1, k, cur, prev);
                sortedFlag = 0;
            }
            else
            {
                prev = cur;
            }
        }
        if(sortedFlag == 1)
        {
            break;
        }
        sortedFlag = 1;
    }
    return ERR_OK;
}

ADTErr QuickSortRec(Vector* _vec)
{
    int numOfItems;
    ADTErr errorFlag;
    
    if(NULL == _vec)
    {
        return ERR_NOT_INITIALIZED;
    }
    
    errorFlag = VectorItemsNum(_vec, &numOfItems);
    if(errorFlag != ERR_OK)
    {
        return errorFlag;
    }
    
    SortRec(_vec, 0, numOfItems - 1);
    
    return ERR_OK;
}

ADTErr InsertionSort(Vector* _vec, SortingType _isSwapNeeded)
{
    int numOfItems;
    unsigned int i, j;
    int swapFlag;
    
    
    if(NULL == _vec)
    {
        return ERR_NOT_INITIALIZED;
    }
    
    VectorItemsNum(_vec, &numOfItems);
    if(numOfItems < 2)
    {
        return ERR_OK;
    }    
    
    for(i = 1; i < numOfItems; ++i)
    {
        for(j = i; j > 0; --j)
        {   
            swapFlag = InsertInPlace(_vec, _isSwapNeeded, j - 1, j);
            if(swapFlag == 0)
            {
                break;
            }
        }
    }
    return ERR_OK;
}

ADTErr ShellSort(Vector* _vec, SortingType _isSwapNeeded)
{
    int numOfItems, gap;
    unsigned int i, j, k;
    int swapFlag;
    
    
    if(NULL == _vec)
    {
        return ERR_NOT_INITIALIZED;
    }
    
    VectorItemsNum(_vec, &numOfItems);
    if(numOfItems < 2)
    {
        return ERR_OK;
    }
    
    gap = numOfItems / 2;
    
    while(gap > 0)
    {
        for(k = 0; k < gap; ++k)
        {
            for(i = k; i < numOfItems - gap; i += gap)
            {
                for(j = i + gap; j > k; j -= gap)
                {   
                    swapFlag = InsertInPlace(_vec, _isSwapNeeded, j - gap, j);
                    if(swapFlag == 0)
                    {
                        break;
                    }
                }
            }
        }
        gap /= 2;
    }
    return ERR_OK;
}

ADTErr SelectionSort(Vector* _vec)
{
    int numOfItems, i, j, minValue, minIndex, temp, curValue;
    
    VectorItemsNum(_vec, &numOfItems);
    for(i = 0; i < numOfItems - 1; ++i)
    {
        VectorGet(_vec, i, &minValue);
        curValue = minValue;
        for(j = i; j < numOfItems; ++j)
        {
            VectorGet(_vec, j, &temp);
            if(temp <= minValue)
            {
                minIndex = j;
                minValue = temp;
            }
        }
        Swap(_vec, i, minIndex, minValue, curValue);
    }
    return ERR_OK;
}

ADTErr MergeSort(Vector* _vec)
{
    int* array;
    int numOfItems;
    size_t i , j, right, middle;
    
    if(NULL == _vec)
    {
        return ERR_NOT_INITIALIZED;
    }

    VectorItemsNum(_vec, &numOfItems);
    array = malloc(numOfItems * sizeof(int));
    if(NULL == array)
    {
        return ERR_ALLOCATION_FAILED;
    }

    for(i = 1; i <= numOfItems - 1; i *= 2)
    {
        for(j = 0; j <= numOfItems - 1; j += (2 * i))
        {
            right = (j + (2 * i) <= numOfItems - 1) ? j + (2 * i) - 1 : numOfItems - 1;
            middle = i + j;
            Merge(_vec, array, j, middle,  right);
        }
    }
    
    free(array);
    return ERR_OK;    
}

ADTErr MergeSortRec(Vector* _vec)
{
    int* array;
    int numOfItems;
    
    if(NULL == _vec)
    {
        return ERR_NOT_INITIALIZED;
    }

    VectorItemsNum(_vec, &numOfItems);

    array = malloc(numOfItems * sizeof(int));
    if(NULL == array)
    {
        return ERR_ALLOCATION_FAILED;
    }
    RecMerge(_vec, array, 0, numOfItems - 1);
    
    free(array);
    return ERR_OK;
}

ADTErr CountingSort(Vector* _vec, int _maxValue)
{
    int *bArray;
    int *indexArray;
    int numOfItems;
    
    if(NULL == _vec)
    {
        return ERR_NOT_INITIALIZED;
    }

    VectorItemsNum(_vec, &numOfItems);

    indexArray = calloc(_maxValue + 1, sizeof(int)); /* array C - for appereance counting*/
    if(NULL == indexArray)
    {
        return ERR_ALLOCATION_FAILED;
    }
    
    bArray = calloc(numOfItems, sizeof(int)); /* array B - */
    if(NULL == bArray)
    {
        free(indexArray);
        return ERR_ALLOCATION_FAILED;
    }
    
    CountAppereance(_vec, bArray, indexArray, numOfItems);
    Cumulate(indexArray, _maxValue);
    PutInPlace(_vec, bArray, indexArray, numOfItems);
   /* CopyToOriginalVector(_vec, bArray, numOfItems);*/
    
    free(bArray);
    free(indexArray);
    
    return ERR_OK;
}
/*
ADTErr RadixSort(Vector* _vec, int _nDigits)
{
    int *bArray;
    int *indexArray;
    int numOfItems, i;
    
    if(NULL == _vec)
    {
        return ERR_NOT_INITIALIZED;
    }

    VectorItemsNum(_vec, &numOfItems);

    indexArray = calloc(_maxValue + 1, sizeof(int));*/ /* array C - for appereance counting*/
 /*   if(NULL == indexArray)
    {
        return ERR_ALLOCATION_FAILED;
    }
    
    bArray = calloc(numOfItems, sizeof(int)); *//* array B - */
 /*   if(NULL == bArray)
    {
        free(indexArray);
        return ERR_ALLOCATION_FAILED;
    }
    
    for(i = 1; i <= _nDigits; ++i)
    {
        CountAppereanceForRadix(_vec, bArray, indexArray, numOfItems, i);
        Cumulate(indexArray, _maxValue);
        PutInPlace(_vec, bArray, indexArray, numOfItems);
    }
    
    free(bArray);
    free(indexArray);
    
    return ERR_OK;
}*/

static void CountAppereance(Vector* _vec, int* _bArray, int* _indexArray, int _numOfItems)
{
    int i;
    int value;
    
    for(i = 0; i < _numOfItems; ++i)
    {
        VectorGet(_vec, i, &value);
        ++_indexArray[value];
        _bArray[i] = value;
    }
}
/*
static void CountAppereanceForRadix(Vector* _vec, int* _bArray, int* _indexArray, int _numOfItems, int _digitNum)
{
    int i, j;
    int value;
    
    for(i = 0; i < _numOfItems; ++i)
    {
        VectorGet(_vec, i, &value);
        for(j = 1; j < _digitNum; ++j)
        {
            value /= 10;
        }
        value %= 10;
        ++_indexArray[value];
        _bArray[i] = value;
    }
}
*/
static void Cumulate(int* _indexArray, int _maxValue)
{
    int i;
    
    for(i = 1; i <= _maxValue; ++i)
    {
        _indexArray[i] += _indexArray[i - 1]; 
    }
}

static void PutInPlace(Vector* _vec, int* _bArray, int* _indexArray, int _numOfItems)
{
    int i, value, newIndex;
    
    for(i = _numOfItems - 1; i >= 0; --i)
    {
      /* VectorGet(_vec, i, &value);*/     value = _bArray[i];
        newIndex = _indexArray[value] - 1;
      /*  bArray[newIndex] = value;*/       VectorSet(_vec, newIndex, value); 
        _indexArray[value] -= 1;
    }
}

static void CopyToOriginalVector(Vector* _vec, int* bArray, int numOfItems)
{
    int i;
    for(i = 0; i < numOfItems; ++i)
    {
        VectorSet(_vec, i, bArray[i]);
    }
}

static void RecMerge(Vector* _vec, int* _arr, size_t _left, size_t _right)
{
    size_t middle;
    
    if(_right == _left)
    {
        return;
    }
    
    middle = (_right + _left) / 2;
    
    RecMerge(_vec, _arr, _left, middle);
    RecMerge(_vec, _arr, middle + 1, _right);
    Merge(_vec, _arr, _left, middle + 1, _right);
}

static void Merge(Vector* _vec, int* _arr, size_t _left, size_t _middle, size_t _right)
{
    int leftVal, rightVal,i = 0, leftMargin, midMar;
    
    midMar = _middle;
    leftMargin = _left;
    
    /*Replace with DoMerge(Vector* _vec, int* _arr, size_t _left, size_t _middle, size_t _right) function*/  

    VectorGet(_vec, _left, &leftVal);
    VectorGet(_vec, _middle, &rightVal);

    while(_middle <= _right && _left < midMar)
    {
        if(leftVal <= rightVal)
        {
            _arr[i] = leftVal;
            VectorGet(_vec, ++_left, &leftVal);
        }
        else
        {
            _arr[i] = rightVal;
            VectorGet(_vec, ++_middle, &rightVal);
        }
        ++i;
    }
    
    /*Replace with FillTails function*/
    while(_middle <= _right)
    {
        _arr[i] = rightVal;
        VectorGet(_vec, ++_middle, &rightVal);
        ++i;
    }
    while(_left < midMar)
    {
        _arr[i] = leftVal;
        VectorGet(_vec, ++_left, &leftVal);
        ++i;
    }
    
    /*Replace with BackToVector*/
    for(i = 0; i <= (_right - leftMargin); ++i)
    {
        VectorSet(_vec, leftMargin + i , _arr[i]);
    }
}

static void SortRec(Vector* _vec, size_t _left, size_t _right)
{
    size_t pivotIndex;
    
    if(_right <= _left)
    {
        return;
    }
    pivotIndex = Partition(_vec, _left, _right);
    if(pivotIndex > _left)
    {
        SortRec(_vec, _left, pivotIndex - 1);
    }
    if(pivotIndex < _right)
    {
        SortRec(_vec, pivotIndex + 1, _right);
    }
}

static int Partition(Vector* _vec, size_t _begin, size_t _end)
{
    size_t pivotIndex, limit = _end;
    int big, small, pivot;
    
    pivotIndex = _begin;
    VectorGet(_vec, ++_begin, &big);
    VectorGet(_vec, _end, &small);
    VectorGet(_vec, pivotIndex, &pivot);

    while(_end >= _begin) 
    {
        while(pivot >= big && _begin < limit)
        {
            VectorGet(_vec, ++_begin, &big);
        }
        while(pivot < small)
        {
            VectorGet(_vec, --_end, &small);
        }

        if(_begin < _end)
        {
            Swap(_vec, _begin, _end, small, big);
		    VectorGet(_vec, --_end, &small);
		    VectorGet(_vec, ++_begin, &big);
        }
        
        if(_begin == limit)
        {
            break ;
        }
    }

    Swap(_vec, pivotIndex, _end, small, pivot);

    return _end;
}

/*
ADTErr QuickSortIterative(Vector* _vec)
{
    int numOfItems;
    ADTErr errorFlag;

    
    if(NULL == _vec)
    {
        return ERR_NOT_INITIALIZED;
    }
    
    errorFlag = VectorItemsNum(_vec, &numOfItems);
    if(errorFlag != ERR_OK)
    {
        return errorFlag;
    }
    SortIterative(_vec, numOfItems);
    return ERR_OK;
}

static void SortIterative(Vector* _vec, int _numOfItems)
{
    Stack* stack;
    int pivot, small, big;
    int dummy;
    int inc = 0, dec = _numOfItems;
    
    stack = StackCreate(INIT_SIZE, BLOCK_SIZE);
    if(NULL == stack)
    {
        return;
    }
    
    StackPush(stack, _numOfItems - 1);
    StackPush(stack, 0);
    while(!StackIsEmpty(stack))
    {
        StackPop(stack, &inc);
        dummy = inc;
        StackPop(stack, &dec);
        VectorGet(_vec, inc, &big);
        VectorGet(_vec, dec, &small);
        VectorGet(_vec, inc, &pivot);
        
        while(inc < dec)
        {
            while(big <= pivot && inc <= _numOfItems)
            {
                VectorGet(_vec, ++inc, &big);
            }
            while(small > pivot && dec >= 0)
            {
                VectorGet(_vec, --dec, &small);
            }
            if(inc < dec)
            {
                Swap(_vec, inc, dec);
            }
        }
        Swap(_vec, dummy, dec);
        
        if(inc > dummy)
        {
            StackPush(stack, inc - 1);
            StackPush(stack, 0);
        }
        if(dec < dummy)
        {
            StackPush(stack, _numOfItems);
            StackPush(stack, inc + 1);
        }
    }
    return;
}
*/

static int Swap(Vector* _vec, size_t _leftIndex, size_t _rightIndex, int _left, int _right)
{
    int isSwaped = 1;
    
    VectorSet(_vec, _leftIndex, _left);
    VectorSet(_vec, _rightIndex, _right);

    return isSwaped;
}

static int InsertInPlace(Vector* _vec, SortingType _isSwapNeeded, unsigned int _left, unsigned int _right)
{
    int leftVal, rightVal, result = 1;
    VectorGet(_vec, _left, &leftVal);
    VectorGet(_vec, _right, &rightVal);
    if(_isSwapNeeded(leftVal, rightVal))
    {
        Swap(_vec, _left, _right, rightVal, leftVal);
    }
    else
    {
        result = 0;
    }
    return result;
}









