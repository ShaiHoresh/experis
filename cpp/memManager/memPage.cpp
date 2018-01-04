#include <string.h>
#include <iostream>
using namespace std;

#include "memPage.h"

size_t MemPage_t::m_defCapacity = 16;
//unsigned int MemPage_t::m_numOfPages = 0;

MemPage_t::MemPage_t():MemManager_t()
{
    m_data = new char[m_defCapacity];
//    ++m_numOfPages;
    m_curCapacity = m_defCapacity;
}

MemPage_t::MemPage_t(size_t _size)
{
    m_data = new char[_size];
//    ++m_numOfPages;
    m_curCapacity = _size;
}

MemPage_t::~MemPage_t()
{
   // delete m_data;
}

size_t MemPage_t::Read(void** _buf, unsigned int _size) 
{
    return Read(_buf, m_position, _size);
}



size_t MemPage_t::Read(void** _buf, size_t _pos, unsigned int _size) 
{
    if(_pos > m_used)
    {
        return 0;
    }
    
    if(_pos + _size > m_used)
    {
        _size = (unsigned int)(m_used - _pos);
    }
    
    memcpy(_buf + _pos, m_data, _size);
    m_position += _size;
    
    return _size;
}


size_t MemPage_t::Write(const void* _data, unsigned int _size)
{
    return Write(_data, _size, m_position);
}

size_t MemPage_t::Write(const void* _data, unsigned int _size ,size_t _pos)
{
    if(!_data || _pos > m_used)
    {
        return 0;
    }
    
    if(_pos + _size > m_curCapacity)
    {
        _size = (unsigned int)(m_curCapacity - m_used);
    }

    memcpy(m_data, _data, _size);
    m_position += _size;
    m_used += _size;
    
    return _size;
}

