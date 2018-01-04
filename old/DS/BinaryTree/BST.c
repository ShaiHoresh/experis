#include <stdlib.h>
#include <stdio.h>

#include "BST.h"

#define MAGIC 5462154

/*typedef struct Tree Tree;*/
typedef struct Node Node;

struct Node
{
    int m_data;
    Node* m_left;
    Node* m_right;
    Node* m_father;
};

struct Tree{
	Node*   m_root;
	int     m_test;
};

/*  DESC:   The funcion NodeCreate creates a node...
    INPUT:  gets nothing as input.
    OUTPUT: a pointer to a new node - iniialized to null at its members.                 
    ERRORS: returns NULL if allocation failed       */
static Node* NodeCreate();

/*  DESC:   The funcion FindPlace find the father of the next node
    INPUT:  gets the root (tree->m_root) and the data as input.
    OUTPUT: a pointer to the father.
    ERRORS: returns NULL if gets NULL             */
static Node* FindPlace(Node* _node, int _data);

/*  DESC:   The funcion Check checks the structs isn't NULL
    INPUT:  gets a void* to the struct (Node/ Tree)
    OUTPUT: ERR_OK if the struct initialized
    ERRORS: ERR_NOT_INITIALIZED if not.             */
static ADTErr Check(void* _struct);

/*  DESC:   The funcion prints the tree in pre-order method
    INPUT:  gets the root (tree->m_root).
    OUTPUT: print to stdout
    ERRORS: none            */
static void PrintPre(Node* _node);

/*  DESC:   The funcion prints the tree in in-order method
    INPUT:  gets the root (tree->m_root).
    OUTPUT: print to stdout
    ERRORS: none            */
static void PrintIn(Node* _node);

/*  DESC:   The funcion prints the tree in post-order method
    INPUT:  gets the root (tree->m_root).
    OUTPUT: print to stdout
    ERRORS: none            */
static void PrintPost(Node* _node);

/*  DESC:   The funcion NodesDestroy destroys all of the nodes.
    INPUT:  gets the root (tree->m_root)
    OUTPUT: none
    ERRORS: none                                    */
static void NodesDestroy(Node* _node);

/*

*/
static void InsertSon(Node* _father, Node* _son);

static int IsFullRec(Node* _node);

Tree* TreeCreate()
{
    Tree* tree;
    tree = malloc(sizeof(Tree));
    if(NULL == tree)
    {
        return NULL;
    }
    tree->m_root = NULL;
    tree->m_test = MAGIC;
    return tree;
}

void TreeDestroy(Tree* _tree)
{
    if(Check((void*)_tree) != ERR_OK || _tree->m_test != MAGIC)
    {
        return;
    }
    _tree->m_test = 0;
    if(Check((void*)_tree->m_root) != ERR_OK)
    {
        free(_tree);
        return;
    }
    NodesDestroy(_tree->m_root);
    free(_tree);
}

ADTErr TreeInsert(Tree* _tree, int _data)
{
    Node* node, *father;
    if(Check((void*)_tree) != ERR_OK)
    {
        return ERR_NOT_INITIALIZED;
    }
    node = NodeCreate(_data);
    if(Check((void*)node) != ERR_OK)
    {
        return ERR_ALLOCATION_FAILED;
    }
    
     /* The first node (the root) "treatment"*/
    if(NULL == _tree->m_root)
    {
        _tree->m_root = node;
        return ERR_OK;
    }
    
    /*in the rest of the tree: */
    father = FindPlace(_tree->m_root, _data);
    if(father->m_data == _data)
    {
        return ERR_EXISTING_VALUE;
    }
    InsertSon(father, node);

    return ERR_OK;
}

int TreeIsDataFound(Tree* _tree, int _data)
{
    int flag = 1;
    Node* node;
    if(Check((void*)_tree) != ERR_OK)
    {
        return -1;
    }
    node = FindPlace(_tree->m_root, _data);
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

void TreePrint(Tree* _tree, TreeTraverse _traverseMode)
{
    Node* node;
    node = _tree->m_root;
    if(Check((void*)_tree) != ERR_OK)
    {
        return;
    }
    switch(_traverseMode)
    {
        case PRE_ORDER:
            PrintPre(node);
        break;
        case IN_ORDER:
            PrintIn(node);
        break;
        case POST_ORDER:
            PrintPost(node);
        break;
        default:
        break;
    }
    printf("\n");
}

int IsTreeFull(Tree* _tree)
{
    if(NULL == _tree)
    {
        return 1;
    }
    
    return IsFullRec(_tree->m_root);
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
    if(NULL != _node)
    {
        printf("%d  ", _node->m_data);
        PrintPre(_node->m_left);
        PrintPre(_node->m_right);
    }
}

static void PrintIn(Node* _node)
{
    if(NULL != _node)
    {
        PrintIn(_node->m_left);
        printf("%d  ", _node->m_data);
        PrintIn(_node->m_right);
    }
}

static void PrintPost(Node* _node)
{
    if(NULL != _node)
    {
        PrintPost(_node->m_left);
        PrintPost(_node->m_right);
        printf("%d  ", _node->m_data);
    }
}

static void NodesDestroy(Node* _node)
{
    if(NULL != _node)
    {
        NodesDestroy(_node->m_left);
        NodesDestroy(_node->m_right);
        free(_node);
    }  
}

static Node* FindPlace(Node* _node, int _data)
{
    if(NULL == _node)
    {
        return _node;
    }
    if(_data == _node->m_data)
    {
        return _node;
    }
    if(_data > _node->m_data && NULL == _node->m_right)
    {
        return _node;
    }
    if(_data < _node->m_data && NULL == _node->m_left)
    {
        return _node;
    }
    (_data > _node->m_data) ? FindPlace(_node->m_right, _data) : FindPlace(_node->m_left, _data);
}

static Node* NodeCreate(int _data)
{
    Node* node;
    node = calloc(1, sizeof(Node));
    node->m_data = _data;
    return node;
}

static ADTErr Check(void* _struct)
{
    if(NULL == _struct)
    {
        return ERR_NOT_INITIALIZED;
    }
    return ERR_OK;
}

static void InsertSon(Node* _father, Node* _son)
{
    (_father->m_data < _son->m_data) ? (_father->m_right = _son) : (_father->m_left = _son);
    _son->m_father = _father;
}
