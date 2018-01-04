#ifndef __ALLOC_H__
#define __ALLOC_H__

#include <stdio.h> /* size_t */

typedef struct Buffer Buffer;

Buffer* CreateBuffer(size_t _chunkSize, size_t _numOfChunks);

void* MyMalloc(Buffer* _buffer);

void* MyFree(Buffer* _buffer, void* _chunk);

void DestroyBuffer(void* _buffer);

#endif /* #ifndef __ALLOC_H__ */
