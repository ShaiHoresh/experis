
#include <stdio.h>  /*printf*/
#include <stdlib.h> /*malloc*/
#include <time.h>  /*rand, clock*/
#include <math.h>  /*pow*/ 
#include "vector.h"
#include "Sorts.h"

int Inc(int _first, int _second)
{
    return(_first > _second);
}

int Dec(int _first, int _second)
{
    return(_first <= _second);
}

int WholeNumber(void* _number, int _key)
{
    return (int)_number;
}

int Digit(void* _number, int _key)
{
    return (((int)_number / _key) % 10);
}

Vector* MakeVectorWithValues(int *arr, size_t numOfElements);
Vector* MakeVectorWithRandValues(int *arr, size_t numOfElements);
int CheckIfSorted(Vector* _vec);
void PrintFormat(size_t _flag);

void TestBubbleNormalVector();/*
void TestBubbleNullVec
void TestBubbleEmptyVec
void TestBubbleOneValue
void TestBubbleTwoValuesInc
void TestBubbleTwoValuesDec
void TestBubbleTwoValuesIdentical
*/
void TestShakeNormalVector();/*
void TestShakeNullVec
void TestShakeEmptyVec
void TestShakeOneValue
void TestShakeTwoValuesInc
void TestShakeTwoValuesDec
void TestShakeTwoValuesIdentical*/

void TestQuickRecNormalVector();/*
void TestQuickRecNullVec
void TestQuickRecEmptyVec
void TestQuickRecOneValue
void TestQuickRecTwoValuesInc
void TestQuickRecTwoValuesDec
void TestQuickRecTwoValuesIdentical

void TestQuickIterNormalVector
void TestQuickIterNullVec
void TestQuickIterEmptyVec
void TestQuickIterOneValue
void TestQuickIterTwoValuesInc
void TestQuickIterTwoValuesDec
void TestQuickIterTwoValuesIdentical*/

void TestInsertionNormalVector();/*
void TestInsertionNullVec
void TestInsertionEmptyVec
void TestInsertionOneValue
void TestInsertionTwoValuesInc
void TestInsertionTwoValuesDec
void TestInsertionTwoValuesIdentical
*/

void TestSelectionNormalVector();

void TestShellNormalVector();

void TestMergeSortRecNormalVector();

void TestMergeSortIterativeNormalVector();

void TestCountingSortNormalVector();

void TestRadixSortNormalVector();



int main()
{
	srand(time(NULL));
    TestBubbleNormalVector();
    
    TestShakeNormalVector();
    
    TestQuickRecNormalVector();
    
    TestInsertionNormalVector();
    
    TestSelectionNormalVector();
    
    TestShellNormalVector();
    
    TestMergeSortRecNormalVector();
    
    TestMergeSortIterativeNormalVector();
    
    TestCountingSortNormalVector();
    
    TestRadixSortNormalVector();
    
	return 0;
}

void TestBubbleNormalVector()
{
    Vector* vector;
    int flag;
    int array[] = {30, 40, 23, 10, 36, 54, 45, 56, 14, 26};
    vector = MakeVectorWithValues(array, 5);
    BubbleSort(vector);
    flag = CheckIfSorted(vector);
    PrintFormat(flag);
    {
        printf("Test Bubble Normal Vector\n");
    }

	VectorDestroy(vector);
}

void TestShakeNormalVector()
{
    Vector* vector;
    int flag;
    int array[] = {30, 40, 23, 10, 36, 54, 45, 56, 14, 26};
    vector = MakeVectorWithValues(array, 10);
    ShakeSort(vector);
    flag = CheckIfSorted(vector);
    PrintFormat(flag);
    {
        printf("Test Bubble Normal Vector\n");
    }
	VectorDestroy(vector);
}

void TestQuickRecNormalVector()
{
    Vector* vector;
    int flag;
    int array[] = {12, 40, 23, 30, 36, 54, 45, 30, 14, 70};
    vector = MakeVectorWithValues(array, 10);
    QuickSortRec(vector);
    flag = CheckIfSorted(vector);
    PrintFormat(flag);
    {
        printf("Test QuickRec Normal Vector\n");
    }
	VectorDestroy(vector);
}

