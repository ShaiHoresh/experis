#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "ADTDefs.h"

typedef struct Vector Vector;


/* size   - The initial allocation size.
  blockSize - The extention block size.  */

Vector* VectorCreate(size_t _initialSize, size_t _extensionBblockSize);

void VectorDestroy (Vector* _vector);

/* Add item to end. */
ADTErr VectorAdd(Vector *_vector, int _item);

/* Delete item from the end. */
ADTErr VectorDelete (Vector *_vector, int* _item);

/* Retrieve value from vector in place _index to item*/
ADTErr VectorGet(Vector *_vector, size_t _index, int *_item);
ADTErr VectorSet(Vector *_vector, size_t _index, int _item);
ADTErr VectorItemsNum(Vector *_vector, int* _numOfItems);
/* Unit-Test functions */

void VectorPrint(Vector *_vector);

#endif /* __VECTOR_H__ */
