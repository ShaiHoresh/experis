#ifndef __GENERIC_DOUBLE_LINKED_LIST_H__
#define __GENERIC_DOUBLE_LINKED_LIST_H__

/** 
 * @brief Create a Generic Double Linked List data type
 * that stores pointer to user provided elements of generic type
 * The Double Linked List is heap allocated and can grow and shrink on demand.
 * 
 * @author Author Gal Rosenthal (galikrosentalik@gmail.com) 
*/

#include <stddef.h>

typedef enum
{
    LIST_OK,
    LIST_UNINITIALIZED,
    LIST_ALLOCATION_FAILED,
    LIST_IS_EMPTY,
    LIST_INV_ARG,
    LIST_ITEM_NOT_FOUND
} ListErrors;

typedef struct List List;

/**
 * @brief A template to a user function that can work on an element in the list.
 *
 * @param[in] _element: Pointer to the item in the list.
 * @param[in] _context: a context in which the function should work.
 *
 * @return 1 on success / 0 on fail.
*/
typedef int (*UserActionFunc)(void* _element, void* _context);


typedef int (*PredicateFunc)(void* _element, void* _context);

/**
 * @brief The function creates a list.
 *
 * @return List*: on success / NULL on fail.
*/
List* ListCreate(void);

/**
 * @brief The function destroys a list.
 *
 * @param[in] _list: Pointer to a list.
 * @param[in] _destroyFunc: Pointer to a destory function for the data.
 *
 * @return void
*/
void ListDestroy(List** _list, UserActionFunc _destoryFunc);

/**
 * @brief The function push data to the head of the list.
 *
 * @param[in] _list: Pointer to a list.
 * @param[in] _data: Pointer to the data to add.
 *
 * @return error code.
 * @retval LIST_OK on success.
 * @retval LIST_UNINITIALIZED if _list NULL.
 * @retval LIST_ALLOCATION_FAILED if it failed to create node.
*/
ListErrors ListPushHead(List* _list, void* _data);

/**
 * @brief The function push data to the tail of the list.
 *
 * @param[in] _list: Pointer to a list.
 * @param[in] _data: Pointer to the data to add.
 *
 * @return error code.
 * @retval LIST_OK on success.
 * @retval LIST_UNINITIALIZED if _list NULL.
 * @retval LIST_ALLOCATION_FAILED if it failed to create node.
*/
ListErrors ListPushTail(List* _list, void* _data);

/**
 * @brief The function removes data from the head of the list.
 *
 * @param[in] _list: Pointer to a list.
 * @param[in/out] _data: Pointer to pointer of variable to receive the deleted item.
 *
 * @return error code.
 * @retval LIST_OK on success.
 * @retval LIST_UNINITIALIZED if _list NULL.
 * @retval ERR_LIST_IS_EMPTY if the list is empty.
*/
ListErrors ListPopHead(List* _list, void* *_data);

/**
 * @brief The function removes data from the tail of the list.
 *
 * @param[in] _list: Pointer to a list.
 * @param[in/out] _data: Pointer to pointer of variable to receive the deleted item.
 *
 * @return error code.
 * @retval LIST_OK on success.
 * @retval LIST_UNINITIALIZED if _list NULL.
 * @retval ERR_LIST_IS_EMPTY if the list is empty.
*/
ListErrors ListPopTail(List* _list, void* *_data);

/**
 * @brief The function searches if a data exists in the list.
 *        It will return the first item that matches from the head.
 *
 * @param[in] _list: Pointer to a list.
 * @param[in] _predicateFunc: Pointer to a function to predicate it according to a context.
 * @param[in] _context: Pointer to the context to pass to the Predicate function.
 * @param[in/out] _item: Pointer to pointer to store the pointer for data.
 *                       If the data is not found then it will be set to NULL.
 *
 * @return error code.
 * @retval LIST_OK on success.
 * @retval LIST_UNINITIALIZED if _list NULL.
*/
ListErrors FindFirstForward(const List* _list, PredicateFunc _predicateFunc, void* _context, void* *_item);

