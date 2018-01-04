#include <stdlib.h> /* malloc size_t */
#include <stdio.h> /* printf - leftover from none generic */

#define DEBUG

#include <assert.h>

#include "../../inc/binTree.h"

#define MAGIC 0xDEADBEAD

#define IS_A_TREE(T)     ((T) && (T)->m_magic == MAGIC)
/*#define                               */

/*typedef struct BSTree BSTree;*/
typedef struct Node Node;

struct Node
{
    void* m_data;
    Node* m_left;
    Node* m_right;
    Node* m_parent;
};

struct BSTree
{
	unsigned int    m_magic;
    Node            m_sentinel;
	LessComparator  m_compFunc;
};

/*  DESC:   The funcion NodeCreate creates a node...
    INPUT:  gets nothing as input.
    OUTPUT: a pointer to a new node - iniialized to null at its members.                 
    ERRORS: returns NULL if allocation failed       */
static Node* NodeCreate();

/*  DESC:   The funcion FindPlace find the parent of the next node
    INPUT:  gets the root (tree->m_sentinel) and the data as input.
    OUTPUT: a pointer to the parent.
    ERRORS: returns NULL if gets NULL             */
static Node* FindPlace(Node* _node, void* _data, PredicateFunction _compFunc);

/*  DESC:   The funcion Check checks the structs isn't NULL
    INPUT:  gets a void* to the struct (Node/ BSTree)
    OUTPUT: 0 if the struct initialized
    ERRORS: ERR_NOT_INITIALIZED if not.             */
/*static ADTErr Check(void* _struct);*/

/*  DESC:   The funcion prints the tree in pre-order method
    INPUT:  gets the root (tree->m_sentinel).
    OUTPUT: print to stdout
    ERRORS: none            */
static void PrintPre(Node* _node);

/*  DESC:   The funcion prints the tree in in-order method
    INPUT:  gets the root (tree->m_sentinel).
    OUTPUT: print to stdout
    ERRORS: none            */
static void PrintIn(Node* _node);

/*  DESC:   The funcion prints the tree in post-order method
    INPUT:  gets the root (tree->m_sentinel).
    OUTPUT: print to stdout
    ERRORS: none            */
static void PrintPost(Node* _node);

/*  DESC:   The funcion NodesDestroy destroys all of the nodes.
    INPUT:  gets the root (tree->m_sentinel)
    OUTPUT: none
    ERRORS: none                                    */
static void NodesDestroy(Node* _node, Destroyer _destroyer);

/*

*/
static void InsertSon(Node* _parent, Node* _son, PredicateFunction _compFunc);

static int IsFullRec(Node* _node);

static BSTreeItr GoDownLeft(Node* _node);

static BSTreeItr GoUpRight(Node* _node);

static BSTreeItr GoDownRight(Node* _node);
  
static BSTreeItr GoUpLeft(Node* _node);

/******************************************************/

BSTree* BSTreeCreate(LessComparator _less)
{
    BSTree* tree;
    if(!_less)
    {
        return NULL;
    }
    
    tree = malloc(sizeof(BSTree));
    if(NULL == tree)
    {
        return NULL;
    }
    
    tree->m_sentinel.m_parent = &tree->m_sentinel;
    tree->m_sentinel.m_left = NULL;
    tree->m_sentinel.m_right = NULL;

    tree->m_compFunc = _less;
    tree->m_magic = MAGIC;

    return tree;
}

void BSTreeDestroy(BSTree* _tree, void (*_destroyer)(void*))
{
    if(!IS_A_TREE(_tree))
    {
        return;
    }

    _tree->m_magic = 0;

    NodesDestroy(_tree->m_sentinel.m_left, _destroyer);

    free(_tree);
}

BSTreeItr BSTreeInsert(BSTree* _tree, void* _data)
{
    Node* node, *parent;
    if(!IS_A_TREE(_tree))
    {
        return NULL;
    }
    node = NodeCreate(_data);
    if(NULL == node)
    {
        return NULL;
    }
    
     /* The first node (the root) "treatment"*/
    if(NULL == _tree->m_sentinel.m_left)
    {
        _tree->m_sentinel.m_left = node;
        return 0;
    }
    
    /*in the rest of the tree: */
    parent = FindPlace(_tree->m_sentinel.m_left, _data, _tree->m_compFunc);

    InsertSon(parent, node, _tree->m_compFunc);

    return 0;
}
/*
int TreeIsDataFound(BSTree* _tree, int _data)
{
    int flag = 1;
    Node* node;
    if(Check((void*)_tree) != 0)
    {
        return -1;
    }
    node = FindPlace(_tree->m_sentinel, _data);
    if(NULL == node)
    {
        flag = 0;
    }
    else if(node->m_data != _data)
    {
        flag = 0;
    }
    return flag;
}
*/
void BSTreePrint(BSTree* _tree, TreeTraversalMode _traverseMode)
{
    Node* node;
    node = _tree->m_sentinel.m_left;
    if(!IS_A_TREE(_tree))
    {
        return;
    }
    switch(_traverseMode)
    {
        case BSTREE_TRAVERSAL_PREORDER:
            PrintPre(node);
        break;
        case BSTREE_TRAVERSAL_INORDER:
            PrintIn(node);
        break;
        case BSTREE_TRAVERSAL_POSTORDER:
            PrintPost(node);
        break;
        default:
        break;
    }
    printf("\n");
}

BSTreeItr BSTreeItrBegin(const BSTree* _tree)
{
    Node* node;
    if(!IS_A_TREE(_tree) || _tree->m_sentinel.m_left == NULL)
    {
        return NULL;
    }
    
    node = _tree->m_sentinel.m_left;
    while(node->m_left != NULL)
    {
        node = node->m_left;
    }
    return (BSTreeItr)node;
}

