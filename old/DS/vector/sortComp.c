#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include "vector.h"
#include "Sorts.h"

void compareRunTimeBubble(int _numOfItems);
void compareRunTimeShake(int _numOfItems);
void compareRunTimeQuickRec(int _numOfItems);
void compareRunTimeInsertion(int _numOfItems);
void compareRunTimeShell(int _numOfItems);
void compareRunTimeSelection(int _numOfItems);
void compareRunTimeMergeRec(int _numOfItems);

void compareRunTimeMerge(int _numOfItems);

int Inc(int _first, int _second)
{
    return(_first > _second);
}

int Dec(int _first, int _second)
{
    return(_first <= _second);
}

Vector* MakeVectorWithValues(int *arr, size_t numOfElements);
int CheckIfSorted(Vector* _vec);

int main()
{
    printf("1000 elements:\n");
    compareRunTimeShake(1000);
    compareRunTimeQuickRec(1000);
    compareRunTimeInsertion(1000);
    compareRunTimeShell(1000);
    compareRunTimeSelection(1000);
    compareRunTimeBubble(1000);
    compareRunTimeMergeRec(1000);
    compareRunTimeMerge(1000);
    
    printf("\n10000 elements:\n");
    compareRunTimeShake(10000);
    compareRunTimeQuickRec(10000);
    compareRunTimeInsertion(10000);
    compareRunTimeShell(10000);
    compareRunTimeSelection(10000);
    compareRunTimeBubble(10000);
    compareRunTimeMergeRec(10000);
    compareRunTimeMerge(10000);
    
    printf("\n50000 elements:\n");
    compareRunTimeShake(50000);
    compareRunTimeQuickRec(50000);
    compareRunTimeInsertion(50000);
    compareRunTimeShell(50000);
    compareRunTimeSelection(50000);
    compareRunTimeBubble(50000);
    compareRunTimeMergeRec(50000);
    compareRunTimeMerge(50000);

	return 0;
}




void compareRunTimeBubble(int _numOfItems)
{
	int i;
	double timeResultRand, timeResultAsc, timeResultDes;
	clock_t timer;
	Vector* randVec, *ascVec, *desVec;
	
	randVec = VectorCreate(_numOfItems, 100);
	ascVec = VectorCreate(_numOfItems, 100);
	desVec = VectorCreate(_numOfItems, 100);
	srand(time(NULL));
	
	for(i = 0; i < _numOfItems ; ++i)
	{
		VectorAdd(randVec, rand()% 100000);
		VectorAdd(ascVec, i);
		VectorAdd(desVec, _numOfItems -i);
	}
	
	timer = clock();
	BubbleSort(randVec);
	timeResultRand = (double)(clock() - timer) /CLOCKS_PER_SEC;
	VectorDestroy(randVec);

    timer = clock();
	BubbleSort(ascVec);
	timeResultAsc = (double)(clock() - timer) /CLOCKS_PER_SEC;
	VectorDestroy(ascVec);
	
	timer = clock();
	BubbleSort(desVec);
	timeResultDes = (double)(clock() - timer) /CLOCKS_PER_SEC;
	VectorDestroy(desVec);
	
	printf("Bubble Sort Rand Values     %f\n",  timeResultRand);
	printf("Bubble Sort Asc Values      %f\n",  timeResultAsc);
	printf("Bubble Sort Des Values      %f\n",  timeResultDes);
	return;
}

void compareRunTimeShake(int _numOfItems)
{
	int i;
	double timeResultRand, timeResultAsc, timeResultDes;
	clock_t timer;
	Vector* randVec, *ascVec, *desVec;
	
	randVec = VectorCreate(_numOfItems, 100);
	ascVec = VectorCreate(_numOfItems, 100);
	desVec = VectorCreate(_numOfItems, 100);
	srand(time(NULL));
	
	for(i = 0; i < _numOfItems ; ++i)
	{
		VectorAdd(randVec, rand()% 100000);
		VectorAdd(ascVec, i);
		VectorAdd(desVec, _numOfItems -i);
	}
	
	
	timer = clock();
	ShakeSort(randVec);
	timeResultRand = (double)(clock() - timer) /CLOCKS_PER_SEC;
	VectorDestroy(randVec);

    timer = clock();
	ShakeSort(ascVec);
	timeResultAsc = (double)(clock() - timer) /CLOCKS_PER_SEC;
	VectorDestroy(ascVec);
	
	timer = clock();
	ShakeSort(desVec);
	timeResultDes = (double)(clock() - timer) /CLOCKS_PER_SEC;
	VectorDestroy(desVec);
	
	printf("Shake Sort Rand Values     %f\n",  timeResultRand);
	printf("Shake Sort Asc Values      %f\n",  timeResultAsc);
	printf("Shake Sort Des Values      %f\n",  timeResultDes);
	return;
}


