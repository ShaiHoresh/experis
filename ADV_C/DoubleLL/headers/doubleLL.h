#ifndef __DOUBLELL_H__
#define __DOUBLELL_H__

/** 
 * @brief Create a Generic Double Linked List data type
 * that stores pointer to user provided elements of generic type
 * The Double Linked List is dynamically allocated and can grow and shrink on demand.
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 

#include "ADTDefs.h"

typedef struct List List;

/**  
 * @brief Dynamically create a new list object
 * @param[in] none
 * @return List * - on success / NULL on fail 
 */
List* ListCreate();

/**  
 * @brief Dynamically deallocate a previously allocated list  
 * @param[in] _list - List to be deallocated.
 * @param[in] _elementDestroy : A function pointer to be used to destroy all elements in the list
 *             or a null if no such destroy is required
 * @return void
 */
void ListDestroy(List** _list, void (*_elementDestroy)(void* _item));

ADTErr ListPushHead(List* _list,void* _data);

ADTErr ListPushTail(List* _list,void* _data);

ADTErr ListPopHead(List* _list,void** _data);

ADTErr ListPopTail(List* _list,void** _data);

size_t ListCountItems(List* _list);

int ListIsEmpty(List* _list);

size_t ListForEach(List* _list);

#endif /* #ifndef __DOUBLELL_H__ */
