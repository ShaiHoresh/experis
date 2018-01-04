#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

struct Vector{
    int*    m_items;
    size_t  m_originalSize;   /* original allocated space for items) */
    size_t  m_size;                 /* actual allocated space for items) */
    size_t  m_nItems;           /* actual number of items */
    size_t  m_blockSize;     /* the chunk size to be allocated when no space*/
} ;

ADTErr ExtendIfNeeded(Vector *_vector);
ADTErr ShrinkArray(Vector *_vector);
void VectorPrint(Vector *_vector);

/*****************************************************************/
Vector* VectorCreate(size_t _initialSize, size_t _extensionBblockSize)
{
	
	Vector* vector = NULL;
	
	if(0 == _initialSize && 0 == _extensionBblockSize)
	{
		return NULL;
	}
	
	vector = malloc(sizeof(Vector));
	
	if(NULL == vector)
	{
		return NULL;
	}
	else
	{
		vector->m_items = malloc(_initialSize * sizeof(int));	
	}
	
	if(NULL == vector->m_items)
	{
		free(vector);
		return NULL;
	}
	else
	{

		vector->m_originalSize = _initialSize;
		vector->m_size = _initialSize;
		vector->m_nItems = 0;
		vector->m_blockSize = _extensionBblockSize;
	}
	return vector;
}

/*****************************************************************/
void VectorDestroy(Vector* _vector)
{
	
	if(_vector != NULL)
	{
		if(_vector->m_items != NULL)
		{	
			free(_vector->m_items);
			_vector->m_items = NULL;
		}
		free(_vector);
	}
	return;
}

/*****************************************************************/
ADTErr VectorAdd(Vector *_vector,  int  _item)   /* Add item to end. */
{

	ADTErr flag;
	if(NULL == _vector || NULL == _vector->m_items)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	if(_vector->m_nItems == _vector->m_size)
	{
		if((flag = ExtendIfNeeded(_vector)) != ERR_OK){
			return flag;
		}
	}

	_vector->m_items[_vector->m_nItems] = _item;
	_vector->m_nItems ++;
	
	return ERR_OK;
}

/*****************************************************************/
ADTErr VectorDelete(Vector *_vector,  int* _item)
{
	ADTErr flag = ERR_OK;
	if(NULL == _vector || NULL == _vector->m_items || NULL == _item)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	if(_vector->m_nItems == 0)
	{
	return ERR_UNDERFLOW;		
	}	
	*_item = _vector->m_items[_vector->m_nItems - 1];
	_vector->m_nItems --;

	if((_vector->m_size) - (_vector->m_nItems) >= (2 * _vector->m_blockSize) && (_vector->m_originalSize) <= (_vector->m_size - _vector->m_blockSize))
	{
		flag = ShrinkArray(_vector);
	}

	return flag;
}

/*****************************************************************/
ADTErr VectorGet(Vector *_vector, size_t _index, int *_item)
{
	if(NULL == _vector || NULL == _vector->m_items || NULL == _item)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_index > _vector->m_nItems)
	{
		return ERR_WRONG_INDEX;
	}
	*_item = _vector->m_items[_index - 1];
	return ERR_OK;
}

/*****************************************************************/
ADTErr VectorSet(Vector *_vector, size_t _index, int  _item)
{
	if(NULL == _vector || NULL == _vector->m_items)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	if(_index >= _vector->m_nItems)
	{
		return ERR_OVERFLOW;
	}
	
	_vector->m_items[_index] = _item;
	return ERR_OK;
}

/*****************************************************************/
ADTErr VectorItemsNum(Vector *_vector, int* _numOfItems)
{
	if(NULL == _vector || NULL == _vector->m_items)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	*_numOfItems = _vector->m_nItems;
	return ERR_OK;
}


/*****************************************************************/
/*  Unit-Test functions  */

void VectorPrint(Vector *_vector)
{
	int i;

	if(NULL == _vector || NULL == _vector->m_items)if(NULL == _vector->m_items) return;

	for(i = 0; i < _vector->m_nItems; ++i)
	{
		printf("%d ", _vector->m_items[i]);
	}
	printf("\n");
}

/*****************************************************************/
/*****************************************************************/
ADTErr ExtendIfNeeded(Vector *_vector)
{
	int* temp;
	if(0 == _vector->m_blockSize)
	{
		return ERR_OVERFLOW;
	}
	
	temp = realloc(_vector->m_items, (_vector->m_size + _vector->m_blockSize) * sizeof(int));
	if(NULL == temp)
	{
		return ERR_REALLOCATION_FAILED;
	}
	_vector->m_items = temp;
	_vector->m_size += _vector->m_blockSize;
	return ERR_OK;
}

/*****************************************************************/
ADTErr ShrinkArray(Vector *_vector)
{
	int* temp;
	temp = realloc(_vector->m_items, (_vector->m_size + _vector->m_blockSize) * sizeof(int));
	if(temp == NULL)
	{
		return ERR_REALLOCATION_FAILED;
	}
	_vector->m_items = temp;
	_vector->m_size -= _vector->m_blockSize;
	return ERR_OK;
}