void compareRunTimeQuickRec(int _numOfItems)
{
	int i;
	double timeResultRand, timeResultAsc, timeResultDes;
	clock_t timer;
	Vector* randVec, *ascVec, *desVec;
	
	randVec = VectorCreate(_numOfItems, 100);
	ascVec = VectorCreate(_numOfItems, 100);
	desVec = VectorCreate(_numOfItems, 100);
	srand(time(NULL));
	
	for(i = 0; i < _numOfItems ; ++i)
	{
		VectorAdd(randVec, rand()% 100000);
		VectorAdd(ascVec, i);
		VectorAdd(desVec, _numOfItems -i);
	}
	
	timer = clock();
	QuickSortRec(randVec);
	timeResultRand = (double)(clock() - timer) /CLOCKS_PER_SEC;
	VectorDestroy(randVec);

    timer = clock();
	QuickSortRec(ascVec);
	timeResultAsc = (double)(clock() - timer) /CLOCKS_PER_SEC;
	VectorDestroy(ascVec);
	
	timer = clock();
	QuickSortRec(desVec);
	timeResultDes = (double)(clock() - timer) /CLOCKS_PER_SEC;
	VectorDestroy(desVec);
	
	printf("Quick Sort Rand Values     %f\n",  timeResultRand);
	printf("Quick Sort Asc Values      %f\n",  timeResultAsc);
	printf("Quick Sort Des Values      %f\n",  timeResultDes);
	return;
}


void compareRunTimeInsertion(int _numOfItems)
{
	int i;
	double timeResultRand, timeResultAsc, timeResultDes;
	clock_t timer;
	Vector* randVec, *ascVec, *desVec;
	
	randVec = VectorCreate(_numOfItems, 100);
	ascVec = VectorCreate(_numOfItems, 100);
	desVec = VectorCreate(_numOfItems, 100);
	srand(time(NULL));
	
	for(i = 0; i < _numOfItems ; ++i)
	{
		VectorAdd(randVec, rand()% 100000);
		VectorAdd(ascVec, i);
		VectorAdd(desVec, _numOfItems -i);
	}
	
	timer = clock();
	InsertionSort(randVec, Inc);
	timeResultRand = (double)(clock() - timer) /CLOCKS_PER_SEC;
	VectorDestroy(randVec);

    timer = clock();
	InsertionSort(ascVec, Inc);
	timeResultAsc = (double)(clock() - timer) /CLOCKS_PER_SEC;
	VectorDestroy(ascVec);
	
	timer = clock();
	InsertionSort(desVec, Inc);
	timeResultDes = (double)(clock() - timer) /CLOCKS_PER_SEC;
	VectorDestroy(desVec);
	
	printf("Insertion Sort Rand Values     %f\n",  timeResultRand);
	printf("Insertion Sort Asc Values      %f\n",  timeResultAsc);
	printf("Insertion Sort Des Values      %f\n",  timeResultDes);
	return;
}

void compareRunTimeShell(int _numOfItems)
{
	int i;
	double timeResultRand, timeResultAsc, timeResultDes;
	clock_t timer;
	Vector* randVec, *ascVec, *desVec;
	
	randVec = VectorCreate(_numOfItems, 100);
	ascVec = VectorCreate(_numOfItems, 100);
	desVec = VectorCreate(_numOfItems, 100);
	srand(time(NULL));
	
	for(i = 0; i < _numOfItems ; ++i)
	{
		VectorAdd(randVec, rand()% 100000);
		VectorAdd(ascVec, i);
		VectorAdd(desVec, _numOfItems -i);
	}
	
	timer = clock();
	ShellSort(randVec, Inc);
	timeResultRand = (double)(clock() - timer) /CLOCKS_PER_SEC;
	VectorDestroy(randVec);

    timer = clock();
	ShellSort(ascVec, Inc);
	timeResultAsc = (double)(clock() - timer) /CLOCKS_PER_SEC;
	VectorDestroy(ascVec);
	
	timer = clock();
	ShellSort(desVec, Inc);
	timeResultDes = (double)(clock() - timer) /CLOCKS_PER_SEC;
	VectorDestroy(desVec);
	
	printf("Shell Sort Rand Values     %f\n",  timeResultRand);
	printf("Shell Sort Asc Values      %f\n",  timeResultAsc);
	printf("Shell Sort Des Values      %f\n",  timeResultDes);
	return;
}

