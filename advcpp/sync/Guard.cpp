#include "Guard.h"

namespace advcpp
{

namespace sync
{




Guard::Guard(Mutex* _mutex)
: m_mutex(_mutex)
{
    m_mutex->Lock();
}

Guard::~Guard()
{
    try
    {
        m_mutex->Unlock();
    }
    catch(...)
    {}
}



} // namespace sync
} // namespace advcpp
