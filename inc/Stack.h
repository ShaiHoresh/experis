#ifndef __STACK_H__
#define __STACK_H__
/*TODO update errors!*/
/** 
 * @brief Create a Generic Stack data type
 * that stores pointer to user provided elements of generic type
 * The Stack is heap allocated and can grow and shrink on demand.
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 
 
#include "DoubleLL.h"

typedef enum
{
    STACK_OK = 100,
    STACK_NOT_INITIALIZED,
    STACK_REALLOCATION_FAILED,
    STACK_IS_EMPTY
} STACKErrors;

typedef List Stack;

typedef int (*StackElementAction)(void*, void*);

/**  
 * @brief Dynamically create a new stack object of given capacity and  
 * @param[in] _initialCapacity - initial capacity, number of elements that can be stored initially
 * @param[in] _blockSize - the stack will grow or shrink on demand by this size 
 * @return stack * - on success / NULL on fail 
 *
 * @warning if _blockSize is 0 the stack will be of fixed size. 
 * @warning if both _initialCapacity and _blockSize are zero function will return NULL.
 */
Stack* StackCreate(void);

/**  
 * @brief Dynamically deallocate a previously allocated stack  
 * @param[in] _stack - Stack to be deallocated.
 * @param[in] _elementDestroy : A function pointer to be used to destroy all elements in the stack
 *             or a null if no such destroy is required
 * @return void
 */
void StackDestroy(Stack** _stack, StackElementAction _destroy);

/**  
 * @brief Push an Item to the top of the stack.  
 * @param[in] _stack - Stack to push any data to.
 * @param[in] _item - Item to add.
 * @return success or error code 
 * @retval ERR_OK on success 
 * @retval ERR_NOT_INITIALIZED of the stack is NULL
 * @retval ERR_REALLOCATION_FAILED if had to reallocate, but failed
 */
STACKErrors StackPush(Stack* _stack, void*  _item);

/**  
 * @brief Pop an Item from top of the stack.  
 * @param[in] _stack - Stack to pop any data from.
 * @param[in] _item - void** to get the data.
 * @return success or error code 
 * @retval STACK_OK on success 
 * @retval STACK_NOT_INITIALIZED of the stack is NULL
 * @retval STACK_REALLOCATION_FAILED if had to reallocate, but failed
 */
STACKErrors StackPop(Stack* _stack, void** _item);

/**  
 * @brief retrieve Item from top of the stack.  
 * @param[in] _stack - Stack to pop any data from.
 * @param[in] _item - void** to get the data.
 * @return success or error code 
 * @retval STACK_OK on success 
 * @retval STACK_NOT_INITIALIZED of the stack is NULL
 */
STACKErrors StackTop(Stack* _stack, void** _item);

/**  
 * @brief check if the stack is empty.
 * @param[in] _stack - Stack to check.
 * @return 1 if empty / 0 if not.
 */
int StackIsEmpty(Stack* _stack);

#endif /*__STACK_H__*/
