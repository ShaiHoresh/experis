#include <stdio.h>
#include <stdlib.h>
#include "List.h"

#define SIZE 10

/******** DEFINING SRTUCT ONLY FOR ISSORT AUX FUNCTION************/
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
/******** DEFINING SRTUCT ONLY FOR ISSORT AUX FUNCTION************/

void PrintInt(int* _data, void* _context)
{
	printf(" %d ", *_data);
	return;
}

void PrintStr(char* _data, void* _context)
{
	printf(" %c ", (char)(*_data));
	return;
}

void destroyInt(int* _data, void* _context)
{
	free(_data);
	return;
}

void destroyStr(char* _data, void* _context)
{
	free(_data);
	return;
}

int IsFour(int* _data, void* _context)
{
	if(*_data == 4)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int IsA(int* _data, void* _context)
{
	if(*_data == 'a')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int IsFourteen(int* _data, void* _context)
{
	if(*_data == 14)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
/********************************/
void TestCreate()
{
	List* ls = ListCreate();
	if(NULL != ls)
	{
		printf("\npass- create\n");
	}
	else
	{
		printf("\nfail-create\n");
	}
	ListDestroy(&ls, (UserActionFunc)destroyInt);
	return;
}

void TestPushHead()
{
	ListErrors check;
	int empty = 0;
	int* data;
	List* ls = ListCreate();
	data = malloc(sizeof(int));
	*data = 1;
	check = ListPushHead(ls , data);
	empty = ListIsEmpty(ls);
	if(LIST_OK == check && 0 == empty)
	{
		printf("\npass- push head\n");
	}
	else
	{
		printf("\nfail- push head\n");
	}
	ListDestroy(&ls, (UserActionFunc)destroyInt);
	return;	
}

void TestPushHeadAfterPopHead()
{
	ListErrors check;
	int empty = 0;
	int* data1;
	int* data2;
	int* item;
	List* ls = ListCreate();
	data1 = malloc(sizeof(int));
	data2 = malloc(sizeof(int));
	*data1 = 1;
	*data2 = 2;
	ListPushHead(ls , data1);
	ListPopHead(ls, (void**)&item);
	check = ListPushHead(ls , data2);
	empty = ListIsEmpty(ls);
	if(LIST_OK == check && 0 == empty)
	{
		printf("\npass- push head after pop head\n");
	}
	else
	{
		printf("\nfail- push head after pop head\n");
	}
	free(item);
	ListDestroy(&ls, (UserActionFunc)destroyInt);
	return;	
}

void TestPushHeadNullList()
{
	ListErrors check = 0;
	int num;
	check = ListPushHead(NULL, &num);
	if(LIST_UNINITIALIZED == check )
	{
		printf("\npass- push head to null list\n");
	}
	else
	{
		printf("\nfail- push head to null list\n");
	}
	return;	
}

void TestPushTailNullList()
{
	ListErrors check = 0;
	int num;
	check = ListPushTail(NULL , &num);
	if(LIST_UNINITIALIZED == check )
	{
		printf("\npass- push tail to null list\n");
	}
	else
	{
		printf("\nfail- push tail to null list\n");
	}
	return;	
}
void TestPushTail()
{
	ListErrors check;
	int empty = 0;
	int* data;
	List* ls = ListCreate();
	data = malloc(sizeof(int));
	*data = 1;
	check = ListPushTail(ls , data);
	empty = ListIsEmpty(ls);
	if(LIST_OK == check && 0 == empty)
	{
		printf("\npass- push tail\n");
	}
	else
	{
		printf("\nfail- push tail\n");
	}
	ListDestroy(&ls, (UserActionFunc)destroyInt);
	return;	
}

void TestPushTailAfterPopTail()
{
	ListErrors check;
	int empty = 0;
	int* data1;
	int* data2;
	int* item;
	List* ls = ListCreate();
	data1 = malloc(sizeof(int));
	data2 = malloc(sizeof(int));
	*data1 = 1;
	*data2 = 2;
	ListPushTail(ls , data1);
	ListPopTail(ls, (void**)&item);
	check = ListPushTail(ls , data2);
	empty = ListIsEmpty(ls);
	if(LIST_OK == check && 0 == empty)
	{
		printf("\npass- push tail after pop tail\n");
	}
	else
	{
		printf("\nfail- push tail after pop tail\n");
	}
	free(item);
	ListDestroy(&ls, (UserActionFunc)destroyInt);
	return;
}

void TestpopTailAfterPushHead()
{
	ListErrors check;
	int empty = 0;
	int* data1;
	int* data2;
	int* item;
	List* ls = ListCreate();
	data1 = malloc(sizeof(int));
	data2 = malloc(sizeof(int));
	*data1 = 1;
	*data2 = 2;
	ListPushHead(ls , data1);
	ListPushHead(ls , data2);
	check = ListPopTail(ls, (void**)&item);
	empty = ListIsEmpty(ls);
	if(LIST_OK == check && 0 == empty && 1 == *item)
	{
		printf("\npass- pop tail after push head\n");
	}
	else
	{
		printf("\nfail- pop tail after push head\n");
	}
	free(item);
	ListDestroy(&ls, (UserActionFunc)destroyInt);
	return;	
}

void TestPopHeadWhenEmpty()
{
	ListErrors check;
	int empty = 0;
	int* item;
	List* ls = ListCreate();
	check = ListPopHead(ls, (void**)&item);
	empty = ListIsEmpty(ls);
	if(LIST_IS_EMPTY == check && 1 == empty)
	{
		printf("\npass- pop head when empty\n");
	}
	else
	{
		printf("\nfail- pop head when empty\n");
	}
	free(item);
	ListDestroy(&ls, (UserActionFunc)destroyInt);
	return;
}	
	
void TestPopTailWhenEmpty()
{
	ListErrors check;
	int empty = 0;
	int* item;
	List* ls = ListCreate();
	check = ListPopTail(ls, (void**)&item);
	empty = ListIsEmpty(ls);
	if(LIST_IS_EMPTY == check && 1 == empty)
	{
		printf("\npass- pop tail when empty\n");
	}
	else
	{
		printf("\nfail- pop tail when empty\n");
	}
	free(item);
	ListDestroy(&ls, (UserActionFunc)destroyInt);
	return;	
}

void TestPopHead()
{
	ListErrors check;
	int empty = 0;
	int* data1;
	int* data2;
	int* item;
	List* ls = ListCreate();
	data1 = malloc(sizeof(int));
	data2 = malloc(sizeof(int));
	*data1 = 1;
	*data2 = 2;
	ListPushHead(ls , data1);
	ListPushHead(ls , data2);
	check = ListPopHead(ls, (void**)&item);
	empty = ListIsEmpty(ls);
	if(LIST_OK == check && 0 == empty && *item == 2)
	{
		printf("\npass- pop head\n");
	}
	else
	{
		printf("\nfail- pop head\n");
	}
	free(item);
	ListDestroy(&ls, (UserActionFunc)destroyInt);
	return;	
}

void TestpopHeadAfterPushTail()
{
	ListErrors check;
	int empty = 0;
	int* data1;
	int* data2;
	int* item;
	List* ls = ListCreate();
	data1 = malloc(sizeof(int));
	data2 = malloc(sizeof(int));
	*data1 = 1;
	*data2 = 2;
	ListPushTail(ls , data1);
	ListPushTail(ls , data2);
	check = ListPopHead(ls, (void**)&item);
	empty = ListIsEmpty(ls);
	if(LIST_OK == check && 0 == empty && 1 == *item)
	{
		printf("\npass- pop head after push tail\n");
	}
	else
	{
		printf("\nfail- pop head after push tail\n");
	}
	free(item);
	ListDestroy(&ls, (UserActionFunc)destroyInt);
	return;		
}

void TestPopTail()
{
	ListErrors check;
	int empty = 0;
	int* data1;
	int* data2;
	int* item;
	List* ls = ListCreate();
	data1 = malloc(sizeof(int));
	data2 = malloc(sizeof(int));
	*data1 = 1;
	*data2 = 2;
	ListPushTail(ls , data1);
	ListPushTail(ls , data2);
	check = ListPopTail(ls, (void**)&item);
	empty = ListIsEmpty(ls);
	if(LIST_OK == check && 0 == empty && *item == 2)
	{
		printf("\npass- pop tail\n");
	}
	else
	{
		printf("\nfail- pop tail\n");
	}
	free(item);
	ListDestroy(&ls, (UserActionFunc)destroyInt);
	return;		
}

void TestCountItemWithItem()
{
	ListErrors check;
	int* data1;
	int* data2;
	List* ls = ListCreate();
	data1 = malloc(sizeof(int));
	data2 = malloc(sizeof(int));
	*data1 = 1;
	*data2 = 2;
	ListPushTail(ls , data1);
	ListPushTail(ls , data2);
	check = ListCountItems(ls);
	if(2 == check)
	{
		printf("\npass- count item with item\n");
	}
	else
	{
		printf("\nfail- count item with item\n");
	}
	ListDestroy(&ls, (UserActionFunc)destroyInt);
	return;	
}

void TestCountItemWithoutItem()
{
	List* ls = ListCreate();
	size_t check = 0;	
	check = ListCountItems(ls);
	if(0 == check)
	{
		printf("\npass- count item without item\n");
	}
	else
	{
		printf("\nfail- count item without item\n");
	}
	ListDestroy(&ls, (UserActionFunc)destroyInt);
	return;	
}



void TestIsEmptyWithItem()
{
	int check;
	int* data1;
	int* data2;
	List* ls = ListCreate();
	data1 = malloc(sizeof(int));
	data2 = malloc(sizeof(int));
	*data1 = 1;
	*data2 = 2;
	ListPushTail(ls , data1);
	ListPushTail(ls , data2);
	check = ListIsEmpty(ls);
	if(0 == check)
	{
		printf("\npass- is empty with item\n");
	}
	else
	{
		printf("\nfail- is empty with item\n");
	}
	ListDestroy(&ls, (UserActionFunc)destroyInt);
	return;	
}

void TestIsEmptyWithoutItem()
{
	List* ls = ListCreate();
	int check = 0;	
	check = ListIsEmpty(ls);
	if(1 == check)
	{
		printf("\npass- is empty when empty\n");
	}
	else
	{
		printf("\nfail- is empty when empty\n");
	}
	ListDestroy(&ls, (UserActionFunc)destroyInt);
	return;	
}

void FindFirstBackwardWhenFound()
{
	int i;
	int* arr[100];
	int* item ;
	ListErrors check;
	List* ls = ListCreate();
	for(i = 0; i < 100; ++i)
	{
		arr[i] = malloc(sizeof(int));
		*arr[i] = i;
		ListPushHead(ls, arr[i]);
	}
	check = FindFirstBackward(ls, (PredicateFunc)IsFour, NULL, (void**)&item);	
	if(LIST_OK == check && *item == 4)
	{
		printf("\npass- FindFirstBackwardWhenFound\n");
	}
	else
	{
		printf("\nfail- FindFirstBackwardWhenFound\n");
	}
	/*ListForEach(ls, (UserActionFunc) PrintInt, NULL);			*/
	ListDestroy(&ls, (UserActionFunc)destroyInt);
	return;	
}

void FindFirstBackwardWhenNotFound()
{
	int i;
	int* arr[10];
	int* item ;
	ListErrors check;
	List* ls = ListCreate();
	for(i = 0; i < 10; ++i)
	{
		arr[i] = malloc(sizeof(int));
		*arr[i] = i;
		ListPushHead(ls, arr[i]);
	}
	check = FindFirstBackward(ls, (PredicateFunc)IsFourteen, NULL, (void**)&item);	
	if(LIST_ITEM_NOT_FOUND == check && item == NULL)
	{
		printf("\npass- FindFirstBackwardWhenNotFound\n");
	}
	else
	{
		printf("\nfail- FindFirstBackwardWhenNotFound\n");
	}		
	ListDestroy(&ls, (UserActionFunc)destroyInt);
	return;	
}

void FindFirstForwardWhenFound()
{
	int i;
	int* arr[10];
	int* item ;
	ListErrors check;
	List* ls = ListCreate();
	for(i = 0; i < 10; ++i)
	{
		arr[i] = malloc(sizeof(int));
		*arr[i] = i;
		ListPushHead(ls, arr[i]);
	}
	check = FindFirstForward(ls, (PredicateFunc)IsFour, NULL, (void**)&item);	
	if(LIST_OK == check && *item == 4)
	{
		printf("\npass- FindFirstForwardWhenFound\n");
	}
	else
	{
		printf("\nfail- FindFirstForwardWhenFound\n");
	}		
	ListDestroy(&ls, (UserActionFunc)destroyInt);
	return;	
}

void FindFirstForwardWhenNotFound()
{
	int i;
	int* arr[10];
	int* item ;
	ListErrors check;
	List* ls = ListCreate();
	for(i = 0; i < 10; ++i)
	{
		arr[i] = malloc(sizeof(int));
		*arr[i] = i;
		ListPushHead(ls, arr[i]);
	}
	check = FindFirstForward(ls, (PredicateFunc)IsFourteen, NULL, (void**)&item);	
	if(LIST_ITEM_NOT_FOUND == check && item == NULL)
	{
		printf("\npass- FindFirstBackwardWhenNotFound\n");
	}
	else
	{
		printf("\nfail- FindFirstBackwardWhenNotFound\n");
	}		
	ListDestroy(&ls, (UserActionFunc)destroyInt);
	return;	
}
void PrinInt()
{
	int i;
	int* arr[10];
	List* ls = ListCreate();
	for(i = 0; i < 10; ++i)
	{
		arr[i] = malloc(sizeof(int));
		*arr[i] = i;
		ListPushHead(ls, arr[i]);
	}
	printf("\n\n");
	ListForEach(ls, (UserActionFunc) PrintInt, NULL);	
	ListDestroy(&ls, (UserActionFunc)destroyInt);
	printf("\n\n");
	return;	
}

void CharAllTest()
{
	char* a = malloc(sizeof(char));
	char* b = malloc(sizeof(char));
	char* c = malloc(sizeof(char));
	char* d = malloc(sizeof(char));
	char* e = malloc(sizeof(char));
	char* f = malloc(sizeof(char));
	char* g = malloc(sizeof(char));
	char* h = malloc(sizeof(char));
	char* i = malloc(sizeof(char));
	char* j = malloc(sizeof(char));
	char* k = malloc(sizeof(char));
	char* l = malloc(sizeof(char));
	char* m = malloc(sizeof(char));
	char* n = malloc(sizeof(char));
	char* o = malloc(sizeof(char));
	char* p = malloc(sizeof(char));
	char* item1;
	char* item2;
	char* item3;
	char* item4;	
	size_t count;
	int empty;
	ListErrors check1;
	ListErrors check2;
	List* ls = ListCreate();
	*a = 'a';
	*b = 'b';
	*c = 'c';
	*d = 'd';
	*e = 'e';
	*f = 'f';
	*g = 'g';
	*h = 'h';
	*i = 'i';
	*j = 'j';
	*k = 'k';
	*l = 'l';
	*m = 'm';
	*n = 'n';
	*o = 'o';
	*p = 'p';
			
	ListPushHead(ls, a);
	ListPushHead(ls, b);
	ListPushHead(ls, c);
	ListPushHead(ls, d);
	ListPushTail(ls, e);
	ListPushTail(ls, f);
	ListPushTail(ls, g);
	ListPushTail(ls, h);
	ListPushHead(ls, i);
	ListPushHead(ls, j);
	ListPushHead(ls, k);
	ListPushHead(ls, l);
	ListPushTail(ls, m);
	ListPushTail(ls, n);
	ListPushTail(ls, o);
	ListPushTail(ls, p);
	
	ListPopTail(ls, (void**)&item1);
	if(*item1 != 'p')
	{
		printf("\nfail - char pop tail\n");
	}	
	free(item1);
	ListPopHead(ls, (void**)&item2);
	if(*item2 != 'l')
	{
		printf("\nfail - char pop head\n");
	}
	free(item2);
	count =  ListCountItems(ls);
	if(count != 14)
	{
		printf("\nfail - char count item\n");
	}
	empty = ListIsEmpty(ls);	
	if(empty != 0)
	{
		printf("\nfail - char is empty\n");
	}
	check1 = FindFirstBackward(ls, (PredicateFunc)IsA, NULL, (void**)&item3);
	if(check1 == LIST_OK && *item3 == 'a')
	{
		printf("\nfail - char FindFirstBackward\n");
	}	
	
	check2 = FindFirstForward(ls, (PredicateFunc)IsA, NULL, (void**)&item4);
	if(check2 == LIST_OK && *item4 == 'a')
	{
		printf("\nfail - char FindFirstForward\n");
	}	
	printf("\npass - char all test\n");		
	printf("\n\n");
	ListForEach(ls, (UserActionFunc) PrintStr, NULL);	
	ListDestroy(&ls, (UserActionFunc)destroyStr);
	printf("\n\n");
	return;	
}


/*************************************************/



void ItrBeginNullTest()
{
	ListItr start;
	start = ListItrBegin(NULL);
	if(NULL == start)
	{
		printf("\npass - itr begin null list\n");
	}
	else
	{
		printf("\nfail - itr begin null list\n");		
	}
	return;
}

void ItrBeginTest()
{
	int i;
	ListItr start;
	int* arr[10];
	List* ls = ListCreate();
	for(i = 0; i < 10; ++i)
	{
		arr[i] = malloc(sizeof(int));
		if(NULL == arr[i])
		{
		printf("                malloc failed in %d", i);
		return;
		}
		*arr[i] = i;
		ListPushHead(ls, arr[i]);
	}
	start = ListItrBegin(ls);
	if(NULL != start)
	{
		printf("\npass - itr begin\n");
	}
	else
	{
		printf("\nfail - itr begin\n");		
	}
	ListDestroy(&ls, (UserActionFunc)destroyInt);
	return;
}

void ItrEndNullTest()
{
	ListItr end;
	end = ListItrEnd(NULL);
	if(NULL == end)
	{
		printf("\npass - itr end null list\n");
	}
	else
	{
		printf("\nfail - itr end null list\n");		
	}
	return;
}

void ItrEndTest()
{
	int i;
	ListItr end;
	int* arr[10];
	List* ls = ListCreate();
	for(i = 0; i < 10; ++i)
	{
		arr[i] = malloc(sizeof(int));
		if(NULL == arr[i])
		{
		printf("                   malloc failed in %d", i);
		return;
		}
		*arr[i] = i;
		ListPushHead(ls, arr[i]);
	}
	end = ListItrEnd(ls);
	if(NULL != end)
	{
		printf("\npass - itr end\n");
	}
	else
	{
		printf("\nfail - itr end\n");		
	}
	ListDestroy(&ls, (UserActionFunc)destroyInt);
	return;
}

void itrEqualWhanNot()
{
	int i;
	int res;
	ListItr end;
	ListItr start;
	int* arr[10];
	List* ls = ListCreate();
	for(i = 0; i < 10; ++i)
	{
		arr[i] = malloc(sizeof(int));
		if(NULL == arr[i])
		{
		printf("                       malloc failed in %d", i);
		return;
		}
		*arr[i] = i;
		ListPushHead(ls, arr[i]);
	}
	end = ListItrEnd(ls);
	start = ListItrBegin(ls);	
	res = ListItrEquals(start, end);
	if(0 == res)
	{
		printf("\npass - itr Equal Whan Not\n");
	}
	else
	{
		printf("\nfail - itr Equal Whan Not\n");		
	}
	ListDestroy(&ls, (UserActionFunc)destroyInt);
	return;	
}

void itrEqualWhanDo()
{
	int res;
	ListItr end;
	ListItr start;
	List* ls = ListCreate();
	end = ListItrEnd(ls);
	start = ListItrBegin(ls);	
	res = ListItrEquals(start, end);
	if(1 == res)
	{
		printf("\npass - itr Equal Whan do\n");
	}
	else
	{
		printf("\nfail - itr Equal Whan do\n");		
	}
	ListDestroy(&ls, (UserActionFunc)destroyInt);
	return;	
}

void itrNextTest()
{
	int i;
	int res1;
	int res2;
	int res3;
	ListItr end;
	ListItr start;
	ListItr notequal;
	ListItr equal;
	int* arr[2];
	List* ls = ListCreate();
	for(i = 0; i < 2; ++i)
	{
		arr[i] = malloc(sizeof(int));
		if(NULL == arr[i])
		{
		printf("                 malloc failed in %d", i);
		return;
		}
		*arr[i] = i;
		ListPushHead(ls, arr[i]);
	}
	end = ListItrEnd(ls);
	start = ListItrBegin(ls);	
	res1 = ListItrEquals(start, end);
	notequal = ListItrNext(start);
	res2 = ListItrEquals(notequal, end);
	equal = ListItrNext(notequal);	
	res3 = ListItrEquals(equal, end);		
	if(0 == res1 && 0 == res2 && 1 == res3)
	{
		printf("\npass - itr next\n");
	}
	else
	{
		printf("\nfail - itr next\n");		
	}
	ListDestroy(&ls, (UserActionFunc)destroyInt);
	return;	
}

void itrNextTailTest()
{
	int i;
	ListItr end;
	ListItr res;
	int* arr[2];
	List* ls = ListCreate();
	for(i = 0; i < 2; ++i)
	{
		arr[i] = malloc(sizeof(int));
		if(NULL == arr[i])
		{
		printf("                   malloc failed in %d", i);
		return;
		}
		*arr[i] = i;
		ListPushHead(ls, arr[i]);
	}
	end = ListItrEnd(ls);
	res = ListItrNext(end);
	if(end == res)
	{
		printf("\npass - itr next to tail\n");
	}
	else
	{
		printf("\nfail - itr next to tail\n");		
	}
	ListDestroy(&ls, (UserActionFunc)destroyInt);
	return;	
}

void itrPrevTest()
{
	int i;
	int res1;
	int res2;
	int res3;
	ListItr end;
	ListItr start;
	ListItr notequal;
	ListItr equal;
	int* arr[2];
	List* ls = ListCreate();
	for(i = 0; i < 2; ++i)
	{
		arr[i] = malloc(sizeof(int));
		if(NULL == arr[i])
		{
		printf("                  malloc failed in %d", i);
		return;
		}
		*arr[i] = i;
		ListPushHead(ls, arr[i]);
	}
	end = ListItrEnd(ls);
	start = ListItrBegin(ls);	
	res1 = ListItrEquals(start, end);
	notequal = ListItrPrev(end);
	res2 = ListItrEquals(notequal, start);
	equal = ListItrPrev(notequal);	
	res3 = ListItrEquals(equal, start);		
	if(0 == res1 && 0 == res2 && 1 == res3)
	{
		printf("\npass - itr prev\n");
	}
	else
	{
		printf("\nfail - itr prev\n");		
	}
	ListDestroy(&ls, (UserActionFunc)destroyInt);
	return;	
}

void itrPrevHeadTest()
{
	int i;
	ListItr start;
	ListItr res;
	int* arr[2];
	List* ls = ListCreate();
	for(i = 0; i < 2; ++i)
	{
		arr[i] = malloc(sizeof(int));
		if(NULL == arr[i])
		{
		printf("                     malloc failed in %d", i);
		return;
		}
		*arr[i] = i;
		ListPushHead(ls, arr[i]);
	}
	start = ListItrBegin(ls);
	res = ListItrPrev(start);
	if(start == res)
	{
		printf("\npass - itr prev to head\n");
	}
	else
	{
		printf("\nfail - itr prev to head\n");		
	}
	ListDestroy(&ls, (UserActionFunc)destroyInt);
	return;	
}

void itrGet()
{
	int i;
	int* res1;
	int* res2;
	int* res3;
	int* res4;
	ListItr end;
	ListItr start;
	int* arr[10];
	List* ls = ListCreate();
	for(i = 0; i < 10; ++i)
	{
		arr[i] = malloc(sizeof(int));
		if(NULL == arr[i])
		{
		printf("                    malloc failed in %d", i);
		return;
		}
		*arr[i] = i;
		ListPushHead(ls, arr[i]);
	}
	end = ListItrEnd(ls);
	start = ListItrBegin(ls);	
	start = ListItrNext(start);
	end = ListItrPrev(end);
	res1 = (int*)ListItrGet(start);
	res2 = (int*)ListItrGet(end);
	
	start = ListItrNext(start);
	end = ListItrPrev(end);
	res3 = (int*)ListItrGet(start);
	res4 = (int*)ListItrGet(end);	
	
	if(8 == *res1 && 0 == *res2 && 7 == *res3 && 1 == *res4)
	{
		printf("\npass - itr get\n");
	}
	else
	{
		printf("\nfail - itr get\n");		
	}
	ListDestroy(&ls, (UserActionFunc)destroyInt);
	return;	
}

void itrSet()
{
	int i;
	int* res[4];

	ListItr end;
	ListItr start;
	
	List* ls = ListCreate();

	int* arr[10];
	int* in1 = malloc(sizeof(int));
	int* in2 = malloc(sizeof(int));
	*in1 = 71070;
	*in2 = 69;
	
	for(i = 0; i < 10; ++i)
	{
		arr[i] = malloc(sizeof(int));
		if(NULL == arr[i])
		{
			printf("\t\tmalloc failed in %d", i);
			return;
		}
		*arr[i] = i;
		ListPushHead(ls, arr[i]);
	}
		
	end = ListItrEnd(ls);
	start = ListItrBegin(ls);	

	end = ListItrPrev(end);
	res[0] = (int*)ListItrSet(start, (void*)in1);
	res[1] = (int*)ListItrSet(end, (void*)in2);
			
	res[2] = (int*)ListItrGet(start);
	res[3] = (int*)ListItrGet(end);
	
	if(9 == *res[0] && 0 == *res[1] && 71070 == *res[2] && 69 == *res[3])
	{
		printf("\npass - itr set\n");
	}
	else
	{
		printf("\nfail - itr set\n");		
	}
	free(res[0]);
	free(res[1]);	

	ListDestroy(&ls, (UserActionFunc)destroyInt);
	return;	
}

void itrInsertBeforeNullitr()
{

	ListItr res;

	res = ListItrInsertBefore(NULL, NULL);
	if(NULL == res)
	{
		printf("\npass - itr Insert Before null itr\n");
	}
	else
	{
		printf("\nfail - itr Insert Before null itr\n");		
	}	
	return;	
}

void itrInsertBefore()
{
	int i;
	int* res1;
	int* res2;
	ListItr end;
	ListItr start;
	int* arr[10];
	int* in1;
	int* in2;
	List* ls = NULL;
	
	in1 = (int*)malloc(sizeof(int));
	in2 = (int*)malloc(sizeof(int));
	*in1 = 71070;
	*in2 = 69;
	ls = ListCreate();
	
	
	
	for(i = 0; i < 10; ++i)
	{
		arr[i] = (int*)malloc(sizeof(int));
		if(NULL == arr[i])
		{
		printf("                    malloc failed in %d", i);
		return;
		}		
		*(arr[i]) = i;
		ListPushTail(ls, arr[i]);
	}
	
	end = ListItrEnd(ls);
	start = ListItrBegin(ls);	
	start = ListItrNext(start);
	start = ListItrInsertBefore(start, (void*)in1);
	end = ListItrInsertBefore(end, (void*)in2);
			
	res1 = (int*)ListItrGet(start);
	res2 = (int*)ListItrGet(end);
	
	if(71070 == *res1 && 69 == *res2)
	{
		printf("\npass - itr Insert Before\n");
	}
	else
	{
		printf("\nfail - itr Insert Before\n");		
	}	
	ListDestroy(&ls, (UserActionFunc)destroyInt);
	return;	
}

void itrremoveTest()
{
	int i;
	int* res1;
	int* res2;
	int* res3;
	int* res4;
	ListItr end;
	ListItr start;
	List* ls = ListCreate();
	int* arr[10];

	for(i = 0; i < 9 ; ++i)
	{
		arr[i] = malloc(sizeof(int));
		if(NULL == arr[i])
		{
		printf("                      malloc failed in %d", i);
		return;
		}
		*arr[i] = i;
		ListPushTail(ls, arr[i]);
	}
	end = ListItrEnd(ls);
	end = ListItrPrev(end);
	start = ListItrBegin(ls);
		start = ListItrNext(start);	
	res1 = (int*)ListItrRemove(start);
	res2 = (int*)ListItrRemove(end);
	
	end = ListItrEnd(ls);
	end = ListItrPrev(end);
	start = ListItrBegin(ls);	
				
	res3 = (int*)ListItrGet(start);
	res4 = (int*)ListItrGet(end);
	
	if(1 == *res1 && 8 == *res2 && 0 == *res3 && 7 == *res4)
	{
		printf("\npass - itr remove\n");
	}
	else
	{
		printf("\nfail - itr remove\n");		
	}	
	ListDestroy(&ls, (UserActionFunc)destroyInt);
	return;	
}


void itrremoveNullitrTest()
{
	
	ListItr res;
	
	res = (int*)ListItrRemove(NULL);
	
	if(NULL == res)
	{
		printf("\npass - itr remove null itr\n");
	}
	else
	{
		printf("\nfail - itr removenull itr\n");		
	}	
	return;	
}


void itrremoveTailTest()
{
	int i;
	ListItr res;
	ListItr end;
	List* ls = ListCreate();
	int* arr[10];

	for(i = 0; i < 10; ++i)
	{
		arr[i] = malloc(sizeof(int));
		if(NULL == arr[i])
		{
		printf("                           malloc failed in %d", i);
		return;
		}
		*arr[i] = i;
		ListPushTail(ls, arr[i]);
	}
	end = ListItrEnd(ls);
	res = (int*)ListItrRemove(end);

	if(NULL == res)
	{
		printf("\npass - itr remove tail\n");
	}
	else
	{
		printf("\nfail - itr remove tail\n");		
	}	
	ListDestroy(&ls, (UserActionFunc)destroyInt);
	return;	
}
/************************************************************************/
/**********************  ADVENCED  ITRATOR ******************************/
/************************************************************************/

 
int IsDividedBy (void * _element, void* _context)
{
	if(0 == (*(int*)_element)%(*(int*)_context))
	{
		return 1;
	}
	return 0;
}


int multipyBy (void * _element, void* _context)
{
	*(int*)_element = (*(int*)_element) * (*(int*)_context);
	return 0;
}

int LessFunc (void* _a, void* _b)
{
	if(NULL == _a || NULL == _b || *(int*)_a < *(int*)_b)
	{
		return 0;
	}
	return 1; 
}

int IsEqual(int* _a, int* _b)
{

	if(NULL == _a || NULL == _b || *_a != *_b)
	{
		return 0;
	}
	return 1;
}

/***********************************/
static int IsSorted(List* _ls)
{
	int first;
	int sec;
	Node* temp = (_ls->m_head.m_next);
	while(temp->m_next != &(_ls->m_tail))
	{
		first = *(int*)ListItrGet((ListItr)temp);
		sec = *(int*)ListItrGet((ListItr)(temp->m_next));
		if(first > sec)
		{
			return 0;
		}	
		temp = temp->m_next;
	}
	return 1;
}
/***********************************/

static List* ListMaking()
{
	int i;
	int* arr[SIZE];
	List* ls = ListCreate();
	for(i = 0; i < 10; ++i)
	{
		arr[i] = malloc(sizeof(int));
		if(NULL == arr[i])
		{
		printf("                   malloc failed in %d", i);
		return NULL;
		}
		*arr[i] = i;
		ListPushHead(ls, arr[i]);
	}	
	return ls;
}

static List* ListRandMaking()
{
	int i;
	int* arr[SIZE];
	List* ls = ListCreate();
	for(i = 0; i < 10; ++i)
	{
		arr[i] = malloc(sizeof(int));
		if(NULL == arr[i])
		{
		printf("                   malloc failed in %d", i);
		return NULL;
		}
		*arr[i] = rand()% 200 + 1;
		ListPushHead(ls, arr[i]);
	}	
	return ls;
}

static List* ListSecRandMaking()
{
	int i;
	int* arr[SIZE];
	List* ls = ListCreate();
	srand(2);
	for(i = 0; i < 10; ++i)
	{
		arr[i] = malloc(sizeof(int));
		if(NULL == arr[i])
		{
		printf("                   malloc failed in %d", i);
		return NULL;
		}
		*arr[i] = rand()% 200 + 1;
		ListPushHead(ls, arr[i]);
	}	
	return ls;
}

static List* dooubleMaking()
{
	int i;
	int* arr[SIZE*2];
	List* ls = ListCreate();
	for(i = 0; i < 10; ++i)
	{
		arr[i] = malloc(sizeof(int));
		if(NULL == arr[i])
		{
		printf("                   malloc failed in %d", i);
		return NULL;
		}
		*arr[i] = i;
		ListPushHead(ls, arr[i]);
	}
	for(i = 0; i < 10; ++i)
	{
		arr[i] = malloc(sizeof(int));
		if(NULL == arr[i])
		{
		printf("                   malloc failed in %d", i);
		return NULL;
		}
		*arr[i] = i;
		ListPushHead(ls, arr[i]);
	}	
	return ls;
}

/***************************************************************/
void ListItrFindFirstWhenFound()
{	
	int isfive;
	ListItr begin;
	ListItr end;
	ListItr res;
	int five = 5;
	
	List* ls = ListMaking();	
	end = ListItrEnd(ls);
	begin = ListItrBegin(ls);
	res = ListItrFindFirst (begin, end, (PredicateFunction)IsDividedBy,  &five);
	isfive = *(int*)ListItrGet(res);		
	
	if(5 == isfive)
	{
		printf("\npass - List Itr Find First when found\n");
	}
	else
	{
		printf("\nfail - List Itr Find First when found\n");		
	}
	ListDestroy(&ls, (UserActionFunc)destroyInt);
	return;
}	
	
	

void ListItrFindFirstWhenNotFound()
{	
	int iseleven;
	ListItr begin;
	ListItr end;
	ListItr res;
	int eleven = 11;
	List* ls = ListMaking();	
	
	end = ListItrEnd(ls);
	begin = ListItrBegin(ls);
	res = ListItrFindFirst (begin, end, (PredicateFunction)IsDividedBy,  &eleven);
	iseleven = *(int*)ListItrGet(res);		
	
	if(0 == iseleven)
	{
		printf("\npass - List Itr Find First when not found\n");
	}
	else
	{
		printf("\nfail - List Itr Find Firstwhen not found\n");		
	}
	ListDestroy(&ls, (UserActionFunc)destroyInt);
	return;
}		
	
void ListItrCountIfTest()
{	
	ListItr begin;
	ListItr end;
	size_t res;
	int four = 4;
	List* ls = ListMaking();	

	end = ListItrEnd(ls);
	begin = ListItrBegin(ls);
	res = ListItrCountIf (begin, end, (PredicateFunction)IsDividedBy, (void*)&four);
	
	if(3 == res)
	{
		printf("\npass - List Itr Count If\n");
	}
	else
	{
		printf("\nfail - List Itr Count If\n");		
	}
	ListDestroy(&ls, (UserActionFunc)destroyInt);
	return;
}		

void ListForEachTest()
{
	ListItr begin;
	ListItr end;
	ListItr itrres;
	int res;
	int four = 4;
	List* ls = ListMaking();	

	end = ListItrEnd(ls);
	begin = ListItrBegin(ls);
/*	ListItrForEach (begin, end, (UserActionFunc)PrintInt, NULL);
	printf("\n\n");	
*/	itrres = ListItrForEach (begin, end, (UserActionFunc)multipyBy, (void*)&four);
/*	ListItrForEach (begin, end, (UserActionFunc)PrintInt, NULL);
*/	res = *(int*)ListItrGet(itrres);	
	
	if(0 == res)
	{
		printf("\npass - List Itr for each\n");
	}
	else
	{
		printf("\nfail - List Itr for each\n");		
	}
	ListDestroy(&ls, (UserActionFunc)destroyInt);
	return;
}



void ListItrSortTest()
{
	ListItr begin;
	ListItr end;
	int res;
	List* ls = ListRandMaking();	

	end = ListItrEnd(ls);
	begin = ListItrBegin(ls);
/*	ListItrForEach (begin, end, (UserActionFunc)PrintInt, NULL);
*/	ListItrSort (begin, end, (LessFunction)LessFunc);
/*	printf("\n\n");
	ListItrForEach (begin, end, (UserActionFunc)PrintInt, NULL);
*/	res = IsSorted(ls);
	
	if(1 == res)
	{
		printf("\npass - List sort\n");
	}
	else
	{
		printf("\nfail - List sort\n");		
	}
	ListDestroy(&ls, (UserActionFunc)destroyInt);
	return;
}

void ListItrSpliceTest()
{
	ListItr sortedlsbegin;
	ListItr sortedlsend;
	ListItr unsortedlsend;
	List* sortedls;
	List* unsortedls;
	size_t firstAmount;
	size_t secAmount;
	
	sortedls = ListMaking();	
	unsortedls = ListRandMaking();	

	sortedlsend = ListItrEnd(sortedls);
	sortedlsbegin = ListItrBegin(sortedls);
	
	sortedlsbegin = ListItrNext(sortedlsbegin);
	sortedlsbegin = ListItrNext(sortedlsbegin);
	sortedlsend = ListItrPrev(sortedlsend);
	sortedlsend = ListItrPrev(sortedlsend);
				
	unsortedlsend = ListItrEnd(unsortedls);
	unsortedlsend = ListItrPrev(unsortedlsend);
	unsortedlsend = ListItrPrev(unsortedlsend);
	unsortedlsend = ListItrPrev(unsortedlsend);		

/*	printf("\n\n");		
	ListItrForEach (ListItrBegin(unsortedls), ListItrEnd(unsortedls), (UserActionFunc)PrintInt, NULL);
	printf("\n\n");		
	ListItrForEach (ListItrBegin(sortedls), ListItrEnd(sortedls), (UserActionFunc)PrintInt, NULL);
*/	
	ListItrSplice(unsortedlsend, sortedlsbegin, sortedlsend);
		
/*	printf("\n\n");		
	ListItrForEach (ListItrBegin(sortedls), ListItrEnd(sortedls), (UserActionFunc)PrintInt, NULL);	
	printf("\n\n");		
	ListItrForEach (ListItrBegin(unsortedls), ListItrEnd(unsortedls), (UserActionFunc)PrintInt, NULL);
*/
	firstAmount = ListCountItems(sortedls);	
	secAmount = ListCountItems(unsortedls);
	if(4 == firstAmount && 16 == secAmount)
	{
		printf("\npass - List splice\n");
	}
	else
	{
		printf("\nfail - List splice\n");		
	}
	ListDestroy(&unsortedls, (UserActionFunc)destroyInt);
	ListDestroy(&sortedls, (UserActionFunc)destroyInt);
	return;			
}


void ListItrMergeWhenSorted()
{
	ListItr oneB;
	ListItr oneE;
	ListItr secB;
	ListItr secE;
	ListItr destE;
	List* oneLs;
	List* secLs;
	List* destanation;
	int res;
	size_t amount;
		
	oneLs = ListRandMaking();	
	secLs = ListSecRandMaking();
	destanation = ListCreate();
	
	oneB = ListItrBegin(oneLs);
	oneE = ListItrEnd(oneLs);
	
	secB = ListItrBegin(secLs);
	secE = ListItrEnd(secLs);	
	
	destE = ListItrEnd(destanation);	
	
	ListItrSort (oneB, oneE, (LessFunction)LessFunc);
	ListItrSort (secB, secE, (LessFunction)LessFunc);
/*	printf("\n\n");
	ListItrForEach (ListItrBegin(oneLs), ListItrEnd(oneLs), (UserActionFunc)PrintInt, NULL);
	printf("\n\n");
	ListItrForEach (ListItrBegin(secLs), ListItrEnd(secLs), (UserActionFunc)PrintInt, NULL);
	printf("\n\n");	
*/	ListItrMerge(destE, oneB, oneE, secB, secE, (LessFunction)LessFunc);
/*	ListItrForEach (ListItrBegin(destanation), ListItrEnd(destanation), (UserActionFunc)PrintInt, NULL);
*/  res = IsSorted(destanation);
	amount = ListCountItems(destanation);
	if(20 == amount && 1 == res)
	{
		printf("\npass - List sorted merge\n");
	}
	else
	{
		printf("\nfail - List sorted merge\n");		
	}
	
	ListDestroy(&destanation, (UserActionFunc)destroyInt);
	ListDestroy(&oneLs, (UserActionFunc)destroyInt);
	ListDestroy(&secLs, (UserActionFunc)destroyInt);
	return;		
}

void ListItrMergeNotSorted()
{
	ListItr oneB;
	ListItr oneE;
	ListItr secB;
	ListItr secE;
	ListItr destE;
	List* oneLs;
	List* secLs;
	List* destanation;
	int res;
	size_t amount;
		
	oneLs = ListRandMaking();	
	secLs = ListSecRandMaking();
	destanation = ListCreate();
	
	oneB = ListItrBegin(oneLs);
	oneE = ListItrEnd(oneLs);
	
	secB = ListItrBegin(secLs);
	secE = ListItrEnd(secLs);	
	
	destE = ListItrEnd(destanation);	
	
/*	printf("\n\n");
	ListItrForEach (ListItrBegin(oneLs), ListItrEnd(oneLs), (UserActionFunc)PrintInt, NULL);
	printf("\n\n");
	ListItrForEach (ListItrBegin(secLs), ListItrEnd(secLs), (UserActionFunc)PrintInt, NULL);
	printf("\n\n");	
*/	
	ListItrMerge(destE, oneB, oneE, secB, secE, NULL);
/*	ListItrForEach (ListItrBegin(destanation), ListItrEnd(destanation), (UserActionFunc)PrintInt, NULL);
*/    
    
    res = IsSorted(destanation);
	amount = ListCountItems(destanation);
	if(20 == amount && 0 == res)
	{
		printf("\npass - List not sorted merge\n");
	}
	else
	{
		printf("\nfail - List not sorted merge\n");		
	}
	
	ListDestroy(&destanation, (UserActionFunc)destroyInt);
	ListDestroy(&secLs, (UserActionFunc)destroyInt);
	ListDestroy(&oneLs, (UserActionFunc)destroyInt);
	return;		
}


void ListItrCutTest()
{
	ListItr begin;
	ListItr end;
	List* ls;
	List* res;
	size_t resAmount;
	size_t firstAmount;
	
	ls = ListRandMaking();	
	end = ListItrEnd(ls);
	begin = ListItrBegin(ls);
	
	begin = ListItrNext(begin);
	begin = ListItrNext(begin);
	end = ListItrPrev(end);
	end = ListItrPrev(end);

/*	printf("\n\n");		
	ListItrForEach (ListItrBegin(ls), ListItrEnd(ls), (UserActionFunc)PrintInt, NULL);
*/
	res = ListItrCut(begin, end);
	
/*	printf("\n\n");		
	ListItrForEach (ListItrBegin(ls), ListItrEnd(ls), (UserActionFunc)PrintInt, NULL);
	
	printf("\n\n");		
	ListItrForEach (ListItrBegin(res), ListItrEnd(res), (UserActionFunc)PrintInt, NULL);
*/
	firstAmount = ListCountItems(ls);	
	resAmount = ListCountItems(res);
	if(4 == firstAmount && 6 == resAmount)
	{
		printf("\npass - List cut\n");
	}
	else
	{
		printf("\nfail - List cut\n");		
	}
	ListDestroy(&ls, (UserActionFunc)destroyInt);
	ListDestroy(&res, (UserActionFunc)destroyInt);
	return;
}



void ListItrUniqueTest()
{
	ListItr begin;
	ListItr end;
	List* ls;
	List* res;
	size_t resAmount;
	size_t firstAmount;
	
	ls = dooubleMaking();	
	end = ListItrEnd(ls);
	begin = ListItrBegin(ls);
	ListItrSort (begin, end, (LessFunction)LessFunc);
	
/*	printf("\n\n");		
	ListItrForEach (ListItrBegin(ls), ListItrEnd(ls), (UserActionFunc)PrintInt, NULL);
*/
	res = ListItrUnique(begin, end, (EqualsFunction)IsEqual);
	
/*	printf("\n\n");		
	ListItrForEach (ListItrBegin(ls), ListItrEnd(ls), (UserActionFunc)PrintInt, NULL);	
	printf("\n\n");		
	ListItrForEach (ListItrBegin(res), ListItrEnd(res), (UserActionFunc)PrintInt, NULL);
*/
	firstAmount = ListCountItems(ls);	
	resAmount = ListCountItems(res);
	if(10 == firstAmount && 10 == resAmount)
	{
		printf("\npass - List unique\n");
	}
	else
	{
		printf("\nfail - List unique\n");		
	}
	ListDestroy(&ls, (UserActionFunc)destroyInt);
	ListDestroy(&res, (UserActionFunc)destroyInt);
	return;	
}


int main()
{

	printf("\n\n	LIST TEST	\n\n");
	TestCreate();
	TestPushHead();
	TestPushTail();
	TestPopHeadWhenEmpty();
	TestPopTailWhenEmpty();	
	TestPopHead();
	TestPopTail();
	TestPushHeadAfterPopHead();
	TestPushHeadNullList();
	TestPushTailNullList();
	TestPushTailAfterPopTail();
	TestpopTailAfterPushHead();
	TestpopHeadAfterPushTail();
	TestCountItemWithItem();
	TestCountItemWithoutItem();
	TestIsEmptyWithItem();
	TestIsEmptyWithoutItem();
	FindFirstBackwardWhenFound();
	FindFirstBackwardWhenNotFound();
	FindFirstForwardWhenFound();
	FindFirstForwardWhenNotFound();
	PrinInt();
	CharAllTest();
	printf("\n\n	ITRATOR TEST	\n\n");	
	
	ItrBeginTest();
	ItrBeginNullTest();
	ItrEndNullTest();
	ItrEndTest();
	itrEqualWhanNot();
	itrEqualWhanDo();
	itrNextTest();
	itrNextTailTest();
	itrPrevTest();
	itrPrevHeadTest();
	itrGet();
	itrSet();
	itrInsertBeforeNullitr();	
	itrInsertBefore();
	itrremoveTailTest();
	itrremoveTest();
	itrremoveNullitrTest();
	
	printf("\n\n	ADVENCED ITRATOR TEST	\n\n");	
	ListItrFindFirstWhenFound();
	ListItrFindFirstWhenNotFound();
	ListItrCountIfTest();
	ListForEachTest();
	ListItrSortTest();
	ListItrSpliceTest();
	ListItrMergeWhenSorted();
	ListItrMergeNotSorted();
	ListItrCutTest();
	ListItrUniqueTest();
	
	printf("\n\n");	
	
	return 0;
}








