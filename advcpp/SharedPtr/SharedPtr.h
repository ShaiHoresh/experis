#ifndef __SHARED_PTR_H__
#define __SHARED_PTR_H__

#include <stdexcept>

namespace advcpp
{

template <class T>
class SharedPtr
{
public:
    explicit SharedPtr(T* _t = 0);
    SharedPtr(const SharedPtr&);
    SharedPtr& operator=(const SharedPtr&);
    ~SharedPtr();
    
    
    T& operator*() const;
    T* operator->() const;
    
    bool operator==(const SharedPtr&) const;

    bool operator!=(const SharedPtr&) const;
    
    T* Get() const;
    
    std::size_t Count() const;

    template <class D>
    friend class SharedPtr;
    
    template <class D>
    explicit SharedPtr(const SharedPtr<D>&);
    
    template <class D>
    SharedPtr& operator=(const SharedPtr<D>&);
    
    template <class D>
    bool operator==(const SharedPtr<D>& _other) const;
    
    template <class D>
    bool operator!=(const SharedPtr<D>& _other) const;
    
private:
    T* m_ptr;
    std::size_t* m_counter;
    
private:
    void HandleDec();
    static std::size_t*(*GetCounter[2])();
    static std::size_t* Dummy();
    static std::size_t* RealOne();
};

template <class T>
std::size_t* SharedPtr<T>::Dummy()
{
    return 0;
}

template <class T>
std::size_t* SharedPtr<T>::RealOne()
{
/*    try*/
/*    {*/
/*        std::size_t* temp = new std::size_t(1);*/
/*    }*/
/*    throw*/
    return new std::size_t(1);
}

template <class T>
std::size_t*(*SharedPtr<T>::GetCounter[])() = {Dummy, RealOne};

 
/*void(*_N9Scaleable_6vTable[])(void) = {(void(*)(void))_N9Scaleable_DTOR, (void(*)(void))_N9Scaleable_N5Scale_DOUBLE};*/

/*template <class T>*/
/*SharedPtr<T>::SharedPtr()*/
/*: m_ptr(0)*/
/*, m_counter(0)*/
/*{}*/

template <class T>
SharedPtr<T>::SharedPtr(T* _t)
: m_ptr(_t)
, m_counter(GetCounter[static_cast<bool>(_t)]())/*(try*/
/*            {*/
/*                GetCounter[static_cast<bool>(_t)]();*/
/*            }*/
/*            catch(...)*/
/*            {*/
/*                delete _t;*/
/*            }*/
/*            )*/
{}

template <class T>
SharedPtr<T>::SharedPtr(const SharedPtr& _t)
: m_ptr(_t.m_ptr)
, m_counter(_t.m_counter)
{
    if(!m_counter)
    {
        m_counter = RealOne();
    }
    __sync_fetch_and_add(m_counter, 1);
}

template <class T>
template <class D>
SharedPtr<T>::SharedPtr(const SharedPtr<D>& _t)
: m_ptr(_t.m_ptr)
, m_counter(_t.m_counter)
{
    if(!m_counter)
    {
        m_counter = RealOne();
    }
    __sync_fetch_and_add(m_counter, 1);
}
    
template <class T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& _t)
{
    if(this == &_t)
    {
        return *this;
    }

    HandleDec();
    
    m_ptr = _t.m_ptr;
    m_counter = _t.m_counter;

    __sync_fetch_and_add(m_counter, 1);
    
    return *this;
}

template <class T>
template <class D>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<D>& _t)
{
    if(*this == _t)
    {
        return *this;
    }

    HandleDec();
    
    m_ptr = _t.m_ptr;
    m_counter = _t.m_counter;

    __sync_fetch_and_add(m_counter, 1);
    
    return *this;
}

template <class T>
SharedPtr<T>::~SharedPtr()
{
    HandleDec();
}

template <class T>
inline void SharedPtr<T>::HandleDec()
{
    if(m_counter)
    {
        if(!__sync_fetch_and_sub(m_counter, 1))
        {
            delete m_counter;
            delete m_ptr;
        }
    }
}

template <class T>
inline T& SharedPtr<T>::operator*() const
{
    return *m_ptr;
}

template <class T>
inline T* SharedPtr<T>::operator->() const
{
    return m_ptr;
}

template <class T>
inline bool SharedPtr<T>::operator==(const SharedPtr& _other) const
{
    return m_ptr == _other.m_ptr;
}

template <class T>
template <class D>
inline bool SharedPtr<T>::operator==(const SharedPtr<D>& _other) const
{
    return m_ptr == _other.m_ptr;
}

template <class T>
inline bool SharedPtr<T>::operator!=(const SharedPtr& _other) const
{
    return !(*this == _other);
}

template <class T>
template <class D>
inline bool SharedPtr<T>::operator!=(const SharedPtr<D>& _other) const
{
    return m_ptr != _other.m_ptr;
}


template <class T>
inline std::size_t SharedPtr<T>::Count() const
{
    return *m_counter;
}

template <class T>
inline T* SharedPtr<T>::Get() const
{
    return m_ptr;
}


} // namespace advcpp

#endif /* __SHARED_PTR_H__ */

