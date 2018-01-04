#include "stack.h"
#include "ADTDefs.h"

#include <stdio.h>
#include <stdlib.h>

void TestCreateStack();

void TestPushToEmpty();
void TestPushOnItems();
void TestPushNull();

void TestPopAfterPush();
void TestPopNull();

void TestTop();
void TestTopFull();
void TestTopNull();
void TestTopAfterPop();

void TestIsEmpty();
void TestIsEmptyAfterPush();
void TestIsEmptyAfterPop();
void TestIsEmptyNULL();
void TestIsEmptyAfterEmptying();

void TestPopWhenEmpty();

Stack* StackCreate( size_t _size, size_t _blockSize);
void StackDestroy(Stack* _stack);
ADTErr StackPush(Stack* _stack, int  _item);
ADTErr StackPop(Stack* _stack, int* _item);
ADTErr StackTop(Stack* _stack, int* _item);
int StackIsEmpty(Stack* _stack);
void StackPrint(Stack* _stack);

int main()
{
	TestCreateStack();

	TestPushToEmpty();
	TestPushOnItems();
	TestPushNull();

	TestPopAfterPush();
	TestPopNull();

	TestTop();
	TestTopFull();
	TestTopNull();
	TestTopAfterPop();

	TestIsEmpty();
	TestIsEmptyAfterEmptying();
	TestIsEmptyAfterPush();
	TestIsEmptyAfterPop();
	TestIsEmptyNULL();

	TestPopWhenEmpty();	

return 0;
}

void TestCreateStack()
{
	Stack* stack;
	stack = StackCreate(3, 1);
	if(NULL == stack)
	{
		printf("FAILED:		Test create stack\n");
	}
	else
	{
		printf("SUCCEEDED:	Test create stack\n");
	}
	StackDestroy(stack);
}

/**********************************************************/
void TestPushToEmpty()
{
	Stack* stack;
	ADTErr flag;
	
	stack = StackCreate(0, 1);
	flag = StackPush(stack, 1);
	
	if(ERR_OK != flag)
	{
		printf("FAILED:		Test push to empty stack\n");
	}
	else
	{
		printf("SUCCEEDED:	Test push to empty stack\n");
	}
	StackDestroy(stack);
}

/**********************************************************/
void TestPushOnItems()
{
	Stack* stack;
	ADTErr flag;
	int i;
	
	stack = StackCreate(2, 1);
	for(i = 0; i < 5; ++i)
	{
		flag = StackPush(stack, 1);
	}
	
	if(ERR_OK != flag)
	{
		printf("FAILED:		Test push to stack\n");
	}
	else
	{
		printf("SUCCEEDED:	Test push to stack\n");
	}
	StackDestroy(stack);
}

/**********************************************************/
void TestPushNull()
{
	Stack* stack = NULL;
	ADTErr flag;
	
	flag = StackPush(stack, 1);
	
	if(ERR_OK == flag)
	{
		printf("FAILED:		Test push to NULL stack\n");
	}
	else
	{
		printf("SUCCEEDED:	Test push to NULL stack\n");
	}
	StackDestroy(stack);
}

/**********************************************************/
void TestPopAfterPush()
{
	Stack* stack;
	ADTErr flag;
	int i = 0, item = 0;
	
	stack = StackCreate(0, 1);
	for(i = 0; i < 5; ++i)
	{
		StackPush(stack, i);
	}
	
	flag = StackPop(stack, &item);
	
	if(ERR_OK == flag && 4 == item)
	{
		printf("SUCCEEDED:	Test pop from stack\n");
	}
	else
	{
		printf("FAILED:		Test pop from stack\n");
	}
	StackDestroy(stack);
}

/**********************************************************/
void TestPopNull()
{
	Stack* stack = NULL;
	ADTErr flag;
	int item;
	
	flag = StackPop(stack, &item);
	
	if(ERR_OK == flag)
	{
		printf("FAILED:		Test pop from NULL stack\n");
	}
	else
	{
		printf("SUCCEEDED:	Test pop from NULL stack\n");
	}
}

/**********************************************************/
void TestTop()
{
	Stack* stack;
	ADTErr flag;
	int i, item;
	
	stack = StackCreate(5, 1);
	for(i = 0; i < 3; ++i)
	{
		StackPush(stack, i);
	}

	flag = StackTop(stack, &item);
	
	if(ERR_OK == flag && 2 == item)
	{
		printf("SUCCEEDED:	Test Top\n");
	}
	else
	{
		printf("FAILED: 	Test Top\n");
	}
	StackDestroy(stack);
}