/**
 * @brief The function searches if a data exists in the list.
 *        It will return the first item that matches from the tail.
 *
 * @param[in] _list: Pointer to a list.
 * @param[in] _predicateFunc: Pointer to a function to predicate it according to a context.
 * @param[in] _context: Pointer to the context to pass to the Predicate function.
 * @param[in/out] _item: Pointer to pointer to store the pointer for data.
 *                       If the data is not found then it will be set to NULL.
 *
 * @return error code.
 * @retval LIST_OK on success.
 * @retval LIST_UNINITIALIZED if _list NULL.
*/
ListErrors FindFirstBackward(const List* _list, PredicateFunc _predicateFunc, void* _context, void* *_item);

/**
 * @brief The function counts the amount of nodes.
 *
 * @param[in] _list: Pointer to a list.
 *
 * @return The number of nodes in the list.
 *
 * @warning Will return 0 if _list is null.
*/
size_t ListCountItems(const List* _list);

/**
 * @brief The function checks if the list is empty.
 *
 * @param[in] _list: Pointer to a list.
 *
 * @return 1 if empty / 0 if not.
 *
 * @warning Will return 0 if _list is null.
*/
int ListIsEmpty(const List* _list);

/**
 * @brief The function perform an action on each individual item in the list. 
 * @param[in] _list: Pointer to a list.
 * @param[in] _action: Pointer to a function of the action to perform.
 * @param[in] _context: Pointer context value for the action.
 * @return The number of times (items) the action was perform on.
 *
 * @warning On NULL pointer to a list or funciton, the return value will be 0.
*/
size_t ListForEach(const List* _list, UserActionFunc _action, void* _context);


typedef void* ListItr;

/** 
 * @brief Get iterator to the list's beginning
 *
 * @params _list : list to return begin iterator, pointing at first element
 *                 or at the end if list is empty
 * @return iterator pointing at the list's beginning
 */
ListItr ListItrBegin(const List* _list);

/** 
 * @brief Get iterator to the list end
 *
 * @params _list : list to return end iterator
 * @return an iterator pointing at the list's end
 */
ListItr ListItrEnd(const List* _list);

/** 
 * @brief retruns none zero if _a and _b iterators refer to same node
 * @warning might be implemented as a macro
 */
int ListItrEquals(const ListItr _a, const ListItr _b);

/** 
 * @brief Get iterator to the next element from a given iterator
 * @warning if _itr is end iterator it will be returned
 */
ListItr ListItrNext(ListItr _itr);

/** 
 * @brief Get iterator to the previous element
 * @warning if _itr is begin iterator it will be returned
 */
ListItr ListItrPrev(ListItr _itr);

/** 
 * @brief Get data from the list node the iterator is pointing to
 *
 * @params _itr : A list iterator
 * @return the data the iterator is pointing at or NULL if pointing to the end
 */
void* ListItrGet(ListItr _itr);

/** 
 * @brief Set data at the node where the iterator is pointing at
 * @return the data from the node to be changed
 */
void* ListItrSet(ListItr _itr, void* _element);

/** 
 * @brief Inserts a new node before node the iterator is pointing at
 * @return an iterator pointing at the element inserted or NULL on error
 */
ListItr ListItrInsertBefore(ListItr _itr, void* _element);

/** 
 * @brief Removes the node the iterator is pointing at
 *
 * @params _itr : A list iterator
 * @return the removed data
 */
void* ListItrRemove(ListItr _itr);


/** 
 * @brief Predicate function returns a none zero value if predicate holds for element
 *
 * @param _element : element to test
 * @param _context : context to be used
 * @return none zero if predicate holds
 */
typedef int (*PredicateFunction)(void * _element, void* _context);

/** 
 * @brief Action function to operate on an element
 *
 * @param _element : element to test
 * @param _context : context to be used
 * @return zero if action fails
 */
