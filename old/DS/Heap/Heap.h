#ifndef __HEAP_H__
#define __HEAP_H__

#include "vector.h"
#include "ADTDefs.h"

typedef struct Heap Heap;

/* The function takes the vector and inverts it to a Heap Tree
input: vector
output: pointer to a Heap Tree
errors: if either the vector is NULL or the allocation of the heap failes - the function will return NULL     */
Heap* HeapBuild(Vector* _vec);

/* The function destroy the struct of the heap
input: pointer to heap
output: none
errors: none                                    */
void HeapDestroy(Heap* _heap);

/* The function inserts a new node to a heap and puts it in place
input: pointer to heap and the data (an integer)
output: ERR_OK if succeeded
errors: ERR_NOT_INITIALIZED if the heap not exist
        ERR_INSERT_FAILED if can't add the node*/
ADTErr HeapInsert(Heap* _heap, int _data);

/* The function retrieves the biggest number in heap
input: pointers to the heap and to a variable to save the data in the heap
output: the data "saved" in _data, ERR_OK return
errors: ERR_NOT_INITIALIZED if either heap or _data doesn't exist*/
ADTErr HeapMax(Heap* _heap, int* _data);

/* The function pops the biggest num in the heap and re-arrange the heap
input: pointers to the heap and to a variable to save the max number in the heap
output: the max value "saved" in _data, ERR_OK return
errors: ERR_NOT_INITIALIZED if either heap or _data doesn't exist*/
ADTErr HeapExtractMax(Heap* _heap, int* _data);

/* The function retrieves the number of element in heap
input: pointer to the heap
output: return the number of elements in heap
errors: if heap doesn't exist*/
size_t HeapItemsNum(Heap* _heap);

void HeapPrint(Heap* _heap);

#endif /*#ifndef __HEAP_H__*/