BSTreeItr BSTreeItrEnd(const BSTree* _tree)
{
    if(!IS_A_TREE(_tree))
    {
        return NULL;
    }
    return (BSTreeItr)&_tree->m_sentinel;
}

int BSTreeItrEquals(BSTreeItr _a, BSTreeItr _b)
{
    return _a == _b;
}

BSTreeItr BSTreeItrNext(BSTreeItr _it)
{
    Node* node;
    
    node = (Node*)_it;
    
    if(NULL == _it)
    {
        return NULL;
    }
    /* TODO make it like a story (-; */
    /* node->m_right ? GoDownLeft(node) : GoUpRight(node) 
    if(node->m_right != NULL)
    {
        node = node->m_right;
        while(node->m_left != NULL)
        {
            node = node->m_left;
        }
    }
    else
    {
        while(node == node->m_parent->m_right)
        {
            node = node->m_parent;
        }
        node = node->m_parent;
        if(node == node->m_parent)
        {
            node = node->m_parent->m_right;
        }
    }*/
    
    return node->m_right ? GoDownLeft(node) : GoUpRight(node);
}



BSTreeItr BSTreeItrPrev(BSTreeItr _it)
{
    Node *node;
    node = (Node*)_it;
    
    if(NULL == _it)
    {
        return NULL;
    }
    
    return node->m_left ? GoDownRight(node) : GoUpLeft(node);
}

void* BSTreeItrGet(BSTreeItr _it)
{
    Node* node;
    if(NULL == _it)
    {
        return NULL;
    }
    node = (Node*)_it;
    return (void*)node->m_data;
}
/********************************************************/
int IsTreeFull(BSTree* _tree)
{
    if(NULL == _tree)
    {
        return 1;
    }
    
    return IsFullRec(_tree->m_sentinel.m_left);
}

static int IsFullRec(Node* _node)
{
    if(NULL == _node)
    {
        return 1;
    }
    
    if((NULL == _node->m_left && NULL != _node->m_right) || (NULL == _node->m_right && NULL != _node->m_left))
    {
        return 0;
    }
    
    return IsFullRec(_node->m_left) && IsFullRec(_node->m_right);
}


static void PrintPre(Node* _node)
{
    if(NULL == _node)/* || _node == _node->m_parent)*/
    {
        return;
    }
  
    printf("%d  ", *(int*)_node->m_data);
    PrintPre(_node->m_left);
    PrintPre(_node->m_right);
}

static void PrintIn(Node* _node)
{
    if(NULL == _node)/* || _node == _node->m_parent)*/
    {
        return;
    }

    PrintIn(_node->m_left);
    printf("%d  ", *(int*)_node->m_data);
    PrintIn(_node->m_right);
}

static void PrintPost(Node* _node)
{
    if(NULL == _node)/* || _node == _node->m_parent)*/
    {
        return;
    }
    PrintPost(_node->m_left);
    PrintPost(_node->m_right);
    printf("%d  ", *(int*)_node->m_data);
}

static void NodesDestroy(Node* _node, Destroyer _destroyer)
{
    if(NULL == _node)
    {
		return;
	}
	
    NodesDestroy(_node->m_left, _destroyer);
    NodesDestroy(_node->m_right, _destroyer);
    
    if(NULL != _destroyer)
    {
		_destroyer(_node->m_data);
	}
	
	free(_node);
}

static Node* FindPlace(Node* _node, void* _data, PredicateFunction _compFunc)
{
    if(NULL == _node)
    {
        return _node;
    }
   /* if(1 == _compFunc(_data, _node->m_data))
    {
        return _node;
    }*/
    if(_compFunc(_node->m_data, _data) && NULL == _node->m_right)
    {
        return _node;
    }
    if(_compFunc(_data, _node->m_data) && NULL == _node->m_left)
    {
        return _node;
    }
    return (_compFunc(_node->m_data, _data)) ? FindPlace(_node->m_right, _data, _compFunc) : FindPlace(_node->m_left, _data, _compFunc);
}

static Node* NodeCreate(void* _data)
{
    Node* node;
    node = calloc(1, sizeof(Node));
    if(NULL == node)
    {
        return NULL;
    }
    node->m_data = _data;
    return node;
}
/*
static ADTErr Check(void* _struct)
{
    if(NULL == _struct)
    {
        return ERR_NOT_INITIALIZED;
    }
    return 0;
}*/

static void InsertSon(Node* _parent, Node* _son, PredicateFunction _compFunc)
{
    _compFunc(_parent->m_data, _son->m_data) ? (_parent->m_right = _son) : (_parent->m_left = _son);
    _son->m_parent = _parent;
}

static BSTreeItr GoDownLeft(Node* _node)
{
    _node = _node->m_right;
    while(_node->m_left != NULL)
    {
        _node = _node->m_left;
    }
    return (BSTreeItr)_node;
}

static BSTreeItr GoUpRight(Node* _node)
{
    while(_node == _node->m_parent->m_right)
    {
        _node = _node->m_parent;
    }

    _node = _node->m_parent;

 /*   if(node == node->m_parent)
    {
        node = node->m_parent->m_right;
    }*/
    return (BSTreeItr)_node;
}

static BSTreeItr GoDownRight(Node* _node)
{
    _node = _node->m_left;
    while(_node->m_right != NULL)
    {
        _node = _node->m_right;
    }
    return (BSTreeItr)_node;
}
    
static BSTreeItr GoUpLeft(Node* _node)
{
    while(_node == _node->m_parent->m_left)
    {
        _node = _node->m_parent;
    }
    _node = _node->m_parent;
/*    if(node == node->m_parent)
    {
        node = guard;
    }*/

    return (BSTreeItr)_node;
}
