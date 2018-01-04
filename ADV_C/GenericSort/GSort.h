#ifndef __GSORT_H__
#define __GSORT_H__

#include "ADTDefs.h" /* Error definitions*/
#include <stddef.h> /* size_t */

typedef int (*SortingType)(const void*, const void*);

ADTErr GenericBubbleSort(void* _elements, size_t _numOfElements, size_t _blockSize, SortingType _isSwapNeeded);



#endif /* __GSORT_H__ */
