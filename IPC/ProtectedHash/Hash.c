#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include "List.h"
#include "PHashMap.h"

#define MAGIC_NUM 71070

#define IS_HASH(MAP) (NULL != (MAP) && MAGIC_NUM == (MAP)->m_mgc_num)  

#define MUTEX_AMOUNT 100


struct HashMap
{
    List** m_map;   
    HashFunction m_hashfunc;
    EqualityFunction m_equal; 
    int m_mgc_num;
    size_t m_hashSize;
    size_t m_numOfelement;
    pthread_mutexattr_t m_mutexesAttr;
	pthread_mutex_t* m_mutex;   
    #ifndef NDEBUG
	Map_Stats m_statistic;
	#endif/*NDEBUG*/ 
};

typedef struct Element Element;

struct Element
{
	void* m_key;
	void* m_data;
};
typedef void (*keyDestroy)(void* _key);
typedef void (*valDestroy)(void* _value);
 
/**********************/



/************************************************************/
static int isPrimenum(int i)
{
	int count;	
	int sq= (int)sqrt(i);
	
	if(i < 4 && i > 0)
	{
		return 1;
	}
	if ( i % 2 == 0 )
	{
		return 0;		
	}	
	for(count = 3 ; count <= sq ; count=count+2 )
	{
		if ( i % count == 0 )
		{
			return 0;		
		}
	}
	return 1;
}

size_t FindPrime(size_t _num)
{
	while(!isPrimenum((int)_num))
	{
		_num++;
	}
	return _num;
}

/****************************************************************************/

static ListItr* IfItrExistAlready(List* _ls, void* _key, EqualityFunction _func)
{
	ListItr itr;
	ListItr itrEnd;
	Element* elm;
	
	itrEnd = ListItrEnd(_ls);
	itr = ListItrBegin(_ls);
	
	while(itr != itrEnd)
	{
		elm = (Element*)ListItrGet(itr);
		if(1 == ((int)_func(_key, elm->m_key)))
		{
			return itr; 
		}
		itr =ListItrNext(itr);
	}
	return NULL;
}

static Element* IfElementExistAlready(List* _ls, void* _key, EqualityFunction _func, int _act)
{
	ListItr itr;
	
	itr = IfItrExistAlready(_ls, _key, _func);
	if(_act)
	{	
		return ((Element*)ListItrRemove(itr));
	}
	return (Element*)ListItrGet(itr);
}

/******************************************************************************************************/
  
static HashMap* StructCreate(size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc)
{
	HashMap* hs;
	size_t actualSize;
	
	hs = malloc(sizeof(HashMap));
	if(NULL == hs)
	{
		return NULL;
	}
	
	actualSize = FindPrime(_capacity);

	hs->m_map = malloc(actualSize*sizeof(List*));	
	if(NULL == hs->m_map)
	{
		free(hs);
		return NULL;
	}
		
	hs->m_mutex = malloc(MUTEX_AMOUNT * sizeof(pthread_mutex_t));      
	if(NULL == hs->m_mutex)
	{
		free(hs->m_map);
		free(hs);
		return NULL;
	}	
	
	hs->m_hashSize = actualSize;
	return hs;
} 

int CreateAllbuckets(List** _map, size_t _capacity)
{
	int i;
	for(i = 0; i < _capacity; ++i)
	{
		_map[i] = malloc(sizeof(List*));
		_map[i] = ListCreate();
		if(NULL == _map[i])
		{
			for(--i; i >= 0; --i)
			{
				free(_map[i]);
			}
			return 0;
		}
	}
	return 1;
}

int InitAll(HashMap* _hs, HashFunction _hashFunc, EqualityFunction _keysEqualFunc)
{
    int i;
    
    pthread_mutexattr_init (&_hs->m_mutexesAttr);
    pthread_mutexattr_settype(&_hs->m_mutexesAttr, PTHREAD_MUTEX_RECURSIVE);
   
    for(i = 0; i < MUTEX_AMOUNT; ++i)
    {
    	if(0 != pthread_mutex_init(&(_hs->m_mutex[i]), &_hs->m_mutexesAttr))
		{			
		    for(--i; i >= 0; --i)
    		{
				pthread_mutex_destroy(&(_hs->m_mutex[i]));
				pthread_mutexattr_destroy(&_hs->m_mutexesAttr);
			}
			return 0;
		}
    }
    
    _hs->m_mgc_num = MAGIC_NUM;  
    _hs->m_hashfunc = _hashFunc;
    _hs->m_equal = _keysEqualFunc;
    _hs->m_numOfelement = 0;
    return 1;
}


