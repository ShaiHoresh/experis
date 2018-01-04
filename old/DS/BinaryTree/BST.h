#ifndef __BST_H__
#define __BST_H__

#include "ADTDefs.h"
typedef struct Tree Tree;

/* TreeTraverse - options to print the Binary Search Tree */
typedef enum
{
    PRE_ORDER,
    IN_ORDER,
    POST_ORDER
} TreeTraverse;

/*  DESC:   The funcion TreeCreate creates a tree...
    INPUT:  gets nothing as input.
    OUTPUT: a pointer to a new tree                 
    ERRORS: returns NULL if allocation failed       */
Tree* TreeCreate();

/*  DESC:   The funcion TreeDestroy destroys tree and all its nodes.
    INPUT:  gets a pointer to a tree as input.
    OUTPUT: none 
    ERRORS: none                                    */
void TreeDestroy(Tree* _tree);

/*  DESC:   The funcion TreeInsert inserts new data to the tree.
    INPUT:  gets a pointer to a tree and an integer for data as input.
    OUTPUT: ERR_OK if succeeded
    ERRORS: ERR_NOT_INITIALIZED - if the tree doesn't exist.
            ERR_ALLOCATION_FAILED - if node allocation failed...
            ERR_EXISTING_VALUE - if the data already exist in the tree  */
ADTErr TreeInsert(Tree* _tree, int _data);

/*  DESC:   The funcion TreeIsDataFound looking for data in the tree.
    INPUT:  gets a pointer to a tree and an integer for data as input.
    OUTPUT: 0 - if the number isn't exist, 1 - if exist.
    ERRORS: -1 - if the tree isn't exist                                */
int TreeIsDataFound(Tree* _tree, int _data);

/*  DESC:   The funcion TreePrint prints the data of the tree in one of three
            methods: PRE_ORDER, IN_ORDER and POST_ORDER.
    INPUT:  gets a pointer to a tree and the method as input.
    OUTPUT: prints the data to the sdtout
    ERRORS: none                                */
void TreePrint(Tree* _tree, TreeTraverse _traverseMode);

int IsTreeFull(Tree* _tree);

#endif /* #define __BST_H__ */
