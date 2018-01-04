#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "vector.c"

struct Stack
{
    Vector *m_vector;
};

void StackPrint(Stack* _stack);

Stack* StackCreate(size_t _size, size_t _blockSize)
{
	Vector* vector;
	Stack* stack;
	stack = malloc(sizeof(Stack));
	if(NULL == stack)
	{
		return NULL;
	}
	else
	{
		vector = VectorCreate(_size, _blockSize);
	}

	if(NULL == vector)
	{
		free(stack);
		return NULL;
	}
	else
	{
		stack->m_vector = vector;
	}
}

/*****************************************************************/
void StackDestroy(Stack* _stack)
{
	if(_stack != NULL)
	{
		VectorDestroy(_stack->m_vector);
	}
	free(_stack);
}

/*****************************************************************/
ADTErr StackPush(Stack* _stack, int _item)
{
	ADTErr flag;
	if(NULL == _stack)
	{
		return ERR_NOT_INITIALIZED;
	}
	flag = VectorAdd(_stack->m_vector, _item);
	
	return flag;
}

/*****************************************************************/
ADTErr StackPop(Stack* _stack, int* _item)
{
	ADTErr flag = ERR_OK;
	if(NULL == _stack)
	{
		return ERR_NOT_INITIALIZED;
	}
	flag = VectorDelete(_stack->m_vector, *_item);
	return flag;
}

/*****************************************************************/
ADTErr StackTop(Stack* _stack, int* _item)
{
	if(NULL == _stack)
	{
		return ERR_NOT_INITIALIZED;
	}
	VectorGet(_stack->m_vector, _stack->m_vector->m_nItems, *_item);
	return ERR_OK;
}

/*****************************************************************/
int StackIsEmpty(Stack* _stack)
{
	int numOfItems;
	ADTErr flag;
	
	if(NULL == _stack)
	{
		return 1;
	}
	flag = VectorItemsNum(_stack->m_vector, &numOfItems);
	if(flag == ERR_OK)
	{
		if(0 != numOfItems)
		{
			return 0;
		}
	}
	return 1;
}

/*****************************************************************/
void StackPrint(Stack* _stack)
{
	if(NULL == _stack)
	{
		return;
	}
	VectorPrint(_stack->m_vector);
}




