HashMap* HashMapCreate(size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc)
{
	HashMap* hs;
	
	if(0 == _capacity || NULL == _hashFunc || NULL == _keysEqualFunc)
	{
		return NULL;
	}
	
	hs = StructCreate(_capacity, _hashFunc, _keysEqualFunc);
	if(NULL == hs)
	{
		return NULL;
	}	
	
	if(!CreateAllbuckets(hs->m_map, hs->m_hashSize))
	{
		free(hs->m_mutex);
		free(hs->m_map);
		free(hs);
	}
	
	if(!InitAll(hs, _hashFunc, _keysEqualFunc))
	{
		free(hs->m_mutex);
		free(hs->m_map);
		free(hs);		
	}
	return hs;
}

  
/************************************************************************************************************/ 

static void DestList(List* _ls, keyDestroy _keyDest, valDestroy _valDest)
{
	ListItr itr;
	ListItr tempItr;
	ListItr itrEnd;
	Element* elm;
	
	itrEnd = ListItrEnd(_ls);
	itr = ListItrBegin(_ls);	
	while(itr != itrEnd)
	{
		tempItr =ListItrNext(itr);
		elm = (Element*)ListItrGet(itr);
		if(NULL != _keyDest)
		{
			_keyDest(elm->m_key);
		}
		if(NULL != _valDest)
		{
			_valDest((void*)(elm->m_data));
		}
		free(elm);
		ListItrRemove(itr);
		itr = tempItr;
	}
	ListDestroy(&_ls, NULL);
}

static void DestAll(HashMap* _map, keyDestroy _keyDest, valDestroy _valDest)
{
	int i;

	for(i = 0; i<_map->m_hashSize; ++i)
	{		
		DestList(_map->m_map[i], _keyDest, _valDest);
	}
	
	for(i = 0; i < MUTEX_AMOUNT; ++i)
	{		
		pthread_mutex_destroy(&(_map->m_mutex[i]));
	}
	pthread_mutexattr_destroy(&_map->m_mutexesAttr);
}


void HashMapDestroy(HashMap** _map, keyDestroy _keyDest, valDestroy _valDest)
{

	if(!IS_HASH(*_map))
	{
		return;
	}
	
	(*_map)->m_mgc_num = 0;
	
	DestAll(*_map, _keyDest, _valDest);
	
	free((*_map)->m_mutex);
	free((*_map)->m_map);
	free(*_map);
	*_map = NULL;
	
	return;
} 
  
/*****************************************************************************************/

static void PasteNodeNewList(ListItr _nod, HashFunction _func, List** _newLists, size_t _newSize)
{
	void* key;
	ListItr itrNewList;
	ListItr itrNext;
	size_t newIndex;
		
	key = ((Element*)ListItrGet(_nod))->m_key;
	newIndex = ((_func(key)) % _newSize);
	itrNewList = ListItrBegin(_newLists[newIndex]);		
	itrNext = ListItrNext(_nod);
	ListItrSplice (itrNewList, _nod, itrNext);
	return;	
}

static void PasteAllList(List* _ls, HashFunction _func, List** _mama, size_t _mamaSize)
{
	ListItr itr;
	ListItr itrEnd;
	ListItr itrNext;
		
	itrEnd = ListItrEnd(_ls);
	itr = ListItrBegin(_ls);	
	
	while(itr != itrEnd)
	{
		itrNext = ListItrNext(itr);
		
		PasteNodeNewList(itr, _func, _mama, _mamaSize);						
		
		itr = itrNext;
	}
}

Map_Result HashMapRehash(HashMap* _map, size_t _newCapacity)
{
	List** mamabucket;
	int i;
	int isCreated;
	size_t mamaSize;
	
	if(!IS_HASH(_map))
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	
	mamaSize = FindPrime(_newCapacity);
	
	mamabucket = malloc(mamaSize*sizeof(List*));
	
	isCreated = CreateAllbuckets(mamabucket, mamaSize);	
	
	if(!isCreated)
	{
		return MAP_ALLOCATION_ERROR; 
	}
	
	for(i = 0; i < _map->m_hashSize; ++i)
	{
		PasteAllList(_map->m_map[i], _map->m_hashfunc, mamabucket, mamaSize);
		DestList(_map->m_map[i], NULL, NULL);
	}	
	_map->m_map = mamabucket;
	_map->m_hashSize = mamaSize;
	return MAP_SUCCESS;	
}
  
