#include "stack.h"
#include "ADTDefs.h"

#include <stdio.h>
#include <stdlib.h>
/*
void TestCreateStack();

void TestPushToEmpty();
void TestPushOnItems();
void TestPushNull();

void TestPopAfterPush();
void TestPopNull();

void TestTop();
void TestTopFull();
void TestTopNull();
void TestTopAfterPush();
void TestTopAfterPop();

void TestIsEmpty();
void TestIsEmptyWhenEmpty();
void TestIsEmptyAfterPush();
void TestIsEmptyAfterPoP();

void TestPopWhenEmpty();
*/
Stack*  StackCreate( size_t _size, size_t _blockSize);
void    StackDestroy(Stack* _stack);
ADTErr  StackPush(Stack* _stack, int  _item);
ADTErr  StackPop(Stack* _stack, int* _item);
ADTErr  StackTop(Stack* _stack, int* _item);
int     StackIsEmpty(Stack* _stack);

int main()
{

	Stack* stack;
	stack = StackCreate(0,1);
	StackPush(stack,1);
	StackPush(stack,4);
	StackPush(stack,5);
	StackPush(stack,2);
	StackPrint(stack);
	StackDestroy(stack);

/*
TestPushToEmpty();
TestPushOnItems();
TestPushNull();

TestPopAfterPush();
TestPopNull();

TestTop();
TestTopFull();
TestTopNull();
TestTopAfterPush();
TestTopAfterPop();

TestIsEmpty();
TestIsEmptyWhenEmpty();
TestIsEmptyAfterPush();
TestIsEmptyAfterPoP();

TestPopWhenEmpty();	
*/
return 0;
}
/*
void TestPushToEmpty();
void TestPushOnItems();
void TestPushNull();

void TestPopAfterPush();
void TestPopNull();

void TestTop();
void TestTopFull();
void TestTopNull();
void TestTopAfterPush();
void TestTopAfterPop();

void TestIsEmpty();
void TestIsEmptyWhenEmpty();
void TestIsEmptyAfterPush();
void TestIsEmptyAfterPoP();

void TestPopWhenEmpty();*/
