#include <string.h> /* memcpy */
#include <stdlib.h> /* malloc, size_t */


#include "GSort.h"
static void GSwap(void* _left, void* _right, void* _temp, size_t _blockSize);
static int bubble(char* _start, char* _end, void* _tempBlock, size_t _blockSize, SortingType _isSwapNeeded);

ADTErr GenericBubbleSort(void* _data, size_t _numOfElements, size_t _blockSize, SortingType _isSwapNeeded)
{
    /* declarations */
    void* tempBlock = NULL;
    char* end = NULL;
    size_t i;
    
    /*TODO send to ChecksAndInit Func*/
    /* check if data exist */
    if(NULL == _data || NULL == _isSwapNeeded)
    {
        return ERR_NOT_INITIALIZED;
    }
    
    /* block size 0 is invalid */
    if(_blockSize == 0)
    {
        return ERR_INVALID_SIZE;
    }
    
    /* array of 0 or 1 elements is sorted*/
    if(_numOfElements < 2)
    {
        return ERR_OK;
    }
    
    /* allocating a temp block for swaping */
    tempBlock = malloc(_blockSize);
    if(NULL == tempBlock)
    {
        return ERR_ALLOCATION_FAILED;
    }
    
    end = (char*)_data + (_numOfElements - 1) * _blockSize;
    for(i = 0; i < _numOfElements - 1; ++i)
    {
        if(!bubble(_data, end, tempBlock, _blockSize, _isSwapNeeded))
        {
            break;
        }
        end -= _blockSize;
    }
    
    free(tempBlock);
    
    return ERR_OK;
}



/************************************************************/
static void GSwap(void* _left, void* _right, void* _temp, size_t _blockSize)
{
    memcpy(_temp, _right, _blockSize);
    memcpy(_right, _left, _blockSize);
    memcpy(_left, _temp, _blockSize);
}

static int bubble(char* _start, char* _end, void* _tempBlock, size_t _blockSize, SortingType _isSwapNeeded)
{
    int flag = 0;
    while(_start != _end)
    {
        if(_isSwapNeeded(_start, _start + _blockSize))
        {
            GSwap(_start, _start + _blockSize, _tempBlock, _blockSize);
            flag = 1;
        }
        _start += _blockSize;
    }
    return flag;
}

