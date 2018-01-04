#ifndef __Buffer_H__
#define __Buffer_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 

#include <cstddef>
//#include <tr1/memory>


namespace advcpp
{

template <class T>
class Buffer
{
public:
    explicit Buffer(std::size_t _initSize = 8);
    explicit Buffer(const T&, std::size_t);
    Buffer(const Buffer&);
    virtual ~Buffer();
    
    Buffer& operator=(const Buffer&);
    
    inline T* GetData() const;
    
    inline std::size_t GetCapacity() const;
    inline std::size_t GetSize() const;

private:
    T* m_data;      // change to shared_ptr  -  std::tr1::shared_ptr
    std::size_t m_capacity;
    std::size_t m_size;
};

template <class T>
Buffer<T>::Buffer(std::size_t _initSize)
: m_capacity(_initSize), 
m_size(0)
{
    m_data = new T[_initSize];
}

template <class T>
Buffer<T>::Buffer(const T& _data, std::size_t _size)
: m_capacity(_size)
, m_size(_size)
{
    if(_data)
    {
        m_data = new T[_size];
        memcpy(m_data, &_data, _size);
    }
}


template <class T>
Buffer<T>::Buffer(const Buffer& _other)
: m_capacity(_other.m_capacity)
, m_size(_other.m_size)
{
    m_data = new T[_other.m_capacity];
    m_data = _other.m_data;
}

template <class T>
Buffer<T>::~Buffer()
{
    delete[] m_data;
}

template <class T>
Buffer<T>& Buffer<T>::operator=(const Buffer& _other)
{
    if(this != &_other)
    {
        m_data = new T[_other.m_capacity];
        memcpy(m_data, _other.m_data, _other.m_size);
        m_capacity = _other.m_capacity;
        m_size = _other.m_size;
    }
    
    return *this;
}

template <class T>
T* Buffer<T>::GetData() const
{
    return m_data;
}

template <class T>
std::size_t Buffer<T>::GetCapacity() const
{
    return m_capacity;
}

template <class T>
std::size_t Buffer<T>::GetSize() const
{
    return m_size;
}


} // namespace advcpp
#endif /* __Buffer_H__ */