/**********************************************************/
void TestTopFull()
{
	Stack* stack;
	ADTErr flag;
	int i, item = 300;
	
	stack = StackCreate(5, 1);
	for(i = 0; i < 5; ++i)
	{
		StackPush(stack, i);
	}
	
	flag = StackTop(stack, &item);
	
	if(ERR_OK == flag && 4 == item)
	{
		printf("SUCCEEDED:	Test Top full\n");
	}
	else
	{
		printf("FAILED:		Test Top full\n");
	}
	StackDestroy(stack);
}

/**********************************************************/
void TestTopNull()
{
	Stack* stack = NULL;
	ADTErr flag;
	int item = 300;

	flag = StackTop(stack, &item);

	if(ERR_OK != flag)
	{
		printf("SUCCEEDED:	Test Top NULL\n");
	}
	else
	{
		printf("FAILED:		Test Top NULL\n");
	}
}

/**********************************************************/
void TestTopAfterPop()
{
	Stack* stack;
	ADTErr flag;
	int i, item;
	
	stack = StackCreate(5, 1);
	for(i = 0; i < 5; ++i)
	{
		StackPush(stack, i);
	}
	StackPop(stack, &item);
	StackPop(stack, &item);
	flag = StackTop(stack, &item);
	if(ERR_OK == flag && 2 == item)
	{
		printf("SUCCEEDED:	Test Top After Pop\n");
	}
	else
	{
		printf("FAILED:		Test Top After Pop\n");
	}
	StackDestroy(stack);
}

/**********************************************************/
void TestIsEmpty()
{
	Stack* stack;
	int flag;
	stack = StackCreate(5, 1);
	
	flag = StackIsEmpty(stack);
	
	if(0 != flag)
	{
		printf("FAILED:		Test is empty?\n");
	}
	else
	{
		printf("SUCCEEDED:	Test is empty?\n");
	}
	StackDestroy(stack);
}

/**********************************************************/
void TestIsEmptyAfterEmptying()
{
	Stack* stack;
	int flag, temp, i;
	
	stack = StackCreate(5, 1);
	
	for(i = 0; i < 5; ++i)
	{
		StackPush(stack, i);
	}
	
		for(i = 0; i < 5; ++i)
	{
		StackPop(stack, &temp);
	}
	
	flag = StackIsEmpty(stack);
	
	if(0 != flag)
	{
		printf("FAILED:		Test is empty After Emptying?\n");
	}
	else
	{
		printf("SUCCEEDED:	Test is empty After Emptying?\n");
	}
	StackDestroy(stack);
}

/**********************************************************/
void TestIsEmptyAfterPush()
{
	Stack* stack;
	int flag, i;
	
	stack = StackCreate(5, 1);
	
	for(i = 0; i < 5; ++i)
	{
		StackPush(stack, i);
	}
	
	flag = StackIsEmpty(stack);
	
	if(0 == flag)
	{
		printf("FAILED:		Test is empty After Push?\n");
	}
	else
	{
		printf("SUCCEEDED:	Test is empty After Push?\n");
	}
	StackDestroy(stack);
}

/**********************************************************/
void TestIsEmptyAfterPop()
{
	Stack* stack;
	int flag, temp, i;
	
	stack = StackCreate(5, 1);
	
	for(i = 0; i < 5; ++i)
	{
		StackPush(stack, i);
	}
	StackPop(stack, &temp);
	flag = StackIsEmpty(stack);
	
	if(0 == flag)
	{
		printf("FAILED:		Test is empty After Pop?\n");
	}
	else
	{
		printf("SUCCEEDED:	Test is empty After Pop?\n");
	}
	StackDestroy(stack);
}

/**********************************************************/
void TestIsEmptyNULL()
{
	Stack* stack = NULL;
	int flag;

	flag = StackIsEmpty(stack);
	
	if(0 == flag)
	{
		printf("FAILED:		Test is NULL empty?\n");
	}
	else
	{
		printf("SUCCEEDED:	Test is NULL empty?\n");
	}
}

/**********************************************************/

void TestPopWhenEmpty()
{
	Stack* stack;
	ADTErr flag;
	int i, item;
	
	stack = StackCreate(0, 1);
	for(i = 0; i < 5; ++i)
	{
		StackPush(stack, i);
	}
	for(i = 0; i < 8; ++i)
	{
		flag = StackPop(stack, &item);
		if(flag != ERR_OK)
		{
			break;
		}
	}
	
	if(ERR_OK != flag)
	{
		printf("SUCCEEDED:	Test pop from stack\n");
	}
	else
	{
		printf("FAILED:		Test pop from stack\n");
	}
	StackDestroy(stack);
}
