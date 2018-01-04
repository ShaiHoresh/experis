#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include <cstddef>

namespace network
{

struct Message
{
    explicit Message(int);
    
    char* m_data;
    int m_size;
};

inline Message::Message(int _size)
: m_data(new char[_size])
, m_size(_size)
{}

}   //  namespace network

#endif /* __MESSAGE_H__ */

