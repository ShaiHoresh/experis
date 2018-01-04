#include "../../inc/vector.h"

#include <stdlib.h> /* malloc */

#define MAGIC 0xDEADBEAF

struct Vector{
    void**  m_items;        /* pointer to pointers array */
    size_t  m_originalSize; /* original allocated space for items) */
    size_t  m_size;         /* actual allocated space for items) */
    size_t  m_nItems;       /* actual number of items */
    size_t  m_blockSize;    /* the chunk size to be allocated when no space*/
    unsigned int m_secNumber;
} ;

/***TODO add description*******/
static ADTErr ExtendIfNeeded(Vector *_vector);
static ADTErr ShrinkArray(Vector *_vector);
/**********/


Vector* VectorCreate(size_t _initialCapacity, size_t _blockSize)
{
	Vector* vector = NULL;
	
	if(0 == _initialCapacity && 0 == _blockSize)
	{
		return NULL;
	}
	
	vector = malloc(sizeof(Vector));
	if(NULL == vector)
	{
		return NULL;
	}

	vector->m_items = malloc(_initialCapacity*sizeof(void*));	

	if(NULL == vector->m_items)
	{
		free(vector);
		return NULL;
	}

	vector->m_originalSize = _initialCapacity;
	vector->m_size = _initialCapacity;
	vector->m_nItems = 0;
	vector->m_blockSize = _blockSize;
	vector->m_secNumber = MAGIC;

	return vector;
}

void VectorDestroy(Vector** _vector, VectorElementAction _action)
{
   /* int i;*/
    if(*_vector != NULL && (*_vector)->m_secNumber == MAGIC)
	{
		if((*_vector)->m_nItems > 0)
		{	
			if(NULL != _action)
			{
			    /*for(i = 0; i < (*_vector)->m_nItems; ++i)
			    {
			        _elementDestroy((*_vector)->m_items[i]);
			         free((*_vector)->m_items[i]);
			    }
			    */
			    VectorForEach(*_vector, _action, NULL);
		    }
			free((*_vector)->m_items);
			(*_vector)->m_items = NULL;
		}
		(*_vector)->m_secNumber = 0;
		free(*_vector);
		*_vector = NULL;
	}
	return;
}
 
ADTErr VectorAppend(Vector* _vector, void* _item)
{
	ADTErr flag;
	if(NULL == _vector || NULL == _vector->m_items)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	if(_vector->m_nItems == _vector->m_size)
	{
		if((flag = ExtendIfNeeded(_vector)) != ERR_OK)
		{
			return flag;
		}
	}

	_vector->m_items[_vector->m_nItems] = _item;
	_vector->m_nItems ++;
	
	return ERR_OK;
}

ADTErr VectorRemove(Vector* _vector, void** _pValue)
{
	ADTErr flag = ERR_OK;
	if(NULL == _vector || NULL == _vector->m_items/* || NULL == _pValue*/)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	if(_vector->m_nItems == 0)
	{
	return ERR_UNDERFLOW;		
	}	
	*_pValue = _vector->m_items[_vector->m_nItems - 1];
	_vector->m_nItems --;

	if((_vector->m_size) - (_vector->m_nItems) >= (2 * _vector->m_blockSize) && (_vector->m_originalSize) <= (_vector->m_size - _vector->m_blockSize))
	{
		flag = ShrinkArray(_vector);
	}

	return flag;
}

ADTErr VectorGet(const Vector* _vector, size_t _index, void** _pValue)
{
	if(NULL == _vector || NULL == _vector->m_items || NULL == _pValue)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_index > _vector->m_nItems || _index == 0)
	{
		return ERR_WRONG_INDEX;
	}
	*_pValue = _vector->m_items[_index - 1];
	return ERR_OK;
}

ADTErr VectorSet(Vector* _vector, size_t _index, void* _value)
{
	if(NULL == _vector)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	if(_index > _vector->m_nItems || _index == 0)
	{
		return ERR_WRONG_INDEX;
	}
	
	_vector->m_items[_index - 1] = _value;
	return ERR_OK;
}

size_t VectorSize(const Vector* _vector)
{
	if(NULL == _vector || NULL == _vector->m_items)
	{
		return 0;
	}
	
	return _vector->m_nItems;
}

size_t VectorCapacity(const Vector* _vector)
{
	if(NULL == _vector || NULL == _vector->m_items)
	{
		return 0;
	}
	
	return _vector->m_size;    
}

size_t VectorForEach(const Vector* _vector, VectorElementAction _action, void* _context)
{
    size_t i;

    if(NULL == _vector || NULL == _vector->m_items || NULL == _action)
    {
        return 0;
    }

    for(i = 0; i < _vector->m_nItems; ++i)
    {
        if(_action(_vector->m_items[i], _context) == 0)
        {
            break;
        }
    }

    return i;
}


/**********************Aux functions*************************/

static ADTErr ExtendIfNeeded(Vector *_vector)
{
	void* temp;
	if(0 == _vector->m_blockSize)
	{
		return ERR_OVERFLOW;
	}
	
	temp = realloc(_vector->m_items, (_vector->m_size + _vector->m_blockSize)*sizeof(void*));
	if(NULL == temp)
	{
		return ERR_REALLOCATION_FAILED;
	}
	_vector->m_items = temp;
	_vector->m_size += _vector->m_blockSize;
	return ERR_OK;
}

static ADTErr ShrinkArray(Vector *_vector)
{
	void* temp;
	temp = realloc(_vector->m_items, (_vector->m_size + _vector->m_blockSize)*sizeof(void*));
	if(temp == NULL)
	{
		return ERR_REALLOCATION_FAILED;
	}
	_vector->m_items = temp;
	_vector->m_size -= _vector->m_blockSize;
	return ERR_OK;
}