typedef int (*ListActionFunction)(void* _element, void* _context);

/** 
 * @brief Action function to check if a < b
 *
 * @param _a : element to test
 * @param _b : element to test against
 * @return none zero if _a < _b
 */
typedef int (*LessFunction)(void* _a, void* _b);

/** 
 * @brief Action function to check if a == b
 *
 * @param _a : element to test
 * @param _b : element to test against
 * @return none zero if _a == _b
 */
typedef int (*EqualsFunction)(void* _a, void* _b);

/** 
 * @brief Finds the first element in a range satsifying a predicate
 * @details find the element for which the predicate reuturns a non zero value
 *  in the half open range [begin..end)
 *
 * @param _begin : start search from here
 * @param _end : end search here - not included
 * @param _predicate : Predicate function
 * @param _context : context to be passed to the predicate
 * @return an iterator pointing to the first node with data found or to _end if not
 */
ListItr ListItrFindFirst(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context);

/** 
 * @brief count elements in a sub list satisfying predicate
 * @details find the element for which the predicate reuturns a non zero value
 *  in the half open range [begin..end)
 *
 * @param _begin : start search from here
 * @param _end : end search here - not included
 * @param _predicate : Predicate function
 * @param _context : context to be passed to the predicate
 * @return count of all elements e where _predicate(e, _context) != 0
 */
size_t ListItrCountIf(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context);

/** 
 * @brief execute an action for all elements in a half open range
 * @details call -action for each element in the range [begin..end)
 * iteration will stop if Action function returns 0 for an element
 *
 * @param _begin: A list iterator to start operations from
 * @param _end : A list iterator to end operations on
 * @param _Action : user provided action function
 * @param _context : Parameters for the function
 * @return ListItr to the element where the iteration stoped. this might be end iterator
 */
ListItr ListItrForEach(ListItr _begin, ListItr _end, ListActionFunction _action, void* _context);


/** 
 * @brief Sorts a sublist in place using the bubble sort algorithm
 * Complexity O(?)
 *
 * @params _begin : Iterator to sublist start
 * @params _end : Iterator to sublist end
 * @params _less : less compare function
 * 
 */
void ListItrSort(ListItr _begin, ListItr _end, LessFunction _less);


/** 
 * @brief Splice all element from [_begin.._end) into _dst
 * @details remove all elements from the half open range [_begin.._end)
 * and insert them before _dest
 * O(?)
 *
 * @warning The function assumes that : 
 *  _begin and _end are in the correct order and on the same list
 *  _dset is not between them
 * Otherwise behavior is undefined
 * all three iterators can belong to same list
 */

ListItr ListItrSplice(ListItr _dest, ListItr _begin, ListItr _end);

/** 
 * @brief Merges two given sub lists into destination 
 * @details Merge elements from two sub lists defined by [_firstbegin.._firstEnd)
 * and [_secondBegin.._secondEnd) in optionaly sorted order using _less function.
 * merged elements will be inserted before _destBegin
 * if a _less function is provided then merge will be sorted
 * 
 * @warning this will removes all merged items from source ranges.
 * O(?)
 *  
 */
ListItr ListItrMerge(ListItr _destBegin, ListItr _firstBegin, ListItr _firstEnd,
			ListItr _secondBegin, ListItr _secondEnd, LessFunction _less);

/** 
 * @brief Removes a sublist [_begin.._end) from a list and creates a new list
 * with all removed items.
 * O(?)
 *
 */
List* ListItrCut(ListItr _begin, ListItr _end);

/** 
 * @brief Removes all duplicate elements from a sorted sublist [_begin.._end) 
 * and rertun a new list with all removed items.
 * O(?)
 * post condition: [_begin.._end) contains only unique elements
 */
List* ListItrUnique(ListItr _begin, ListItr _end, EqualsFunction _equals);



#endif /* #ifndef __GENERIC_DOUBLE_LINKED_LIST_H__ */

