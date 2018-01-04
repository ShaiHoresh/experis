#include<stdlib.h>
#include<stdio.h>
#include "List.h"


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

/*******************************/


ListItr ListItrFindFirst (ListItr _begin, ListItr _end, PredicateFunc _predicate, void* _context)
{
	Node* start;
	Node* finish;
	
	if(NULL == _begin || NULL == _end || NULL == _predicate)
	{
		return NULL;
	}
	
	start = (Node*)_begin;
	finish = (Node*)_end;
	
	while(start != finish && NULL != start->m_next)
	{
		if(_predicate((void*)(start->m_data), _context))
		{
			return ((void*)start);
		}
		start = start->m_next;
	}
	return _end;
}


size_t ListItrCountIf (ListItr _begin, ListItr _end, PredicateFunc _predicate, void* _context)
{
	Node* start;
	Node* finish;
	size_t counter = 0;
	
	if(NULL == _begin || NULL == _end || NULL == _predicate)
	{
		return 0;
	}
	
	start = (Node*)_begin;
	finish = (Node*)_end;
	
	while(start != finish && NULL != start->m_next)
	{
		if(_predicate((void*)(start->m_data), _context))
		{
			++counter;
		}
		start = start->m_next;
	}
	return counter;
}


ListItr ListItrForEach (ListItr _begin, ListItr _end, UserActionFunc _action, void* _context)
{
	Node* start;
	Node* finish;
	
	if(NULL == _begin || NULL == _end || NULL == _action)
	{
		return NULL;
	}
	
	start = (Node*)_begin;
	finish = (Node*)_end;
	
	while(start != finish && NULL != start->m_next)
	{
		if(_action((void*)(start->m_data), _context))
		{
			return ((void*)start);
		}
		start = start->m_next;
	}
	return (ListItr)((Node*)_end)->m_prev;	
}


/****************************/

static void itrSwap (ListItr _first, ListItr _sec)
{
	void* temp;
	temp = ListItrGet(_first);
	ListItrSet(_first, ListItrGet(_sec));
	ListItrSet(_sec, temp);
}

static int Bubble (ListItr _start, ListItr _end, LessFunction _less)
{			
	int sweped = 1;
	void* firstData = ListItrGet(_start);
	void* sectData = ListItrGet(ListItrNext(_start));
	
	while(((Node*)_start)->m_next != _end)
	{
		if(_less(firstData, sectData))
		{
			itrSwap(_start, (ListItr)((Node*)_start)->m_next);
			sweped = 0;
			_start = ListItrNext(_start);
			sectData = ListItrGet(ListItrNext(_start));
			continue;
		}
		firstData = sectData; 
		_start = ListItrNext(_start);
		sectData = ListItrGet(ListItrNext(_start)); 
	}
	return sweped;	
}


void ListItrSort (ListItr _begin, ListItr _end, LessFunction _less)
{
	ListItr finish;
	ListItr tempfinish;
	if(NULL == _begin || NULL == _end || NULL == _less)
	{
		return;	
	}
	
	finish = _end;
	tempfinish = _end;
	
	while(!Bubble(_begin, tempfinish, _less))
	{
		finish = ListItrPrev(finish);
		tempfinish = finish;
	}
	return;
}
/****************************/

static ListItr Soldring (ListItr _begin, ListItr _end)
{
	ListItr temp = ((Node*)_end)->m_prev;		
	((Node*)_end)->m_prev = ((Node*)_begin)->m_prev;      
	((Node*)_begin)->m_prev->m_next = (Node*)_end;
	return temp; 
}

static ListItr attaching (ListItr _dest, ListItr _begin, ListItr _end)
{
	ListItr temp = ((Node*)_dest)->m_prev;
	((Node*)_end)->m_next = (Node*)_dest;
	((Node*)_dest)->m_prev = (Node*)_end;
	((Node*)temp)->m_next = (Node*)_begin;
	((Node*)_begin)->m_prev =(Node*)temp;
	return _dest; 
}
/*
*/


ListItr ListItrSplice (ListItr _dest, ListItr _begin, ListItr _end)
{
	ListItr temp;
	if(NULL == _dest || NULL == _begin || NULL == _end)
	{
		return NULL;	
	}
	
	temp = Soldring(_begin, _end);
    return attaching(_dest, _begin, temp);
}

/***********************************************************/


static void UnSortMerging(ListItr _destBegin, ListItr _firstBegin, ListItr _firstEnd, ListItr _secondBegin, ListItr _secondEnd)
{	
	ListItrSplice (_firstBegin, _secondBegin, _secondEnd);
	ListItrSplice (_destBegin, _secondBegin, _firstEnd);
	return;
}

static void SortedMerging(ListItr _destBegin,ListItr _firstBegin, ListItr _firstEnd, ListItr _secondBegin, ListItr _secondEnd, LessFunction _less)
{
	ListItr tempitr;
	
	while(_firstBegin != _firstEnd && _secondBegin != _secondEnd)
	{
		if(!_less(ListItrGet(_firstBegin), ListItrGet(_secondBegin)))
		{	
			tempitr = ListItrNext(_firstBegin);	
			ListItrSplice (_destBegin, _firstBegin, ListItrNext(_firstBegin));
			_firstBegin = tempitr;
		}
		else
		{
			tempitr = ListItrNext(_secondBegin);
			ListItrSplice (_destBegin, _secondBegin, ListItrNext(_secondBegin));
			_secondBegin = tempitr;				
		}
	}
	if(_firstBegin == _firstEnd)
	{
		ListItrSplice (_destBegin, _secondBegin, _secondEnd);
	}
	else
	{
		ListItrSplice (_destBegin, _firstBegin, _firstEnd);
	}
	
	return;
}


ListItr ListItrMerge(ListItr _destBegin, ListItr _firstBegin, ListItr _firstEnd, ListItr _secondBegin, ListItr _secondEnd, LessFunction _less)
{
		
	if(NULL == _destBegin || NULL == _firstBegin || NULL == _firstEnd || NULL == _secondBegin || NULL == _secondEnd)
	{
		return NULL;	
	}
	
	if(NULL == _less)
	{
		UnSortMerging(_destBegin, _firstBegin, _firstEnd, _secondBegin, _secondEnd);
	}
	else
	{	
		SortedMerging(_destBegin, _firstBegin, _firstEnd, _secondBegin, _secondEnd, _less);
	}
	return _destBegin;
}

/***********************************************************/

List* ListItrCut(ListItr _begin, ListItr _end)
{
	List* ls;
	
	if(NULL == _begin || NULL == _end)
	{
		return NULL;	
	}
	
	ls = ListCreate();
	ListItrSplice (ListItrEnd(ls), _begin, _end);
	return ls;
}

/****************************************************************/

List* ListItrUnique(ListItr _begin, ListItr _end, EqualsFunction _equals)
{
	
	List* ls;
	ListItr temp;
	if(NULL == _begin || NULL == _end || NULL == _equals)
	{
		return NULL;	
	}
	
	ls = ListCreate();		
	while(_begin != _end)
	{
		if(_equals(ListItrGet(_begin), ListItrGet(((Node*)_begin)->m_next)))
		{
			temp = ListItrNext(_begin);
			ListItrSplice (ListItrEnd(ls), _begin, ListItrNext(_begin));
			_begin = temp;
			continue;
		}
		_begin = ListItrNext(_begin);
	}
	return ls;
}









