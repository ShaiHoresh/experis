/*includes and macros*/ 
#include <stdlib.h> /*malloc(?)*/
#include "../../inc/Stack.h"
#include "../../inc/DoubleLL.h"
/*#include "../../inc/ADTDefs.h"*/


Stack* StackCreate(void)
{
    return (Stack*)ListCreate();
}

void StackDestroy(Stack** _stack, StackElementAction _destroy)
{
    ListDestroy((List**)_stack, _destroy);
}

STACKErrors StackPush(Stack* _stack, void* _item)
{
    return ListPushTail((List*)_stack, _item) + 100;
}

STACKErrors StackPop(Stack* _stack, void** _item)
{
    return ListPopTail((List*)_stack, _item) + 100;
}

STACKErrors StackTop(Stack* _stack, void** _item)
{
    ListItr itr;

    itr = ListItrEnd(_stack);
    itr = ListItrPrev(itr);
    if(itr != ListItrPrev(itr))
    {
        *_item = ListItrGet(itr);
        return STACK_OK;
    }
    else
    {
        *_item = NULL;
        return STACK_NOT_INITIALIZED;
    }
}

int StackIsEmpty(Stack* _stack)
{
    return ListIsEmpty((List*)_stack);
}
