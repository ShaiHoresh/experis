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

    vector = VectorCreate(_size, _blockSize);

    if(NULL == vector)
    {
        return NULL;
    }

    stack = malloc(sizeof(Stack));
    if(NULL == stack)
    {
        return NULL;
    }

    stack->m_vector = vector;

    return stack;
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
	flag = VectorDelete(_stack->m_vector, _item);
	return flag;
}

/*****************************************************************/
ADTErr StackTop(Stack* _stack, int* _item)
{
	int numOfItems = 0;
	ADTErr error;
	
	if(NULL == _stack || NULL == _item)
	{
		return ERR_NOT_INITIALIZED;
	}

	error = VectorItemsNum(_stack->m_vector,  &numOfItems);

	if(error != ERR_OK)
	{
		return error;
	}
	error = VectorGet(_stack->m_vector, numOfItems, _item);

	return error;
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
			return 1;
		}
	}
	return 0;
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



















/*	printf("numOfItems = %d, _item = %d\n",numOfItems, *_item);*/
