#ifndef __SORTS_H__
#define __SORTS_H__


#include "vector.h"
#include "stack.h"

typedef int (*SortingType)(int, int); /*TODO document*/
typedef int (*FindKey)(void*, int);

ADTErr BubbleSort(Vector* _vec);

ADTErr ShakeSort(Vector* _vec);

ADTErr QuickSortRec(Vector* _vec);

ADTErr QuickSortIterative(Vector* _vec);

ADTErr InsertionSort(Vector* _vec, SortingType _isSwapNeeded);

ADTErr ShellSort(Vector* _vec, SortingType _isSwapNeeded);

ADTErr SelectionSort(Vector* _vec);

ADTErr MergeSort(Vector* _vec);

ADTErr MergeSortRec(Vector* _vec);

ADTErr CountingSort(Vector* _vec, int _maxValue, FindKey _keyFunc, int _key);

/*implemented on base 10*/
ADTErr RadixSort(Vector* _vec, int _nDigits, FindKey _keyfunc);

int WholeNumber(void* _number, int _key);
/*{
    return (int)_number;
}
*/
int Digit(void* _number, int _key);
/*{
    return (((int)_number / (int)pow(10, _key - 1)) % 10);
}*/


#endif /*__SORTS_H__*/
