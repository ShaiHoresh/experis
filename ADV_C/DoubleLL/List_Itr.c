#include<stdlib.h>
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



ListItr ListItrBegin(const List* _list)
{
	List* temp;
	if(NULL == _list || magic_num != _list->m_mgc_num)
	{
		return NULL;
	}
	temp = (List*)_list;
	return (ListItr*)(temp->m_head.m_next);
}



ListItr ListItrEnd(const List* _list)
{
	List* temp;
	if(NULL == _list || magic_num != _list->m_mgc_num)
	{
		return NULL;
	}
	temp = (List*)_list;	
	return (ListItr*)&(temp->m_tail);
}


int ListItrEquals(const ListItr _a, const ListItr _b)
{

	if(NULL == _a || NULL == _b || _a != _b)
	{
		return 0;
	}
	return 1;
}

ListItr ListItrNext(ListItr _itr)
{
	Node* nod = (Node*)_itr;
	if(NULL == _itr)
	{
		return NULL;
	}
	if(NULL == nod->m_next)
	{
		return _itr;
	}
	return (ListItr*)(nod->m_next);
}


ListItr ListItrPrev(ListItr _itr)
{
	Node* nod = (Node*)_itr;
	if(NULL == _itr)
	{
		return NULL;
	}
	if(NULL == nod->m_prev || NULL == (nod->m_prev)->m_prev)
	{
		return _itr;
	}
	return ((ListItr*)(nod->m_prev));
}

void* ListItrGet(ListItr _itr)
{
	Node* nod = (Node*)_itr;
	if(NULL == _itr || NULL == nod->m_prev || NULL == nod->m_next)
	{
		return NULL;
	}
	return (void*)(nod->m_data);
}


void* ListItrSet(ListItr _itr, void* _element)
{
	Node* nod = (Node*)_itr;
	Node* temp;
	if(NULL == _itr || NULL == nod->m_prev || NULL == nod->m_next)
	{
		return NULL;
	}
	temp = nod->m_data;
	nod->m_data = _element;
	return temp;
}

ListItr ListItrInsertBefore(ListItr _itr, void* _element)
{
	Node* nod = (Node*)_itr;
	Node* temp = malloc(sizeof(Node));
	if(NULL == _itr || NULL == nod->m_prev || NULL == temp)
	{
		return NULL;
	}		
	temp->m_data = _element;
	temp->m_prev = nod->m_prev;
	temp->m_next = nod;
	(nod->m_prev)->m_next = temp; 
	nod->m_prev = temp;
	
	return (void*)temp;
}


void* ListItrRemove(ListItr _itr)
{
	Node* nod = (Node*)_itr;
	void* data;
	if(NULL == _itr || NULL == nod->m_prev || NULL == nod->m_next)
	{
		return NULL;
	}	
	data = nod->m_data;
	(nod->m_prev)->m_next = nod->m_next; 
	(nod->m_next)->m_prev = nod->m_prev;	
	free(_itr);
	return data;
}



































