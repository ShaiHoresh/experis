#include <iostream>
using namespace std;

#include "memManager.h"

MemManager_t::MemManager_t()
: m_position(0), m_used(0)
{}

MemManager_t::~MemManager_t()
{}

bool MemManager_t::SetPosition(size_t _pos)
{
    if(_pos <= m_used)
    {
        m_position = m_used;
        return true;
    }
    throw "invalid position";
//    return false;
}