void TestInsertionNormalVector()
{
    Vector* vector;
    int flag;
    int array[] = {30, 40, 23, 10, 36, 54, 45, 56, 14, 26};
    vector = MakeVectorWithValues(array, 10);
    InsertionSort(vector, Inc);
    flag = CheckIfSorted(vector);
    PrintFormat(flag);
    {
        printf("Test Insertion Normal Vector\n");
    }

	VectorDestroy(vector);
}

void TestSelectionNormalVector()
{
    Vector* vector;
    int flag;
    int array[] = {888, 40, 23, 10, 36, 54, 45, 56, 14, 26};
    vector = MakeVectorWithValues(array, 9);
    SelectionSort(vector);
    flag = CheckIfSorted(vector);
    PrintFormat(flag);
    {
        printf("Test Selection Normal Vector\n");
    }
	VectorDestroy(vector);
}

void TestShellNormalVector()
{
    Vector* vector;
    int flag;
    int array[] = {888, 777, 666, 50, 36, 54, 45, 56, 14, 26};
    vector = MakeVectorWithValues(array, 10);
    ShellSort(vector, Inc);
    flag = CheckIfSorted(vector);
    PrintFormat(flag);
    {
        printf("Test Shell Normal Vector\n");
    }
	VectorDestroy(vector);
}

void TestMergeSortRecNormalVector()
{
    Vector* vector;
    int flag;
    int array[] = {30, 40, 23, 10, 36, 54, 45, 56, 14, 26};
    vector = MakeVectorWithValues(array, 8);
    MergeSortRec(vector);
    flag = CheckIfSorted(vector);
    PrintFormat(flag);
    {
        printf("Test Merge Sort Rec Normal Vector\n");
    }
	VectorDestroy(vector);
}

void TestMergeSortIterativeNormalVector()
{
    Vector* vector;
    int flag;
    int array[] = {30, 40, 23, 10, 80, 54, 45, 56, 14, 26};
    vector = MakeVectorWithValues(array, 10);
    MergeSort(vector);
    flag = CheckIfSorted(vector);
    PrintFormat(flag);
    {
        printf("Test Merge Sort Iterative Normal Vector\n");
    }
	VectorDestroy(vector);
}

void TestCountingSortNormalVector()
{
    Vector* vector;
    int flag;
    int array[] = {1, 6, 13, 10, 3, 12, 5, 3, 6, 1};
    vector = MakeVectorWithValues(array, 10);
    CountingSort(vector, 15, WholeNumber, 0);
    flag = CheckIfSorted(vector);
    PrintFormat(flag);
    {
        printf("Test Counting Sort Normal Vector\n");
    }
	VectorDestroy(vector);
}

void TestRadixSortNormalVector()
{
    Vector* vector;
    int flag;
    int array[] = {153, 226, 452, 230, 853, 24, 461, 823, 6, 281};
    vector = MakeVectorWithRandValues(array, 50);
    RadixSort(vector, 2, Digit);
    flag = CheckIfSorted(vector);
    PrintFormat(flag);
    {
        printf("Test Radix Sort Normal Vector\n");
    }
	VectorDestroy(vector);
}

/*********************************************************/

Vector* MakeVectorWithValues(int *arr, size_t numOfElements)
{
	Vector* vector;
	int i;
	vector = VectorCreate(numOfElements, 2);
	if(NULL == vector)
	{
	    return NULL;
	}
	for(i = 0; i < numOfElements; ++i)
	{
        VectorAdd(vector, arr[i]);
    }
    return vector;
}

Vector* MakeVectorWithRandValues(int *arr, size_t numOfElements)
{
	Vector* vector;
	int i;
	vector = VectorCreate(numOfElements, 2);
	if(NULL == vector)
	{
	    return NULL;
	}
	for(i = 0; i < numOfElements; ++i)
	{
        VectorAdd(vector, (rand() % numOfElements));
    }
    return vector;
}





int CheckIfSorted(Vector* _vec)
{
    int i, a, b;
    int NOE;
    
    VectorItemsNum(_vec, &NOE);
    for(i = 0; i < NOE - 1; ++i)
    {
        VectorGet(_vec, i, &a);
        VectorGet(_vec, i + 1, &b);
        if(a > b)
        {
            return 0;
        }
    }
    return 1;
}

void PrintFormat(size_t _flag)
{
    if(_flag != 0)
    {
        printf("PASSED:     ");
    }
    else
    {
        printf("FAILED:     ");
    }
}

