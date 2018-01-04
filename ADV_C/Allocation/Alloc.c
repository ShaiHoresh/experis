#include <stdlib.h> /* initial malloc, size_t */

#include "Alloc.h"

#define MAGIC 0xDEEDBEEC

typedef struct Chunk
{
    void*           m_next;
    unsigned int    m_magic;
    char            m_data;
} Chunk;

struct Buffer
{
    void*   m_freeSpace;
 /*   size_t  m_interval;*/
};

Buffer* CreateBuffer(size_t _chunkSize, size_t _numOfChunks)
{
    /* declarations */
    Buffer* buffer;
    size_t i, interval;
    size_t location;
    /* check params */
    if(0 == _chunkSize || 0 == _numOfChunks)
    {
        return NULL;
    }
    
    /* allocate big buffer */
    buffer = malloc(_numOfChunks * (_chunkSize + sizeof(Chunk) - sizeof(void*)) + sizeof(Buffer));
    if(!buffer)
    {
        return NULL;
    }
    
    /* initial struct */
/*    buffer->m_interval = _chunkSize + sizeof(Chunk) - sizeof(void*);
*/
    /* initial chunks */
    ((Buffer*)buffer)->m_freeSpace = buffer + sizeof(Buffer);
    
    location = (size_t)&(buffer->m_freeSpace);
    interval = _chunkSize + sizeof(Chunk) - sizeof(void*);
    for(i = 0; i < _numOfChunks; ++i)
    {
        ((Chunk*)location)->m_next = (void*)(location + interval);
        
        ((Chunk*)location)->m_magic = MAGIC;
        location += interval;
    }
    
    /* return buffer */
    return buffer;
}

void* MyMalloc(Buffer* _buffer)
{
    /* declarations */
    void* chunk = NULL;
    /* check buffer */
    if(NULL == _buffer)
    {
        return NULL;
    }
    
    /* update pointers */
    chunk = &(((Chunk*)_buffer->m_freeSpace)->m_data);
    _buffer->m_freeSpace = ((Chunk*)_buffer->m_freeSpace)->m_next;
    
    /* return chunk */
    return chunk;
}

void* MyFree(Buffer* _buffer, void* _chunk)
{
    void* temp;
    if(NULL == _buffer || NULL == _chunk)
    {
        return NULL;
    }
/*    
    if(((Chunk*)_chunk)->m_magic != MAGIC)
    {
        return _buffer;
    }
*/    
    temp = (void*)((size_t)_chunk - (sizeof(Chunk) - sizeof(void*)));
    ((Chunk*)_chunk)->m_next = _buffer->m_freeSpace;
    _buffer->m_freeSpace = temp;
    
    return _buffer;
}

void DestroyBuffer(void* _buffer)
{
    if(NULL != _buffer)
    {
        free(_buffer);
    }
    return;
}




/*  (Buffer*)_buffer->m_freeSpace  */










