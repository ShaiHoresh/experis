/* Add signature, including description, author and dates 
   of creation and last update
*/

#include <stdlib.h>
#include <stdio.h>

#include "../../inc/DoubleLL.h"

#define MAGIC 0xDEADBEAF

typedef struct Node Node;

struct Node
{
	void*   m_data;
	Node*   m_next;
	Node*   m_prev;
};

struct List
{
	unsigned int m_magic;
	Node    m_head;
	Node    m_tail;
};



#define LIST_FIRST(L) ( (L)->m_head.m_next)
#define LIST_LAST(L)  ( (L)->m_tail.m_prev)
#define LIST_END(L)   (&(L)->m_tail)

#define IS_EMPTY(L)      (LIST_FIRST((L)) == LIST_END((L)))
#define IS_A_LIST(L)     ((L) && (L)->m_magic == MAGIC)


static Node* NodeCreate(void* _data);
static void InsertNode(Node* _prev, Node* _node);
static ListErrors CheckList(const List* _list);
/*static ListErrors CheckData(void** _data);*/
static void RemoveNode(Node* _node);

/*static int IsEmpty(List* _list);*/

/*void ListPrint(List* _list);*/
static int bubble(ListItr _begin, ListItr _end, LessFunction _less);
static void Swap(ListItr _left, ListItr _right);
int _destroyFunc(void* _element, void *_context);
/**********************************************************/
List* ListCreate(void)
{
    List* list;
    list = malloc(sizeof(List));
    if(NULL == list)
    {
        return NULL;
    }
    list->m_head.m_next = &list->m_tail;
    list->m_tail.m_prev = &list->m_head;
    list->m_head.m_prev = NULL;
    list->m_tail.m_next = NULL;
    list->m_magic = MAGIC;
    return list;
}

void ListDestroy(List* *_list, UserActionFunc _destoryFunc)
{
    Node* node;
    if(CheckList(*_list) != LIST_UNINITIALIZED)
    {
        node = (*_list)->m_head.m_next;
        if(node != &(*_list)->m_tail)
        {
           /* ListForEach(*_list, _destroyFunc, NULL);*/
           _destoryFunc(node->m_data, NULL);
           node = node->m_next;
           free(node->m_prev);
        }
        (*_list)->m_magic = 0;
        free(*_list);
        *_list = NULL;
    }
}


ListErrors ListPushHead(List* _list, void* _data)
{
    Node* node;
    if(!IS_A_LIST(_list))
    {
        return LIST_UNINITIALIZED;
    }
    node = NodeCreate(_data);
    if(NULL == node)
    {
        return LIST_ALLOCATION_FAILED;
    }
    InsertNode(_list->m_head.m_next, node);
    return LIST_OK;
}

ListErrors ListPushTail(List* _list, void* _data)
{
    Node* node;
    if(!IS_A_LIST(_list))
    {
        return LIST_UNINITIALIZED;
    }
    node = NodeCreate(_data);
    if(NULL == node)
    {
        return LIST_ALLOCATION_FAILED;
    }
    InsertNode(&_list->m_tail, node);
    return LIST_OK;
}

ListErrors ListPopHead(List* _list, void** _data)
{
    Node temp;
    if(!IS_A_LIST(_list))
    {
        return LIST_UNINITIALIZED;
    }
    if(IS_EMPTY(_list))
    {
        return LIST_IS_EMPTY;
    }
    temp = _list->m_head;
    *_data = _list->m_head.m_next->m_data;
    RemoveNode(_list->m_head.m_next);
    free(temp.m_next);
    return LIST_OK;
}

ListErrors ListPopTail(List* _list, void** _data)
{
    Node temp;
    if(!IS_A_LIST(_list))
    {
        return LIST_UNINITIALIZED;
    }
    if(IS_EMPTY(_list))
    {
        return LIST_IS_EMPTY;
    }
    
    temp = _list->m_tail;
    *_data = _list->m_tail.m_prev->m_data;
    
    RemoveNode(_list->m_tail.m_prev);
    free(temp.m_prev);
    
    return LIST_OK;
}

size_t ListCountItems(const List* _list)
{
    size_t counter = 0;
    Node* node = NULL;
    if(CheckList(_list) == LIST_UNINITIALIZED)
    {
        return 0;
    }
    node = _list->m_head.m_next;
   /* tail = _list->m_tail;*/
    while(node != &_list->m_tail)
    {
        ++counter;
        node = node->m_next;
    }
    return counter;
}

int ListIsEmpty(const List* _list)
{
    if(CheckList(_list) != LIST_UNINITIALIZED)
    {
        return(_list->m_head.m_next == &_list->m_tail);
    }
    return 1;
}

size_t ListForEach(const List* _list, UserActionFunc _action, void* _context)
{
    Node* node = NULL;
    size_t counter = 0;
    
    if(CheckList(_list) != LIST_UNINITIALIZED)
    {
        node = _list->m_head.m_next;
        while(node != &_list->m_tail)
        {
            if(_action(node->m_data, _context) == 1)
            {
                break;
            }
            counter++;
            node = node->m_next;
        }
    }
    return counter;
}

ListErrors FindFirstForward(const List* _list, PredicateFunction _predicateFunc, void* _context, void* *_item)
{
    Node* node = NULL;
    
    if(CheckList(_list) != LIST_UNINITIALIZED)
    {
        node = _list->m_head.m_next;
        while(node != &_list->m_tail)
        {
            if(_predicateFunc(node, _context) == 1)
            {
                _item = (void*)node;
                return LIST_OK;
            }
            node = node->m_next;
        }
        _item = NULL;
    }
    return LIST_ITEM_NOT_FOUND;
}

