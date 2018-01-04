#include <stdio.h>
#include <stdlib.h>
#include "../../inc/Stack.h"

void TestCreateStack();
void TestPush();
void TestPop();
void TestDestroy();
void TestTop();
void TestIsEmpty();
void TestTopEmpty();

int DestroyInt(void* _data, void* _context)
{
    free(_data);
}

void PrintFormat(int flag)
{
    flag ? printf("Succeeded:   ") : printf("Failed:        ");
}

int main()
{
    TestCreateStack();
    TestPush();
    TestPop();
    TestDestroy();
    TestTop();
    TestIsEmpty();
    TestTopEmpty();
    
    return 0;
}


void TestCreateStack()
{
    Stack* stack;
    
    stack = StackCreate();
    PrintFormat(stack != NULL);
    printf("TestCreate\n");
    
    StackDestroy(&stack, DestroyInt);
}

void TestPush()
{
    Stack* stack;
    STACKErrors error;
    int* data;
    int b = 5;
    
    stack = StackCreate();
    data = malloc(sizeof(int));
    *data = b;
    error = StackPush(stack, (void*)data);
    
    PrintFormat(error == STACK_OK);
    printf("Test Push\n");
    
    StackDestroy(&stack, DestroyInt);
}

void TestPop()
{
    Stack* stack;
    STACKErrors error;
    int* data;
    int b = 5;
    void* ret = NULL;
    
    stack = StackCreate();
    data = malloc(sizeof(int));
    *data = b;
    StackPush(stack, (void*)data);
    
    error = StackPop(stack, &ret);
    PrintFormat(error == STACK_OK && *(int*)ret == b);
    printf("Test Pop\n");
    
    StackDestroy(&stack, DestroyInt);
}

void TestDestroy()
{
    Stack* stack;
    
    stack = StackCreate();
    StackDestroy(&stack, DestroyInt);

    PrintFormat(stack == NULL);
    printf("Test Destroy\n");
}


void TestTop()
{
    Stack* stack;
    STACKErrors error;
    int* data, *more;
    void* ret = NULL;
    int b = 5, c = 6;
    
    stack = StackCreate();
    data = malloc(sizeof(int));
    *data = b;
    StackPush(stack, (void*)data);
    more = malloc(sizeof(int));
    *more = c;
    error = StackPush(stack, (void*)more);
    
    error = StackTop(stack, &ret);
    
    PrintFormat(error == STACK_OK && *(int*)ret == c);
    printf("Test Top\n");
    
    StackDestroy(&stack, DestroyInt);
}

void TestTopEmpty()
{
    Stack* stack;
    STACKErrors error;
    void* ret = NULL;
    
    stack = StackCreate();
    
    error = StackTop(stack, &ret);
    
    PrintFormat(error != STACK_OK);
    printf("Test Top Empty\n");
    
    StackDestroy(&stack, DestroyInt);
}

/* This is not a unit test - tests both empty and not empty stacks */
void TestIsEmpty()
{
    Stack* stack;
    int* data;
    int b = 5;
    void* ret = NULL;
    int full, empty;
    
    stack = StackCreate();
    data = malloc(sizeof(int));
    *data = b;
    
    StackPush(stack, (void*)data);
    full = StackIsEmpty(stack);
    
    StackPop(stack, &ret);
    empty = StackIsEmpty(stack);
    
    PrintFormat(full == 0 && empty == 1);
    printf("Test Is Empty\n");
    
    StackDestroy(&stack, DestroyInt);
}

