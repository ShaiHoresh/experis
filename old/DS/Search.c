#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define ARR_SIZE 500000

int LinearSearch(int* _array, int _numOfItems, int _numToSearch);
int LinearSearchImproved(int* _array, int _numOfItems, int _numToSearch);
int LinearSearchImprovedAndPull(int* _array, int _numOfItems, int _numToSearch);
int BinarySearch(int* _array, int _numOfItems, int _numToSearch);
int ProportionalSearch(int* _array, int _numOfItems, int _numToSearch);
int JumpSearch(int* _array, int _numOfItems, int _numToSearch);

int main()
{
    int unsorted[ARR_SIZE], su[11] = {1,3,5,7,9,11,13,15,17,19};
    int sorted[10] = {1, 4, 6, 8, 12, 15, 34, 45, 76, 89};
    /*int sorted[ARR_SIZE];*/
    int i, result;
    clock_t timer;
    double timeResult, sum = 0;
    
	srand(time(NULL));
    
    sum = 0;
    printf("found? %d\n", ProportionalSearch(sorted, 10, 3));
  /*  printf("Proportional search average time of %f sec\n", sum);*/
 /*   for(i = 0; i < ARR_SIZE - 1; ++i)
    {
        unsorted[i] = rand() % 250000;
    }
    
    for(i = 0; i < ARR_SIZE; ++i)
    {
        sorted[i] = i * (rand() % 10 + 1);
    }    */

/*    for(i = 0; i < 100; ++i)
    {
	    timer = clock();
	    LinearSearch(unsorted, ARR_SIZE, rand() % 100);
	    timeResult = (double)(clock() - timer) /CLOCKS_PER_SEC;
	    sum += timeResult;
    }
    printf("Linear search average time of %f sec\n", sum / i);
    
    sum = 0;
    for(i = 0; i < 100; ++i)
    {
	    timer = clock();
        LinearSearchImproved(unsorted, ARR_SIZE, rand() % 100);
	    timeResult = (double)(clock() - timer) /CLOCKS_PER_SEC;
	    sum += timeResult;
    }
    printf("Linear search Improved average time of %f sec\n", sum / i);
    
    sum = 0;
    for(i = 0; i < 1000000; ++i)
    {
	    timer = clock();
	    LinearSearchImprovedAndPull(unsorted, ARR_SIZE, rand() % 100);
	    timeResult = (double)(clock() - timer) /CLOCKS_PER_SEC;
	    sum += timeResult;
    }
    printf("Linear search Improved And Pull average time of %f sec\n", sum / i);
*/    

/*    for(i = 0; i < 1; ++i)
    {
	    timer = clock();
        JumpSearch(sorted, ARR_SIZE, rand() % ARR_SIZE);
	    timeResult = (double)(clock() - timer) /CLOCKS_PER_SEC;
	    sum += timeResult;
    }*/
/*
    for(i = 0; i < 22; ++i)
    {
        printf("prop:   looking for %2d - ", i);
        result = ProportionalSearch(su, 10, i);
        printf("is it found: %d\n", result);
    }

    sum = 0;
    for(i = 0; i < 100; ++i)
    {
	    timer = clock();
        BinarySearch(sorted, ARR_SIZE, rand() % ARR_SIZE);
	    timeResult = (double)(clock() - timer) /CLOCKS_PER_SEC;
	    sum += timeResult;
    }
    printf("Binary search average time of %f sec\n", sum);
*/
    return 0;
}

int LinearSearch(int* _array, int _numOfItems, int _numToSearch)
{
    size_t i;
    for(i = 0; i < _numOfItems; ++i)
    {
        if(_array[i] == _numToSearch)
        {
            return 1;
        }
    }
    return 0;
}

int LinearSearchImproved(int* _array, int _numOfItems, int _numToSearch)
{
    size_t i = 0;
    _array[_numOfItems] = _numToSearch;
    while(1)
    {
        /*insert the value to search in the end of the array
            
        */
        if(_array[i] == _numToSearch)
        {
            break;
        }
        ++i;
    }
    if(i == _numOfItems)
    {
        return 0;
    }
    return 1;
}

int LinearSearchImprovedAndPull(int* _array, int _numOfItems, int _numToSearch)
{
    size_t i = 0, temp;
    _array[_numOfItems] = _numToSearch;
    while(1)
    {
        if(_array[i] == _numToSearch)
        {
            break;
        }
        ++i;
    }
    if(i == _numOfItems)
    {
        return 0;
    }
    if(i > 0)
    {
        temp = _array[i];
        _array[i] = _array[i / 10];
        _array[i / 10] = temp;
    }
    return 1;
}

int ProportionalSearch(int* _array, int _numOfItems, int _numToSearch)
{
    int minVal, minIndex, maxVal, maxIndex, index;
    
    minIndex = 0;
    maxIndex = _numOfItems - 1;
    while(maxIndex >= minIndex)
    {
        index = (int)(((float)(_numToSearch - _array[minIndex]) / (_array[maxIndex] - _array[minIndex])) * (maxIndex - minIndex + 1) * 0.9) + minIndex;
        if(_array[index] == _numToSearch)
        {
            return 1;
        }

        if(_array[index] < _numToSearch)
        {
            minIndex = index + 1;
        }
        else
        {
            maxIndex = index - 1;
        }
    }
    return 0;
}

int JumpSearch(int* _array, int _numOfItems, int _numToSearch)
{
    size_t cur, root;
    
    root = (int)sqrt((double)_numOfItems);
    cur = root;
    
    if(_array[0] == _numToSearch)
    {
        return 1;
    }
    
    while(cur <= _numOfItems && root > 0)
    {
        printf("%d, ", _array[cur]);
        if(_array[cur] == _numToSearch)
        {
            return 1;
        }
        else if(_array[cur] < _numToSearch)
        {
            cur += root;
        }
        else
        {
            if(root == 1)
            {
                break;
            }
            cur = cur - root + (int)sqrt((double)root);
            root = sqrt(root);
            printf("\n");
        }
        if(cur == 0)
        {
            break;
        }
    }
    return 0;
}

int BinarySearch(int* _array, int _numOfItems, int _numToSearch)
{
    int minIndex, maxIndex, midIndex;
    
    minIndex = 0;
    maxIndex = _numOfItems;
    
    midIndex = (maxIndex + minIndex) / 2;
    
    if(_array[0] == _numToSearch)
    {
        return 1;
    }
    
    while(maxIndex > midIndex && midIndex > minIndex)
    {
        if(_array[midIndex] == _numToSearch)
        {
            return 1;
        }
        else if(_array[midIndex] < _numToSearch)
        {
            minIndex = midIndex;
            midIndex = (maxIndex + midIndex) / 2;
        }
        else
        {
            maxIndex = midIndex;
            midIndex = (minIndex + midIndex) / 2;
        }
    }
    
    return 0;
}