void compareRunTimeSelection(int _numOfItems)
{
	int i;
	double timeResultRand, timeResultAsc, timeResultDes;
	clock_t timer;
	Vector* randVec, *ascVec, *desVec;
	
	randVec = VectorCreate(_numOfItems, 100);
	ascVec = VectorCreate(_numOfItems, 100);
	desVec = VectorCreate(_numOfItems, 100);
	srand(time(NULL));
	
	for(i = 0; i < _numOfItems ; ++i)
	{
		VectorAdd(randVec, rand()% 100000);
		VectorAdd(ascVec, i);
		VectorAdd(desVec, _numOfItems -i);
	}
	
	timer = clock();
	SelectionSort(randVec);
	timeResultRand = (double)(clock() - timer) /CLOCKS_PER_SEC;
	VectorDestroy(randVec);

    timer = clock();
	SelectionSort(ascVec);
	timeResultAsc = (double)(clock() - timer) /CLOCKS_PER_SEC;
	VectorDestroy(ascVec);
	
	timer = clock();
	SelectionSort(desVec);
	timeResultDes = (double)(clock() - timer) /CLOCKS_PER_SEC;
	VectorDestroy(desVec);
	
	printf("Selection Sort Rand Values     %f\n",  timeResultRand);
	printf("Selection Sort Asc Values      %f\n",  timeResultAsc);
	printf("Selection Sort Des Values      %f\n",  timeResultDes);
	return;
}

void compareRunTimeMergeRec(int _numOfItems)
{
	int i;
	double timeResultRand, timeResultAsc, timeResultDes;
	clock_t timer;
	Vector* randVec, *ascVec, *desVec;
	
	randVec = VectorCreate(_numOfItems, 100);
	ascVec = VectorCreate(_numOfItems, 100);
	desVec = VectorCreate(_numOfItems, 100);
	srand(time(NULL));
	
	for(i = 0; i < _numOfItems ; ++i)
	{
		VectorAdd(randVec, rand()% 100000);
		VectorAdd(ascVec, i);
		VectorAdd(desVec, _numOfItems -i);
	}
	
	timer = clock();
	MergeSortRec(randVec);
	timeResultRand = (double)(clock() - timer) /CLOCKS_PER_SEC;
	VectorDestroy(randVec);

    timer = clock();
	MergeSortRec(ascVec);
	timeResultAsc = (double)(clock() - timer) /CLOCKS_PER_SEC;
	VectorDestroy(ascVec);
	
	timer = clock();
	MergeSortRec(desVec);
	timeResultDes = (double)(clock() - timer) /CLOCKS_PER_SEC;
	VectorDestroy(desVec);
	
	printf("Merge Sort Rec Rand Values     %f\n",  timeResultRand);
	printf("Merge Sort Rec Asc Values      %f\n",  timeResultAsc);
	printf("Merge Sort Rec Des Values      %f\n",  timeResultDes);
	return;
}

void compareRunTimeMerge(int _numOfItems)
{
	int i;
	double timeResultRand, timeResultAsc, timeResultDes;
	clock_t timer;
	Vector* randVec, *ascVec, *desVec;
	
	randVec = VectorCreate(_numOfItems, 100);
	ascVec = VectorCreate(_numOfItems, 100);
	desVec = VectorCreate(_numOfItems, 100);
	srand(time(NULL));
	
	for(i = 0; i < _numOfItems ; ++i)
	{
		VectorAdd(randVec, rand()% 100000);
		VectorAdd(ascVec, i);
		VectorAdd(desVec, _numOfItems -i);
	}
	
	timer = clock();
	MergeSort(randVec);
	timeResultRand = (double)(clock() - timer) /CLOCKS_PER_SEC;
	VectorDestroy(randVec);

    timer = clock();
	MergeSort(ascVec);
	timeResultAsc = (double)(clock() - timer) /CLOCKS_PER_SEC;
	VectorDestroy(ascVec);
	
	timer = clock();
	MergeSort(desVec);
	timeResultDes = (double)(clock() - timer) /CLOCKS_PER_SEC;
	VectorDestroy(desVec);
	
	printf("Merge Sort Rand Values     %f\n",  timeResultRand);
	printf("Merge Sort Asc Values      %f\n",  timeResultAsc);
	printf("Merge Sort Des Values      %f\n",  timeResultDes);
	return;
}




