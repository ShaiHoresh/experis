#include <stdlib.h>
#include <stdio.h>

#include "doubleLL.h"

#define MAGIC 987645321

struct Node
{
	int     m_data;
	Node*   m_next;
	Node*   m_prev;
};

struct List
{
	Node    m_head;
	Node    m_tail;
};

static Node* NodeCreate(int _data);
static void InsertNode(Node* _prev, Node* _node);
static ADTErr CheckList(List* _list);
static ADTErr CheckData(int* _data);
static void RemoveNode(Node* _node);

static int IsEmpty(List* _list);

void ListPrint(List* _list);

/**********************************************************/
List* ListCreate()
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
    list->m_head.m_data = MAGIC;
    return list;
}

void ListDestroy(List* _list)
{
    Node* node;
    if(CheckList(_list) != ERR_NOT_INITIALIZED)
    {
        node = _list->m_head.m_next;
        while(node != &_list->m_tail)
        {
            free(node);
            node = node->m_next;
        }
        _list->m_head.m_data = 0;
        free(_list);
    }
}


ADTErr ListPushHead(List* _list, int _data)
{
    Node* node;
    if(CheckList(_list) == ERR_NOT_INITIALIZED)
    {
        return ERR_NOT_INITIALIZED;
    }
    node = NodeCreate(_data);
    if(NULL == node)
    {
        return ERR_ALLOCATION_FAILED;
    }
    InsertNode(&_list->m_head, node);
    return ERR_OK;
}

ADTErr ListPushTail(List* _list,int _data)
{
    Node* node;
    if(CheckList(_list) == ERR_NOT_INITIALIZED)
    {
        return ERR_NOT_INITIALIZED;
    }
    node = NodeCreate(_data);
    if(NULL == node)
    {
        return ERR_ALLOCATION_FAILED;
    }
    InsertNode(_list->m_tail.m_prev, node);
    return ERR_OK;
}

ADTErr ListPopHead(List* _list, int* _data)
{
    Node temp;
    if(CheckList(_list) == ERR_NOT_INITIALIZED || CheckData(_data) == ERR_NOT_INITIALIZED)
    {
        return ERR_NOT_INITIALIZED;
    }
    if(IsEmpty(_list))
    {
        return ERR_UNDERFLOW;
    }
    temp = _list->m_head;
    *_data = _list->m_head.m_next->m_data;
    RemoveNode(_list->m_head.m_next);
    free(temp.m_next);
    return ERR_OK;
}

ADTErr ListPopTail(List* _list, int* _data)
{
    Node temp;
    if(CheckList(_list) == ERR_NOT_INITIALIZED || CheckData(_data) == ERR_NOT_INITIALIZED)
    {
        return ERR_NOT_INITIALIZED;
    }
    if(IsEmpty(_list))
    {
        return ERR_UNDERFLOW;
    }
    temp = _list->m_tail;
    *_data = _list->m_tail.m_prev->m_data;
    RemoveNode(_list->m_tail.m_prev);
    free(temp.m_prev);
    return ERR_OK;
}

size_t ListCountItems(List* _list)
{
    size_t counter = 0;
    Node* node;
    if(CheckList(_list) == ERR_NOT_INITIALIZED)
    {
        return 0;
    }
    node = &_list->m_head;
    while(node->m_next != &_list->m_tail)
    {
        ++counter;
        node = node->m_next;
    }
    return counter;
}

int ListIsEmpty(List* _list)
{
    if(CheckList(_list) != ERR_NOT_INITIALIZED)
    {
        return(_list->m_head.m_next == &_list->m_tail);
    }
    return 1;
}

void ListPrint(List* _list)
{
    Node* node;
    
    if(CheckList(_list) != ERR_NOT_INITIALIZED)
    {
        node = &_list->m_head;
        while(node->m_next != &_list->m_tail)
        {
            node = node->m_next;
            printf("%d  ", node->m_data);
        }
        printf("\n");
    }
}

static Node* NodeCreate(int _data)
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

static void InsertNode(Node* _prev, Node* _node)
{
    _node->m_next = _prev->m_next;
    _node->m_prev = _prev;
    _prev->m_next->m_prev = _node;
    _prev->m_next = _node;
}

static void RemoveNode(Node* _node)
{
    _node->m_next->m_prev = _node->m_prev;
    _node->m_prev->m_next = _node->m_next;
}

static int IsEmpty(List* _list)
{
    return(_list->m_head.m_next == &_list->m_tail);
}

static ADTErr CheckList(List* _list)
{
    if(NULL == _list || _list->m_head.m_data != MAGIC)
    {
        return ERR_NOT_INITIALIZED;
    }
    return ERR_OK;
}

static ADTErr CheckData(int* _data)
{
    if(NULL == _data)
    {
        return ERR_NOT_INITIALIZED;
    }
    return ERR_OK;
}













