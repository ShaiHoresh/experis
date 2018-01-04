#include <stdlib.h> /*malloc*/
#include <math.h> /*sqrt*/
#include <stdio.h>

#include "../../inc/DoubleLL.h"
#include "../../inc/HashMap.h"

#define MAGIC 0xFEEDFACE
/*#define NDEBUG 1*/

#define IS_A_HASH(H) ((H) && (H)->m_magic == MAGIC)

struct HashMap
{
    unsigned int        m_magic;
    List**              m_buckets;
    HashFunction        m_hashFunc;
    EqualityFunction    m_equalityFunc;
    size_t              m_hashSize;
/*    
#ifndef NDEBUG
    MapStats            m_statistics;
#endif  NDEBUG */
} ;

typedef struct Data
{
    void*   m_key;
    void*   m_value;
}Data;

static size_t FindPrime(size_t _size);

static void BucketDestroy(List* _list, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value));

static ListItr IsKeyExist(HashMap* _map, size_t _index, const void* _key, void** _pValue);

static int CreateBuckets(List** buckets, size_t _capacity);

static int counter(const void* _key, void* _value, void* _context);

static int ReWriteBucketsArray(HashMap *_map, List** list, size_t _newCapacity);
/*
#ifndef NDEBUG
static void InitStats(HashMap* hash);
#endif  NDEBUG */

HashMap* HashMapCreate(size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc)
{
    HashMap* hash;
    int flag = 0;
    
    if(_capacity < 2 || NULL == _hashFunc || NULL == _keysEqualFunc)
    {
        return NULL;
    }
    
    hash = malloc(sizeof(HashMap));
    if(NULL == hash)
    {
        return NULL;
    }
        
    hash->m_magic = MAGIC;
    hash->m_hashSize = FindPrime(_capacity);
    hash->m_hashFunc = _hashFunc;
    hash->m_equalityFunc = _keysEqualFunc;
    
    hash->m_buckets = malloc(hash->m_hashSize * sizeof(List*));
    if(NULL == hash->m_buckets)
    {
        free(hash);
        return NULL;
    }    
    
    flag = CreateBuckets(hash->m_buckets, _capacity);
    if(flag == 0)
    {
        return NULL;
    }
/*
#ifndef NDEBUG
    InitStats(hash);
#endif  NDEBUG */
    
    return hash;    
}
/*
#ifndef NDEBUG
static void InitStats(hash)
{
    hash.m_statistics->m_pairs = 0;
    hash.m_statistics->m_collisions = 0;
    hash.m_statistics->m_buckets = 0;
    hash.m_statistics->m_chains = 0;
    hash.m_statistics->m_maxChainLength = 0;
    hash.m_statistics->m_averageChainLength = 0;
}
#endif  NDEBUG */