/*********************************************************************************************/


Element* ElementCreate(const void* _key, const void* _value)
{
	Element* elm = malloc(sizeof(Element));
	if(NULL == elm)
	{
		return NULL;
	}
	elm->m_key = ((void*)_key);
	elm->m_data = ((void*)_value);
	return elm;
}

Map_Result HashMapInsert(HashMap* _map, const void* _key, const void* _value)
{	
	size_t bucketIndex;
	Element* elm;
	size_t mtxI;
	
	if(!IS_HASH(_map))
	{
		return MAP_UNINITIALIZED_ERROR;
	}
		
	if(NULL == _key)
	{
		return MAP_KEY_NULL_ERROR;
	}
	
	bucketIndex = ((_map->m_hashfunc(_key))%(_map->m_hashSize));	
	mtxI = bucketIndex % MUTEX_AMOUNT;	

	pthread_mutex_lock(&(_map->m_mutex[mtxI]));	
	if(NULL != IfElementExistAlready(_map->m_map[bucketIndex], (void*)_key, _map->m_equal, 0))
	{
		pthread_mutex_unlock(&(_map->m_mutex[mtxI]));												
		return MAP_KEY_DUPLICATE_ERROR;
	}	
	elm = ElementCreate(_key, _value);
	
	if(NULL == elm)
	{
		pthread_mutex_unlock(&(_map->m_mutex[mtxI]));													
		return MAP_ALLOCATION_ERROR;
	}				
	
	if(!ListPushHead(_map->m_map[bucketIndex], (void*)elm))
	{
		++_map->m_numOfelement;
		pthread_mutex_unlock(&(_map->m_mutex[mtxI]));														
		return MAP_SUCCESS;
	}	
	pthread_mutex_unlock(&(_map->m_mutex[mtxI]));
	return MAP_ALLOCATION_ERROR;	
} 

/****************************************************************************************************/  

Map_Result FatchAndDestroy(HashMap* _map, Element* _elm, void** _pKey, void** _pValue)
{		
	if(NULL == _elm)
	{
		return MAP_KEY_NOT_FOUND_ERROR;
	}

	*_pKey = *(void**)(_elm->m_key);
	*_pValue = *(void**)(_elm->m_data);
	
	pthread_mutex_lock(&(_map->m_mutex[0]));
	--_map->m_numOfelement;		
	pthread_mutex_unlock(&(_map->m_mutex[0]));															
	
	free(_elm);
	return MAP_SUCCESS;
}


Map_Result HashMapRemove(HashMap* _map, const void* _searchKey, void** _pKey, void** _pValue)
{
	size_t bucketIndex;
	Element* elm;
	size_t mtxI;

	if(!IS_HASH(_map))
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	if(NULL == _pKey || NULL == _pValue)
	{
		return MAP_INV_ARG;
	}	
	if(NULL == _searchKey)
	{
		return MAP_KEY_NULL_ERROR;
	}

	bucketIndex = (_map->m_hashfunc(_searchKey)%(_map->m_hashSize));
	mtxI = bucketIndex % MUTEX_AMOUNT;	

	pthread_mutex_lock(&(_map->m_mutex[mtxI]));
	elm = IfElementExistAlready(_map->m_map[bucketIndex], (void*)_searchKey, _map->m_equal, 1);
	pthread_mutex_unlock(&(_map->m_mutex[mtxI]));														
		
	return FatchAndDestroy(_map, elm, _pKey, _pValue);		;
}

/************************************************************************************/

Map_Result HashMapFind(const HashMap* _map, const void* _searchKey, void** _pValue)
{
	size_t bucketIndex;
	Element* elm = NULL;
	size_t mtxI;
	
	if(!IS_HASH(_map))
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	if(NULL == _searchKey || NULL == _pValue)
	{
		return MAP_INV_ARG;
	}		
	if(NULL == _searchKey)
	{
		return MAP_KEY_NULL_ERROR;
	}
	
	bucketIndex = ((_map->m_hashfunc(_searchKey))%(_map->m_hashSize));
	mtxI = bucketIndex % MUTEX_AMOUNT;	

	pthread_mutex_lock(&(_map->m_mutex[mtxI]));	
	elm = IfElementExistAlready(_map->m_map[bucketIndex], (void*)_searchKey, _map->m_equal, 0);
	pthread_mutex_unlock(&(_map->m_mutex[mtxI]));														

	if(NULL == elm)
	{
		return MAP_KEY_NOT_FOUND_ERROR;
	}
		
	*_pValue = (elm->m_data);
	
	return MAP_SUCCESS;
}
  
