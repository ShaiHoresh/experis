#include <stdio.h>
#include <stdlib.h>
#include "List.h"

static const int magic_num = 71070;

typedef struct Node Node;



struct Node
{
	void* 	m_data;
	Node* m_next;
	Node* m_prev;
};

struct List
{
	int m_mgc_num;
	Node m_head;
	Node m_tail;	
};


List* ListCreate(void)
{
	List* ls = (List*) malloc(sizeof(List));
	if(NULL == ls)
	{
		return NULL;
	}
	ls->m_mgc_num = magic_num;
	ls->m_head.m_next = &(ls->m_tail);
	ls->m_head.m_prev = NULL;
	ls->m_tail.m_prev = &(ls->m_head);
	ls->m_tail.m_next = NULL;	
	return ls;
}
/*****************************************************************/
static void pushHeadLinking(Node* _new, Node* _head)
{
	_new->m_next = (_head->m_next);
	_new->m_prev = _head;
	_head->m_next = _new;
	_new->m_next->m_prev = _new;
}

ListErrors ListPushHead(List* _list, void* _data)
{
	Node* new;
	
	if(NULL == _list || _list->m_mgc_num != magic_num)
	{
		return LIST_UNINITIALIZED;
	}
	
	new = (Node*) malloc(sizeof(Node));
	if(NULL == new)
	{
	 printf("\t\t\tdebug print");
		return LIST_ALLOCATION_FAILED;
	}	
	
	new->m_data = _data;
	pushHeadLinking(new, &_list->m_head);	
	return LIST_OK;
}

/*******************************************************/
static void pushTailLinking(Node* _new, Node* _tail)
{
	_new->m_prev = _tail->m_prev;
	_new->m_next = _tail;
	_tail->m_prev->m_next = _new;
	_tail->m_prev = _new;
}

ListErrors ListPushTail(List* _list, void* _data)
{
	Node* new;
	if(NULL == _list || _list->m_mgc_num != magic_num)
	{
		return LIST_UNINITIALIZED;
	}
	new = (Node*) malloc(sizeof(Node));
	if(NULL == new)
	{
		return LIST_ALLOCATION_FAILED;
	}	
	new->m_data = _data;
	pushTailLinking(new, &_list->m_tail);
	return LIST_OK;
}

/**************************************************************/

ListErrors ListPopHead(List* _list, void* *_data)
{
	if(NULL == _list || _list->m_mgc_num != magic_num)
	{
		return LIST_UNINITIALIZED;
	}	
	if(_list->m_head.m_next == &(_list->m_tail))
	{
		return LIST_IS_EMPTY;
	}
	*_data = _list->m_head.m_next->m_data;
	_list->m_head.m_next = _list->m_head.m_next->m_next;
	free(_list->m_head.m_next->m_prev);
	_list->m_head.m_next->m_prev = &_list->m_head;
	return LIST_OK;
}


ListErrors ListPopTail(List* _list, void* *_data)
{
	if(NULL == _list || _list->m_mgc_num != magic_num)
	{
		return LIST_UNINITIALIZED;
	}	
	if(_list->m_tail.m_prev == &(_list->m_head))
	{
		return LIST_IS_EMPTY;
	}
	*_data = _list->m_tail.m_prev->m_data;
	_list->m_tail.m_prev = _list->m_tail.m_prev->m_prev;
	free(_list->m_tail.m_prev->m_next);
	_list->m_tail.m_prev->m_next = &_list->m_tail;
	return LIST_OK;	
}


size_t ListCountItems(const List* _list)
{
	size_t counter = 0;
	Node* temp;
	if(NULL == _list || _list->m_mgc_num != magic_num)
	{
		return 0;
	}
	temp = &(((List*)_list)->m_head);
	while(1)
	{
		if(temp->m_next == &_list->m_tail)
		{
			break;
		}
		temp = temp->m_next;
		++counter;
	}
	return counter;
}


int  ListIsEmpty(const List* _list)
{
	if((NULL == _list) || _list->m_mgc_num != magic_num || (_list->m_head.m_next == &_list->m_tail))
	{
		return 1;
	}
	return 0;
}



void ListDestroy(List** _list, UserActionFunc _destoryFunc)
{
	Node* temp;
	
	if((NULL == *_list) || (*_list)->m_mgc_num != magic_num || (*_list)->m_head.m_next == &((*_list)->m_tail))
	{
		return;
	}

	if(NULL != _destoryFunc)
	{
		temp = ((*_list)->m_head.m_next);	
		while(temp != &((*_list)->m_tail))
		{
			_destoryFunc(temp->m_data, NULL);
			temp = temp->m_next;
			free(temp->m_prev);
		}
	}

	(*_list)->m_mgc_num = 0;
	free(*_list);
	*_list = NULL;
	return;
}


ListErrors FindFirstBackward(const List* _list, PredicateFunc _predicateFunc, void* _context, void* *_item)
{
	Node* temp = NULL;
	if(NULL == _list || _list->m_mgc_num != magic_num  || NULL == _predicateFunc)
	{
		return LIST_UNINITIALIZED;
	}
	temp = ((_list->m_tail).m_prev);
	while(temp != &(((List*)_list)->m_head))
	{
		if(_predicateFunc(temp->m_data, _context))
		{
			*_item = temp->m_data;
			return LIST_OK;
		}
		temp = temp->m_prev;
	}
	*_item =	NULL;
	return LIST_ITEM_NOT_FOUND;
}



ListErrors FindFirstForward(const List* _list, PredicateFunc _predicateFunc, void* _context, void* *_item)
{
	Node* temp = NULL;
	if(NULL == _list || _list->m_mgc_num != magic_num || NULL == _predicateFunc)
	{
		return LIST_UNINITIALIZED;
	}
	temp = ((((List*)_list)->m_head).m_next);
	while(temp != &(_list->m_tail))
	{
		if(_predicateFunc(temp->m_data, _context))
		{
			*_item = temp->m_data;
			return LIST_OK;
		}
		temp = temp->m_next;
	}
	*_item =	NULL;
	return LIST_ITEM_NOT_FOUND;
}


size_t ListForEach(const List* _list, UserActionFunc _action, void* _context)
{
	Node* temp = NULL;
	if(NULL == _list || _list->m_mgc_num != magic_num || NULL == _action)
	{
		return LIST_UNINITIALIZED;
	}
	temp = ((((List*)_list)->m_head).m_next);
	while(temp != &(_list->m_tail))
	{
		_action(temp->m_data, _context);
		temp = temp->m_next;
	}
	return LIST_OK;
}

/*************************************************************/




























