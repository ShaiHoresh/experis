#ifndef __DOUBLELL_H__
#define __DOUBLELL_H__

#include "ADTDefs.h"

typedef struct Node Node;
typedef struct List List;

List* ListCreate();
void ListDestroy(List* _list);

ADTErr ListPushHead(List* _list,int _data);
ADTErr ListPushTail(List* _list,int _data);
ADTErr ListPopHead(List* _list,int* _data);
ADTErr ListPopTail(List* _list,int* _data);
size_t ListCountItems(List* _list);
int ListIsEmpty(List* _list);

void ListPrint(List* _list);

#endif /* #ifndef __DOUBLELL_H__ */