void HashMapDestroy(HashMap** _map, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
{
    /*declarations*/
    size_t i;
    
    /*checks*/
    if(!IS_A_HASH(*_map) || NULL == _keyDestroy)
    {
        return;
    }
    
    /*run on all elements in array*/
    for(i = 0; i < (*_map)->m_hashSize; ++i)
    {
        /*destroy each element in bucket and the bucket itself*/
        BucketDestroy((*_map)->m_buckets[i], _keyDestroy, _valDestroy);
        ListDestroy(&(*_map)->m_buckets[i], NULL);
    }

    (*_map)->m_magic = 0;

    free((*_map)->m_buckets);
    free(*_map);
    
    *_map = NULL;
    return;
}


MapResult HashMapRehash(HashMap *_map, size_t _newCapacity)
{
    /*declarations*/
    List** list = NULL;
    int flag;
    
    /*checks*/
    if(!IS_A_HASH(_map))
    {
        return MAP_UNINITIALIZED_ERROR;
    }
    
    _newCapacity = FindPrime(_newCapacity);
    list = malloc(_newCapacity * sizeof(List*));
    if(NULL == list)
    {
        return MAP_ALLOCATION_ERROR;
    }
    
    flag = CreateBuckets(list, _newCapacity);
    if(flag == 0)
    {
        return LIST_ALLOCATION_FAILED;
    }
    
    /*get data from old map and push it to the new list*/
    if(!ReWriteBucketsArray(_map, list, _newCapacity))
    {
        return LIST_ALLOCATION_FAILED;
    }
    _map->m_hashSize = _newCapacity;
    _map->m_buckets = list;
    return MAP_SUCCESS;
}



MapResult HashMapInsert(HashMap* _map, const void* _key, const void* _value)
{
    Data* data = NULL;
    size_t index, hashKeyIndex;
    ListErrors error;
    
    /*checks*/
    if(!IS_A_HASH(_map))
    {
        return MAP_UNINITIALIZED_ERROR;
    }
    
    /*get index from hash func*/
    hashKeyIndex = _map->m_hashFunc(_key);
    index = hashKeyIndex %_map->m_hashSize;
    
    /*check if key exist*/
    if(IsKeyExist(_map, index, _key, NULL))
    {
        return MAP_KEY_DUPLICATE_ERROR;
    }
    
    /*push data to list head*/
    data = malloc(sizeof(Data));
    if(NULL == data)
    {
        return MAP_ALLOCATION_ERROR;
    }
    data->m_key = (void*)_key;
    data->m_value = (void*)_value;
    
    error = ListPushTail(_map->m_buckets[index], data);
    if(error == LIST_ALLOCATION_FAILED)
    {
        return MAP_ALLOCATION_ERROR;
    }
    
    return MAP_SUCCESS;
}

MapResult HashMapRemove(HashMap* _map, const void* _searchKey, void** _pKey, void** _pValue)
{
    size_t i;
    ListItr itr;
    
    if(!IS_A_HASH(_map))
    {
        return MAP_UNINITIALIZED_ERROR;
    }
    
    if(NULL == _searchKey)
    {
        return MAP_KEY_NULL_ERROR;
    }
    
    for(i = 0; i < _map->m_hashSize; ++i)
    {
        itr = IsKeyExist((HashMap*)_map, i, _searchKey, _pValue);
        if(NULL != itr)
        {
           /* *_pValue = (Data*)_pValue;*/
            *_pKey = (void*)_searchKey;
            ListItrRemove(itr);
            return MAP_SUCCESS;
        }
    }
    return MAP_KEY_NOT_FOUND_ERROR;
}

size_t HashMapForEach(const HashMap* _map, KeyValueActionFunction _action, void* _context)
{
    size_t i, counter = 0;
    ListItr itr, endItr;
    Data* data;
    
    if(!IS_A_HASH(_map))
    {
        return MAP_UNINITIALIZED_ERROR;
    }
    
    for(i = 0; i < _map->m_hashSize; ++i)
    {
        
        itr = ListItrBegin(_map->m_buckets[i]);
        endItr = ListItrEnd(_map->m_buckets[i]);
        while(itr != endItr)
        {
            data = ListItrGet(itr);
            if(_action(((Data*)data)->m_key, ((Data*)data)->m_value, _context) == 0)
            {
                break;
            }
            ++counter;
            itr = ListItrNext(itr);
        }
    }
    return counter;
}

MapResult HashMapFind(const HashMap* _map, const void* _searchKey, void** _pValue)
{
    size_t i;
    
    if(!IS_A_HASH(_map))
    {
        return MAP_UNINITIALIZED_ERROR;
    }
    
    if(NULL == _searchKey)
    {
        return MAP_KEY_NULL_ERROR;
    }
    
    for(i = 0; i < _map->m_hashSize; ++i)
    {
        if(IsKeyExist((HashMap*)_map, i, _searchKey, _pValue))
        {
            return MAP_SUCCESS;
        }
    }
    return MAP_KEY_NOT_FOUND_ERROR;
}

size_t HashMapSize(const HashMap* _map)
{
    return HashMapForEach(_map, counter, NULL);
}
/********************************************************************/

#ifndef NDEBUG

size_t CountUsedChains(const HashMap* _map)
{
    size_t i = 0, counter = 0;
    
    for(i = 0; i < _map->m_hashSize; ++i)
    {
        if(!ListIsEmpty(_map->m_buckets[i]))
        {
            ++counter;
        }
    }
    
    return counter;
}

size_t MaxChainLength(const HashMap* _map)
{
    size_t max = 0, i = 0, curNumOfItems = 0;
    
    for(i = 0; i < _map->m_hashSize; ++i)
    {
        curNumOfItems = ListCountItems(_map->m_buckets[i]);
        if(curNumOfItems > max)
        {
            max = curNumOfItems;
        }
    }
    return max;
}

MapStats HashMapGetStatistics(const HashMap* _map)
{
    MapStats stats;
    stats.m_pairs = HashMapSize(_map);                                              /* number of pairs stored */
    stats.m_buckets = _map->m_hashSize;                                               /* total number of collisions encountered */
    stats.m_chains = CountUsedChains(_map);                                         /* total number of buckets */
    stats.m_collisions = stats.m_pairs - stats.m_chains;  /* none empty buckets (having non zero length list) */
    stats.m_maxChainLength = MaxChainLength(_map);                                  /* length of longest chain */
    stats.m_averageChainLength = _map->m_hashSize / stats.m_chains;      /* average length of none empty chains */

    return stats;
}



#endif /* NDEBUG */

/********************************************************************/

static int counter(const void* _key, void* _value, void* _context)
{
    return 1;
}

static int CreateBuckets(List** buckets, size_t _capacity)
{
    size_t i, j;
    int flag = 1;
    
    for(i = 0; i < _capacity; ++i)
    {
        buckets[i] = ListCreate();
        if(NULL == buckets[i])
        {
            flag = 0;
            break;
        }
    }
    
    if(flag == 0)
    {
        for(j = 0; j < i; ++j)
        {
            free(buckets[i]);
        }
        free(buckets);
    }
    return flag;
}

static void BucketDestroy(List* _list, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
{
    ListItr itr, endItr;
    Data* data;
    
    itr = ListItrBegin(_list);
    endItr = ListItrEnd(_list);
    
    while(itr != endItr)
    {
        data = ListItrGet(itr);
        if(NULL != _keyDestroy)
        {
            _keyDestroy(((Data*)data)->m_key);
        }
        if(NULL != _valDestroy)
        {
            _valDestroy(((Data*)data)->m_value);
        }
        ListItrRemove(itr);
        itr = ListItrNext(itr);
    }
    return;
}


static ListItr IsKeyExist(HashMap* _map, size_t _index, const void* _key, void** _pValue)
{
    ListItr itr, endItr;
    Data* data = NULL;
    
    itr = ListItrBegin(_map->m_buckets[_index]);
    endItr = ListItrEnd(_map->m_buckets[_index]);
    
    while(itr != endItr)
    {
        data = ListItrGet(itr);
        if(_map->m_equalityFunc(data->m_key, _key) == 1)
        {
            if(_pValue)
            {
                *_pValue = data->m_value;
            }
            return itr;
        }
        itr = ListItrNext(itr);
    }
    return NULL;    
}

static size_t FindPrime(size_t _size)
{
    int i, flag = 1;
    size_t sizeSqr;
    
    if(_size % 2 == 0)
    {
        ++_size;
    }
  /*  sizeSqr = (int)sqrt((double)_size);*/
    sizeSqr = _size / 2;
    
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

static int ReWriteBucketsArray(HashMap *_map, List** list, size_t _newCapacity)
{
    /*declarations*/
    size_t i = 0, hashKeyIndex, index;
    ListItr itr, endItr;
    Data* data;
    ListErrors error;
    
    /*get data*/
    
    for(i = 0; i < _map->m_hashSize; ++i)
    {
        itr = ListItrBegin(_map->m_buckets[i]);
        endItr = ListItrEnd(_map->m_buckets[i]);
        while(itr != endItr)
        {
            data = ListItrGet(itr);
            hashKeyIndex = _map->m_hashFunc((Data*)data->m_key);
            index = hashKeyIndex % _newCapacity;
            
          /*  container = malloc(sizeof(Data));
            if(NULL == container)
            {
                return MAP_ALLOCATION_ERROR;
            }
            container->m_key = (Data*)data->m_key;
            container->m_value = (Data*)data->m_value;*/
            
            error = ListPushHead(list[index], data);
            if(error != LIST_OK)
            {
                return 0;
            }
            itr = ListItrNext(itr);
        }
    }
    return 1;
}