/***************************************************************************************/

size_t HashMapSize(const HashMap* _map)
{ 
	if(!IS_HASH(_map))
	{
		return 0;
	}
	return _map->m_numOfelement;
} 

/*****************************************************************************/

static size_t ForAllList(List* _ls, KeyValueActionFunction _action, void* _context, int* stop)
{
	ListItr itr;
	ListItr itrEnd;
	size_t counter = 0;
	void* key;
	void* data;
	itrEnd = ListItrEnd(_ls);
	itr = ListItrBegin(_ls);
	
	while(itr != itrEnd)
	{
		key = ((void*)((Element*)ListItrGet(itr))->m_key);
		data = ((void*)((Element*)ListItrGet(itr))->m_data);
		if(!_action(key, data, _context))
		{
			*stop = 1;
			return counter; 
		}
		++counter;
		itr =ListItrNext(itr);
	}
	return counter;
}


static void LockAll(HashMap* _map)
{
    int i;   
    for(i = 0; i < MUTEX_AMOUNT; ++i)
    {
		pthread_mutex_lock(&(_map->m_mutex[i]));
    }
}

static void FreeAll(HashMap* _map)
{
    int i;   
    for(i = 0; i < MUTEX_AMOUNT; ++i)
    {
		pthread_mutex_unlock(&(_map->m_mutex[i]));
    }
}

size_t HashMapForEach(const HashMap* _map, KeyValueActionFunction _action, void* _context)
{
	int i;
	size_t counter = 0;
	int ifStop = 0;
	if(!IS_HASH(_map))
	{
		return 0;
	}
	
	LockAll(( HashMap*)_map);
	for(i = 0; i < _map->m_hashSize; ++i)
	{
		counter += ForAllList(_map->m_map[i], _action, _context, &ifStop);
		if(ifStop)
		{
			break;
		}
	}
	FreeAll(( HashMap*)_map);
	return counter;
}
 
Map_Result HashMapLock(HashMap* _map, void* _key)
{
	size_t bucketIndex;
	size_t mtxI;
	
	if(!IS_HASH(_map))
	{
		return MAP_UNINITIALIZED_ERROR;
	}
		
	if(NULL == _key)
	{
		return MAP_KEY_NULL_ERROR;
	}
	
	bucketIndex = ((_map->m_hashfunc(_key))%(_map->m_hashSize));	
	mtxI = bucketIndex % MUTEX_AMOUNT;	
	pthread_mutex_lock(&(_map->m_mutex[mtxI]));	
	
	return MAP_SUCCESS;
}

Map_Result HashMapUnLock(HashMap* _map, void* _key)
{
	size_t bucketIndex;
	size_t mtxI;
	
	if(!IS_HASH(_map))
	{
		return MAP_UNINITIALIZED_ERROR;
	}
		
	if(NULL == _key)
	{
		return MAP_KEY_NULL_ERROR;
	}
	
	bucketIndex = ((_map->m_hashfunc(_key))%(_map->m_hashSize));	
	mtxI = bucketIndex % MUTEX_AMOUNT;	
	pthread_mutex_unlock(&(_map->m_mutex[mtxI]));	
	
	return MAP_SUCCESS;
}


/*********************************************************************************/  
  
#ifndef NDEBUG


static void HashMapForEachStatistic(const HashMap* _map, Map_Stats* stat)
{
	int i;
	size_t tempCount;
	stat->collisions = 0;
	stat->chains = 0;
	stat->maxChainLength = 0;
	
	for(i = 0; i < _map->m_hashSize; ++i)
	{
		tempCount = ListCountItems(*_map->m_map);
		
		if(tempCount > stat->maxChainLength)
		{
			stat->maxChainLength = tempCount;
		}		
		if(!ListIsEmpty(*_map->m_map))
		{
			++stat->chains;
		}		
	}
	stat->collisions = stat->pairs - stat->chains;
	stat->averageChainLength = stat->pairs / stat->chains;
	return;
}

Map_Stats HashMapGetStatistics(const HashMap* _map)
{
	Map_Stats* stat;
	stat = malloc(sizeof(Map_Stats*));
	stat->pairs = _map->m_numOfelement;
	stat->buckets = _map->m_hashSize;
	HashMapForEachStatistic(_map, stat);
	return *stat;
}

#endif /* NDEBUG */
 
  
  
  


    

