#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, size_t, rand */

#include "../../inc/binTree.h"

void PrintFormat(int flag)
{
    flag ? printf("Succeeded:   ") : printf("Failed:        ");
}

int LessInt(void* _left, void* _right)
{
    return *(int*)_left < *(int*)_right;
}

void DestroyReg(void* _data)
{
    free(_data);
    return;
}

void TestCreate();
void TestCreateWNull();

void TestDoubleDestroy();

void TestInsertNormal();
void TestItrBeginNormal();
void TestItrNextNormal();
void TestItraFewNextNormal();

void TestItrEndNormal();
void TestItrPrevNormal();
void TestItraFewPrevNormal();

int main()
{
    TestCreate();
    TestCreateWNull();
    
    TestDoubleDestroy();
    TestInsertNormal();
    TestItrBeginNormal();
    TestItrNextNormal();
    TestItraFewNextNormal();
    
    TestItrEndNormal();
    TestItrPrevNormal();
    TestItraFewPrevNormal();
    
    return 0;
}

void TestCreate()
{
    BSTree* tree;
    tree = BSTreeCreate(LessInt);
    PrintFormat((int)tree);
    printf("Test create normal\n");
    BSTreeDestroy(tree, DestroyReg);
}

void TestCreateWNull()
{
    BSTree* tree;
    tree = BSTreeCreate(NULL);
    PrintFormat(!tree);
    printf("Test create NULL function\n");
    BSTreeDestroy(tree, DestroyReg);
}

void TestDoubleDestroy()
{
    BSTree* tree;
    tree = BSTreeCreate(LessInt);
    PrintFormat((int)tree);
    BSTreeDestroy(tree, DestroyReg);
    BSTreeDestroy(tree, DestroyReg);
    printf("Test Double Destroy\n");
}

void TestInsertNormal()
{
    BSTree* tree;
    int* a;
    int i, arr[11] = {14, 24, 32, 1452, 567, 2, 95, 1, 890, 3468, 25456};
    
    tree = BSTreeCreate(LessInt);
    
    for(i = 0; i < 11; ++i)
    {
        a = malloc(sizeof(int));
        *a = arr[i];
        BSTreeInsert(tree, a);
    }
    PrintFormat((int)tree);
    printf("Test create normal\n");
    BSTreePrint(tree, BSTREE_TRAVERSAL_INORDER);
    BSTreePrint(tree, BSTREE_TRAVERSAL_POSTORDER);
    BSTreePrint(tree, BSTREE_TRAVERSAL_PREORDER);
    BSTreeDestroy(tree, DestroyReg);
}

void TestItrBeginNormal()
{
    BSTree* tree;
    BSTreeItr itr = NULL;
    int* a;
    void* data;
    int i, arr[11] = {14, 24, 32, 1452, 567, 2, 95, 1, 890, 3468, 25456};
    
    tree = BSTreeCreate(LessInt);
    
    for(i = 0; i < 11; ++i)
    {
        a = malloc(sizeof(int));
        *a = arr[i];
        BSTreeInsert(tree, a);
    }
    itr = BSTreeItrBegin(tree);
    data = BSTreeItrGet(itr);
    PrintFormat(*(int*)data == 1);
    printf("Test Itr Begin Normal\n");
    BSTreeDestroy(tree, DestroyReg);
}
    
void TestItrNextNormal()
{
    BSTree* tree;
    BSTreeItr itr = NULL;
    int* a;
    void* data;
    int i, arr[11] = {14, 24, 32, 1452, 567, 2, 95, 1, 890, 3468, 25456};
    
    tree = BSTreeCreate(LessInt);
    
    for(i = 0; i < 11; ++i)
    {
        a = malloc(sizeof(int));
        *a = arr[i];
        BSTreeInsert(tree, a);
    }
    itr = BSTreeItrBegin(tree);
    itr = BSTreeItrNext(itr);
    data = BSTreeItrGet(itr);
    PrintFormat(*(int*)data == 2);
    printf("Test Itr Next Normal\n");
    BSTreeDestroy(tree, DestroyReg);
}
    
void TestItraFewNextNormal()
{
    BSTree* tree;
    BSTreeItr itr = NULL;
    int* a;
    void* data;
    int i, arr[11] = {14, 24, 32, 1452, 567, 2, 95, 1, 890, 3468, 25456};
    
    tree = BSTreeCreate(LessInt);
    
    for(i = 0; i < 11; ++i)
    {
        a = malloc(sizeof(int));
        *a = arr[i];
        BSTreeInsert(tree, a);
    }
    itr = BSTreeItrBegin(tree);
    
    for(i = 0; i < 8; ++i)
    {
        itr = BSTreeItrNext(itr);
    }
    data = BSTreeItrGet(itr);
    PrintFormat(*(int*)data == 1452);
    printf("Test Itr Few Next Normal\n");
    BSTreeDestroy(tree, DestroyReg);
}

void TestItrEndNormal()
{
    BSTree* tree;
    BSTreeItr itr = NULL;
    int* a;

    int i, arr[11] = {14, 24, 32, 1452, 567, 2, 95, 1, 890, 3468, 25456};
    
    tree = BSTreeCreate(LessInt);
    
    for(i = 0; i < 11; ++i)
    {
        a = malloc(sizeof(int));
        *a = arr[i];
        BSTreeInsert(tree, a);
    }
    itr = BSTreeItrEnd(tree);
   /* data = BSTreeItrGet(itr);*/
    PrintFormat(NULL != itr);
    printf("Test Itr End Normal\n");
    BSTreeDestroy(tree, DestroyReg);
}

void TestItrPrevNormal()
{
    BSTree* tree;
    BSTreeItr itr = NULL;
    int* a;
    void* data;
    int i, arr[11] = {14, 24, 32, 1452, 567, 2, 95, 1, 890, 3468, 25456};
    
    tree = BSTreeCreate(LessInt);
    
    for(i = 0; i < 11; ++i)
    {
        a = malloc(sizeof(int));
        *a = arr[i];
        BSTreeInsert(tree, a);
    }
    itr = BSTreeItrEnd(tree);
    itr = BSTreeItrPrev(itr);
    data = BSTreeItrGet(itr);
    PrintFormat(*(int*)data == 25456);
    printf("Test Itr Prev Normal\n");
    BSTreeDestroy(tree, DestroyReg);
}

void TestItraFewPrevNormal()
{
    BSTree* tree;
    BSTreeItr itr = NULL;
    int* a;
    void* data;
    int i, arr[11] = {14, 24, 32, 1452, 567, 2, 95, 1, 890, 3468, 25456};
    
    tree = BSTreeCreate(LessInt);
    
    for(i = 0; i < 11; ++i)
    {
        a = malloc(sizeof(int));
        *a = arr[i];
        BSTreeInsert(tree, a);
    }
    itr = BSTreeItrEnd(tree);
    
    for(i = 0; i < 8; ++i)
    {
        itr = BSTreeItrPrev(itr);
    }
    data = BSTreeItrGet(itr);
    PrintFormat(*(int*)data == 24);
    printf("Test Itr Few Prev Normal\n");
    BSTreeDestroy(tree, DestroyReg);
}
