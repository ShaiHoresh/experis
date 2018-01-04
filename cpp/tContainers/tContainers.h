#ifndef __T_CONTAINERS_H__
#define __T_CONTAINERS_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 

#include <vector>
#include <list>
#include <typeinfo>


#include <cstddef>
#include <algorithm>

using namespace std;


//template<typename T, template <typename S> class Collection>  template< T*>

template <class T, class Container>
class tContainers
{
public:
    typedef typename Container::const_iterator iter_t;
    typedef typename Container::iterator nc_iter_t;

    tContainers();
    virtual ~tContainers ();
    
    bool Empty() const;
    size_t Size() const;
    
    void PushBack(T& _element);
    
    T* First() const;
    T* Last() const;
    T* Find(const T _element) const;
    
    T* Remove(T _element);
    void RemoveAll();
    void RemoveDelete(T _element);
    void RemoveDeleteAll();
    
    T operator[](const size_t _index) const;

    class Compare
    {
        public:
            Compare(T _val):
            val(_val){}
            
        bool operator()(const T* _param)const
        {
            return (val == *_param);
        }
        
        T val;
    };

private:
    /* data */
    tContainers(const tContainers& _cont);
    tContainers& operator=(const tContainers& _cont);
    
    Container m_container;
    
};

template <class T, class Container>
tContainers<T, Container>::tContainers()
{}

template <class T, class Container>
tContainers<T, Container>::~tContainers()
{}

template <class T, class Container>
bool tContainers<T, Container>::Empty() const
{
    return m_container.empty();
}

template <class T, class Container>
size_t tContainers<T, Container>::Size() const
{
    return m_container.size();
}

template <class T, class Container>
void tContainers<T, Container>::PushBack(T& _element)
{
    m_container.insert(m_container.end(), &_element);
}

template <class T, class Container>
T* tContainers<T, Container>::First() const
{
    return Empty() ? m_container.begin() : 0;
}

template <class T, class Container>
T* tContainers<T, Container>::Last() const
{
    return Empty() ? m_container.end() : 0;
}

template <class T, class Container>
T* tContainers<T, Container>::Find(const T _element) const
{
    if(Empty())
    {
        return 0;
    }
    iter_t it = find_if(m_container.begin(), m_container.end(), Compare(_element));
    return *it;
}



template <class T, class Container>
T* tContainers<T, Container>::Remove(T _element)
{
    if(Empty())
    {
        return 0;
    }
    nc_iter_t it = find_if(m_container.begin(), m_container.end(), Compare(_element)); 
    
    if(it == m_container.end())
    {
        return 0;
    }
    T* ret = *it;
   
    m_container.erase(it);
    
    return ret;
}

template <class T, class Container>
void tContainers<T, Container>::RemoveAll()
{
    m_container.clear();
}


template <class T, class Container>
void tContainers<T, Container>::RemoveDelete(T _element)
{
    delete Remove(_element);
}


template <class T, class Container>
void tContainers<T, Container>::RemoveDeleteAll()
{
    if(Empty())
    {
        return;
    }
    
    nc_iter_t it = m_container.begin();
    while(it != m_container.end() && *it != 0)
    {
        m_container.erase(it);
        ++it;
    }
    
    m_container.clear();
}

template <class T, class Container>
T tContainers<T, Container>::operator[](const size_t _index) const
{
    if(typeid(Container) == typeid(vector<T*>))
    {
        return *(*(vector<T*>*) &m_container)[_index];
    }
    
    size_t size = m_container.size();
    if(size < _index)
    {
        return 0;
    }
    
    iter_t it = m_container.begin();
    for(size_t i = 0; i < _index; ++i)
    {
        ++it;
    }
    return **it;
}

#endif /* __T_CONTAINERS_H__ */