ListErrors FindFirstBackward(const List* _list, PredicateFunction _predicateFunc, void* _context, void* *_item)
{
    Node* node = NULL;
    
    if(CheckList(_list) != LIST_UNINITIALIZED)
    {
        node = _list->m_tail.m_prev;
        while(node != &_list->m_head)
        {
            if(_predicateFunc(node, _context) == 1)
            {
                _item = (void*)node;
                return LIST_OK;
            }
            node = node->m_prev;
        }
        _item = NULL;
    }
    return LIST_ITEM_NOT_FOUND;
}

ListItr ListItrBegin(const List* _list)
{
    if(!IS_A_LIST(_list))
    {
        return NULL;
    }
    return LIST_FIRST(_list);
}

ListItr ListItrEnd(const List* _list)
{
    if(!IS_A_LIST(_list))
    {
        return NULL;
    }
    return (ListItr)LIST_END(_list);
}

int ListItrEquals(const ListItr _a, const ListItr _b)
{
    return (_a == _b);
}

ListItr ListItrNext(ListItr _itr)
{
    Node* node;
    if(NULL == _itr)
    {
        return NULL;
    }
    node = (Node*)_itr;
    return _itr = (node->m_next == NULL ? _itr : node->m_next);
}

ListItr ListItrPrev(ListItr _itr)
{
    Node* node;
    if(NULL == _itr)
    {
        return NULL;
    }
    node = (Node*)_itr;
    return _itr = (node->m_prev->m_prev == NULL ? _itr : node->m_prev);
}

void* ListItrGet(ListItr _itr)
{
    Node* node;
    node = (Node*)_itr;
    if(NULL == _itr || node->m_next == NULL)
    {
        return NULL;
    }
    return node->m_data;
}

void* ListItrSet(ListItr _itr, void* _element)
{
    void* data;
    Node* node;
    node = (Node*)_itr;
    if(NULL == _itr || node->m_next == NULL)
    {
        return NULL;
    }
    data = node->m_data;
    node->m_data = _element;

    return data;
}

ListItr ListItrInsertBefore(ListItr _itr, void* _element)
{
    Node* node;
    if(NULL == _itr)
    {
        return NULL;
    }
    
    node = NodeCreate(_element);
    if(NULL == node)
    {
        return NULL;
    }
    
    InsertNode(_itr, node);
    return node;
}

void* ListItrRemove(ListItr _itr)
{
    void* data;
    Node* node;
    
    node = (Node*)_itr;    
    data = node->m_data;
    
    RemoveNode(node);
    free(node);
    
    return data;
}

ListItr ListItrForEach(ListItr _begin, ListItr _end, ListActionFunction _action, void* _context)
{
    if(NULL == _action)
    {
        return NULL;
    }

    while(_begin != _end && _begin != NULL)
    {
        _action(ListItrGet(_begin), _context);
        _begin = ListItrNext(_begin);
    }
    return _begin;
}

ListItr ListItrFindFirst(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context)
{
    Node* node = NULL;
    
    if(NULL == _predicate || NULL == _context)
    {
        return NULL;
    }
    
    node = (Node*)_begin;
    while(node != _end && node != NULL)
    {
        if(_predicate(node, _context) != 0)
        {
            break;
        }
        node = node->m_next;
    }
    return node;
}

size_t ListItrCountIf(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context)
{
    Node* node = NULL;
    size_t counter = 0;
    if(NULL == _predicate || NULL == _context)
    {
        return 0;
    }
    
    node = (Node*)_begin;
    while(node != _end && node != NULL)
    {
        if(_predicate(node->m_data, _context) == 0)
        {
            counter++;
        }
        node = node->m_next;
    }
    return counter;
}

void ListItrSort(ListItr _begin, ListItr _end, LessFunction _less)
{
    if(NULL == _begin || NULL == _end || NULL == _less)
    {
        return;
    }
    while(_begin != _end && _begin != NULL)
    {
        if(!bubble(_begin, _end, _less))
        {
            break;
        }
        _end = ListItrPrev(_end);
    }
    return;
}

/**********************************************************/
/******************AUX**FUNCTIONS**************************/
/**********************************************************/

static Node* NodeCreate(void* _data)
{
    Node* node;
    node = malloc(sizeof(Node));
    if(NULL == node)
    {
        return NULL;
    }
    node->m_data = _data;
    node->m_next = NULL;
    node->m_prev = NULL;
    return node;
}

static void InsertNode(Node* _cur, Node* _node)
{
    _cur->m_prev->m_next = _node;
    _node->m_next = _cur;
    _node->m_prev = _cur->m_prev;
    _cur->m_prev = _node;
}

static void RemoveNode(Node* _node)
{
    if(NULL != _node->m_next)
    {
        _node->m_next->m_prev = _node->m_prev;
        _node->m_prev->m_next = _node->m_next;
    }
}
/*
static int IsEmpty(List* _list)
{
    return(_list->m_head.m_next == &_list->m_tail);
}*/

static ListErrors CheckList(const List* _list)
{
    if(NULL == _list || _list->m_magic != MAGIC)
    {
        return LIST_UNINITIALIZED;
    }
    return LIST_OK;
}

static int bubble(ListItr _begin, ListItr _end, LessFunction _less)
{
    int flag = 0;
    ListItr next = NULL;
/*    Node* node*/
    next = ListItrNext(_begin);
    while(/*!ListItrEquals(_begin, _end)*/ next != _end)
    {
        if(_less(ListItrGet(_begin), ListItrGet(next)))
        {
            Swap(_begin, next);
            flag = 1;
        }
        _begin = next;
        next = ListItrNext(_begin);
    }
    return flag;
}

static void Swap(ListItr _left, ListItr _right)
{
    void* temp;
    
    temp = ListItrGet(_left);
    temp = ListItrSet(_right, temp);
    ListItrSet(_left, temp);
    
    return;
}









