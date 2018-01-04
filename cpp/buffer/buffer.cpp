#include <string.h>

#include "buffer.h"

// static fields declaration
const unsigned int DEFCAPACITY = 16;
size_t Buffer::defCapacity = DEFCAPACITY;

// auxiliary func
char* Buffer::CreateFrom(const char* _buf, const size_t _size)
{
    _size > 0 ? size = _size : size = strlen(_buf);
    myCapacity = size;
    
    while(size > myCapacity)
    {
        myCapacity *= 2;
    }
    
    if(size > defCapacity)
    {
        delete[] buffer;
    }
    buffer = new char[myCapacity];
    
    if(0 == buffer)
    {
        //TODO
    }
    strncpy(buffer, _buf, size);
    
    return buffer;
}

// constractors
Buffer::Buffer(const size_t _size)
{
    size = _size;
    buffer = new char[_size];
    if (0 == buffer)
    {
        //TODO
    }
    memset(buffer, '0', _size);
}

Buffer::Buffer(const char* _array, size_t _size)
{
    CreateFrom(_array, _size);
}

Buffer::Buffer(const char* _src)
{
    CreateFrom(_src);
}

Buffer::Buffer(const Buffer& _buf)
{
    if(this != &_buf)
    {
        CreateFrom(_buf.buffer);
    }
}

// assignment operator
const Buffer& Buffer::operator=(const Buffer& _buf)
{
    if(this != &_buf)
    {
        CreateFrom(_buf.buffer);
    }
    return *this;
}

// destractor
Buffer::~Buffer()
{
    delete[] buffer;
}

int Buffer::Set(const char* _new)
{
    if(_new)
    {
        CreateFrom(_new);
        return 1;
    }
    
    return 0;
}

const char* Buffer::ReSize(const size_t _newSize)
{
    char* newBuffer = new char[_newSize];
    if (0 == newBuffer)
    {
        //TODO
    }
    
    memcpy(newBuffer, buffer, _newSize);
    delete[] buffer;
    buffer = newBuffer;
    
    if(_newSize > myCapacity)
    {
        memset(buffer + myCapacity, '0', _newSize - myCapacity);
    }
    
    myCapacity = _newSize;
    size = strlen(buffer);
    
    return buffer;
}

char& Buffer::operator[](const size_t _index)
{
    if(_index < size)
    {
        char& rc = buffer[_index];
        return rc;
    }
    else
    {
        char null = '\0';
        char& rc = null;
        return rc;
    }
}

const char& Buffer::operator[](const size_t _index) const
{
    if(_index < size)
    {
        char& rc = buffer[_index];
        return rc;
    }
    else
    {
        char null = '\0';
        char& rc = null;
        return rc;
    }
}






