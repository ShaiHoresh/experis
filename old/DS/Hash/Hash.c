#include "Hash.h"

#include <stdio.h>
#include <math.h>


#define MAGIC_NUM 477213
#define SEC_EXTEND (1.3)


struct Hash
{
    int* m_data;
    size_t m_originalSize;          /*original size given by the client*/
    size_t m_hashSize;              /*real array size*/
    size_t m_maxCollisions;             /*maximal offset*/
    size_t m_numberOfInsertions;    /*total insertions count*/
    size_t m_totalCollisions;     /*total collisions until now*/
    unsigned int m_test;
};

static ADTErr Check(void* _var);
static size_t FindPrime(size_t _size);

static int FindPlace(Hash* _hash, int _data);
static int IsExist(const Hash* _hash, int _data, int *_place);

Hash* HashCreate(const size_t _size)
{
    Hash* hash;
    
    if( _size < 1)
    {
        return NULL;
    }
    
    hash = calloc(1, sizeof(Hash));
        
    if(Check((void*)hash) == ERR_NOT_INITIALIZED) 
    {
        return NULL;
    }
    
    hash->m_hashSize = FindPrime((size_t)(_size * SEC_EXTEND));
    hash->m_data = calloc(hash->m_hashSize, sizeof(int));
    if(NULL == hash->m_data)
    {
        free(hash);
        return NULL;
    }
    
    hash->m_originalSize = _size;
    return hash;
}

void HashDestroy(Hash* _hash)
{
    if(!Check((void*)_hash))
    {
        if(!Check((void*)_hash->m_data) || _hash->m_test == MAGIC_NUM)
        {
            _hash->m_test = 0;
            free(_hash->m_data);
        }
        free(_hash);
    }    
}

ADTErr HashInsert(Hash* _hash, int _data)
{
    int index, exist; 
    
    if(_data < 1)
    {
        return ERR_INVALID_VALUE;
    }
    
    if(Check((void*)_hash))
    {
        return ERR_NOT_INITIALIZED;
    }
    
    if(_hash->m_numberOfInsertions >= _hash->m_originalSize)
    {
        return ERR_OVERFLOW;
    }
    
    exist = IsExist(_hash, _data, &index);
    
    if(exist == 1)
    {
        return ERR_EXISTING_VALUE;
    }
    index = FindPlace(_hash, _data);
    
    ++_hash->m_numberOfInsertions;
    _hash->m_data[index] = _data;
    
    return ERR_OK;
}

ADTErr HashRemove(Hash* _hash, int _data)
{
    int index, exist;
    if(Check((void*)_hash))
    {
        return ERR_NOT_INITIALIZED;
    }    
    
    if(_data < 1)
    {
        return ERR_INVALID_VALUE;
    }
    
    exist = IsExist(_hash, _data, &index);
    if(exist == 1)
    {
        return ERR_UNEXISTING_VALUE;
    }

    _hash->m_data[index] = -1;
    --(_hash->m_numberOfInsertions);
    
    return ERR_OK;
}

int HashIsFound(const Hash* _hash, int _data)
{
    int index;
    if(Check((void*)_hash))
    {
        return 0;
    }

    if(_data < 1)
    {
        return 0;
    }
    
    return IsExist(_hash, _data, &index);    
}

size_t HashNumOfItems(const Hash* _hash)
{
    if(Check((void*)_hash))
    {
        return 0;
    }
    return _hash->m_numberOfInsertions;
}

size_t HashCapacity(const Hash* _hash)
{
    if(Check((void*)_hash))
    {
        return 0;
    }
    return _hash->m_originalSize;
}

double HashAverageCollisions(const Hash* _hash)
{
    if(Check((void*)_hash) || 0 == _hash->m_numberOfInsertions)
    {
        return 0;
    }
    return ((double)_hash->m_totalCollisions / _hash->m_numberOfInsertions);
}

size_t HashMaxCollisions(const Hash* _hash)
{
    if(Check((void*)_hash))
    {
        return 0;
    }
    return _hash->m_maxCollisions;
}

void HashPrint(const Hash* _hash)
{
    int i;
    if(Check((void*)_hash))
    {
        return;
    }
    for(i = 0; i < _hash->m_hashSize; ++i)
    {
        if(_hash->m_data[i] > 0)
        {
            printf("%3d", _hash->m_data[i]);
        }
    }
    printf("\n");
}

size_t HashFunc(int _data)
{
    return (size_t)_data;
}

static int IsExist(const Hash* _hash, int _data, int *_place)
{
    int i, flag = 0, cur = _data;
    
    for(i = 0; i < _hash->m_maxCollisions; ++i)
    {
        if(_hash->m_data[HashFunc(cur) % _hash->m_hashSize] == _data)
        {
            flag = 1;
            break;
        }
        ++cur;
    }
    *_place = cur % (int)_hash->m_hashSize;
    return flag;
}

static int FindPlace(Hash* _hash, int _data)
{
    int i = _data;
    size_t counter = 0;
    
    while(_hash->m_data[HashFunc(i) % _hash->m_hashSize] != 0 && _hash->m_data[HashFunc(i) % _hash->m_hashSize] != -1)
    {
        ++i;
        ++counter;
    }
    
    _hash->m_maxCollisions < counter ? _hash->m_maxCollisions = (size_t)counter : 1;
    counter > 0 ? ++_hash->m_totalCollisions : 1;
    
    return (i % (int)_hash->m_hashSize);
}

static size_t FindPrime(size_t _size)
{
    int i, sizeSqr, flag = 1;
    if(_size % 2 == 0)
    {
        ++_size;
    }
    sizeSqr = (int)sqrt(_size);
    
    while(1)
    {
        for(i = 3; i <= sizeSqr; i += 2)
        {
            if((int)_size % i == 0)
            {
                flag = 0;
            }
       }
        if(flag == 1)
        {
            return _size;
        }       
       _size += 2;
       flag = 1;
    }
}

static ADTErr Check(void* _var)
{
    if(NULL == _var)
    {
        return ERR_NOT_INITIALIZED;
    }
    return ERR_OK;
}


















