#include <stdio.h>
#include "BST.h"

void TestCreate();

void TestInsertNullTree();
void TestInsertToEmptyTree();
void TestInsertRight();
void TestInsertLeft();
void TestInsertLeftAndRight();
void TestInsertRightAndLeft();
void TestInsertDouble();

void TestIsDataFoundNull();
void TestIsDataFoundEmpty();
void TestIsDataFoundExist();
void TestIsDataFoundNotExist();

void TestPrints();

void TestDoubleDestroy();

static void PrintFormat(size_t _flag);

int main()
{
    TestCreate();

    TestInsertNullTree();
    TestInsertToEmptyTree();
    TestInsertRight();
    TestInsertLeft();
    TestInsertLeftAndRight();
    TestInsertRightAndLeft();
    TestInsertDouble();
    
    TestIsDataFoundNull();
    TestIsDataFoundEmpty();
    TestIsDataFoundExist();
    TestIsDataFoundNotExist();
    
    TestPrints();

    TestDoubleDestroy();

    return 0;
}

void TestCreate()
{
    size_t flag = 1;
    Tree* tree;
    tree = TreeCreate();
    if(NULL != tree)
    {
        flag = 0;
    }
    TreeDestroy(tree);
    PrintFormat(flag);
    printf("Test Create\n");
}

void TestInsertNullTree()
{
    size_t flag = ERR_OK;
    Tree* tree = NULL;
    flag = TreeInsert(tree, 5);
    TreeDestroy(tree);
    PrintFormat(!flag);
    printf("Test Insert Null Tree\n");
}

void TestInsertToEmptyTree()
{
    ADTErr flag = 1;
    Tree* tree;
    tree = TreeCreate();
    flag = TreeInsert(tree, 5);
    TreeDestroy(tree);
    PrintFormat(flag);
    printf("Test Insert To Empty Tree\n");
}
void TestInsertRight()
{
    ADTErr flag = 1;
    Tree* tree;
    tree = TreeCreate();
    TreeInsert(tree, 5);
    flag = TreeInsert(tree, 8);
    TreeDestroy(tree);
    PrintFormat(flag);
    printf("Test Insert Right\n");   
}
void TestInsertLeft()
{
    ADTErr flag = 1;
    Tree* tree;
    tree = TreeCreate();
    TreeInsert(tree, 5);
    flag = TreeInsert(tree, 3);
    TreeDestroy(tree);
    PrintFormat(flag);
    printf("Test Insert Left\n");    
}

void TestInsertLeftAndRight()
{
    ADTErr flag = 1;
    Tree* tree;
    tree = TreeCreate();
    TreeInsert(tree, 5);
    TreeInsert(tree, 1);
    flag = TreeInsert(tree, 3);
    TreeDestroy(tree);
    PrintFormat(flag);
    printf("Test Insert Left And Right\n");   
}

void TestInsertRightAndLeft()
{
    ADTErr flag = 1;
    Tree* tree;
    tree = TreeCreate();
    TreeInsert(tree, 5);
    TreeInsert(tree, 9);
    flag = TreeInsert(tree, 7);
    TreeDestroy(tree);
    PrintFormat(flag);
    printf("Test Insert Right And Left\n");    
}

void TestInsertDouble()
{
    ADTErr flag = 1;
    Tree* tree;
    tree = TreeCreate();
    TreeInsert(tree, 5);
    flag = TreeInsert(tree, 5);
    TreeDestroy(tree);
    PrintFormat(!flag);
    printf("Test Insert Double\n");
}

void TestIsDataFoundNull()
{
    int flag = 1;
    Tree* tree = NULL;
    flag = TreeIsDataFound(tree, 7);
    TreeDestroy(tree);
    PrintFormat(!flag);
    printf("Test Is Data Found in NULL tree\n");
}

void TestIsDataFoundEmpty()
{
    int flag = 1;
    Tree* tree;
    tree = TreeCreate();
    flag = TreeIsDataFound(tree, 5);
    TreeDestroy(tree);
    PrintFormat(flag);
    printf("Test Is Data Found In Empty Tree\n");
}

void TestIsDataFoundExist()
{
    int flag = 1;
    Tree* tree;
    tree = TreeCreate();
    TreeInsert(tree, 5);
    TreeInsert(tree, 9);
    TreeInsert(tree, 7);
    flag = TreeIsDataFound(tree, 9);
    TreeDestroy(tree);
    PrintFormat(!flag);
    printf("Test Is Data Found If Exists\n");
}

void TestIsDataFoundNotExist()
{
    int flag = 1;
    Tree* tree;
    tree = TreeCreate();
    TreeInsert(tree, 5);
    TreeInsert(tree, 9);
    flag = TreeIsDataFound(tree, 7);
    TreeDestroy(tree);
    PrintFormat(flag);
    printf("Test Is Data Found If Not Exists\n");
}

void TestPrints()
{
    Tree* tree;
  /*  int isFull;*/
    tree = TreeCreate();
    TreeInsert(tree, 6);
    TreeInsert(tree, 4);
    TreeInsert(tree, 2);
    TreeInsert(tree, 5);
    TreeInsert(tree, 10);
    TreeInsert(tree, 8);
    TreeInsert(tree, 12);
    TreeInsert(tree, 1);
    TreeInsert(tree, 3);
    printf("PRE_ORDER:  ");
    TreePrint(tree, PRE_ORDER);
    printf("IN_ORDER:   ");
    TreePrint(tree, IN_ORDER);
    printf("POST_ORDER: ");
    TreePrint(tree, POST_ORDER); 
    printf("%d\n", IsTreeFull(tree));
    TreeDestroy(tree);   
}

void TestDoubleDestroy()
{
    Tree* tree;
    tree = TreeCreate();
    TreeDestroy(tree);
    TreeDestroy(tree);
    printf("PASSED:     Test Double Destroy\n");
}
    

static void PrintFormat(size_t _flag)
{
    if(_flag == 0)
    {
        printf("PASSED:     ");
    }
    else
    {
        printf("FAILED:     ");
    }
}
