/*                  list iterator functions.
                    implemented by Shai horesh.
                    creation date: 7/8/2017 
*/

#include "list_itr.h"
#include "GenericDoubleLinkedList.h"
/*#include <> */
/*
typedef struct Node Node;

struct Node
{
	void*   m_data;
	Node*   m_next;
	Node*   m_prev;
};

struct List
{
	Node    m_head;
	Node    m_tail;
	unsigned int m_magic;
};*/

#define MAGIC 0xDEADBEAF

#define LIST_FIRST(L) ( (L)->m_head.m_next)
#define LIST_LAST(L)  ( (L)->m_tail.m_prev)
#define LIST_END(L)   (&(L)->m_tail)

#define IS_EMPTY(L)      (LIST_FIRST((L)) == LIST_END((L)))
#define IS_A_LIST(L)     ((L) && (L)->m_magic == MAGIC)

/*declarations*/

ListItr ListItr_Begin(const List* _list)
{
    if(!IS_A_LIST(_list))
    {
        return NULL;
    }
    return LIST_FIRST(_list);
}

ListItr ListItr_End(const List* _list)
{
    if(!IS_A_LIST(_list))
    {
        return NULL;
    }
    return LIST_END(_list);
}

int ListItr_Equals(const ListItr _a, const ListItr _b)
{
    return (_a == _b)
}

ListItr ListItr_Next(ListItr _itr)
{
    if(_NULL == _itr)
    {
        return NULL;
    }
    return _itr = ((Node)*_itr->m_next == NULL ? _itr : (Node)*_itr->m_next);
}

ListItr ListItr_Prev(ListItr _itr)
{
    if(_NULL == _itr)
    {
        return NULL;
    }
    return _itr = ((Node)*_itr->m_prev->m_prev == NULL ? _itr : (Node)*_itr->m_prev);
}

void* ListItr_Get(ListItr _itr)
{
    if(_NULL == _itr || (Node)*_itr->m_next == NULL)
    {
        return NULL;
    }
    return (Node)*_itr->m_data;
}

void* ListItr_Set(ListItr _itr, void* _element)
{
    void* data;
    if(_NULL == _itr || (Node)*_itr->m_next == NULL)
    {
        return NULL;
    }
    
    data = (Node)*_itr->m_data;
    (Node)*_itr->m_data = _element;

    return data;
}

ListItr ListItr_InsertBefore(ListItr _itr, void* _element)
{
    Node* node;
    if(_NULL == _itr || _element == NULL)
    {
        return NULL;
    }
    
    node = NodeCreate(_element);
    if(NULL == node)
    {
        return LIST_ALLOCATION_FAILED;
    }
    
    InsertNode(&_itr, node);
    return &node;       /*(void*)*/
}

void* ListItr_Remove(ListItr _itr)
{
    void* data;
    data = (Node)*_itr->m_data;
    
    RemoveNode((Node)*_itr);
    free((Node)*_itr);
    
    return data;
}










