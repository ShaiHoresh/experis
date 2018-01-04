#ifndef __T_CONTAINERS2_H__
#define __T_CONTAINERS2_H__

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

template<class T, template <class, class a = allocator<T> > class Container>
class tContainers
{
public:
    typedef typename Container<T, allocator<T> >::const_iterator iter_t;
    typedef typename Container<T, allocator<T> >::iterator nc_iter_t;

    tContainers(){};
    virtual ~tContainers (){};
    
    bool Empty() const  
    {
        return m_container.empty();
    };
    
    size_t Size() const 
    {
        return m_container.size();
    };
        
    void PushBack(T& _element)
    {
        m_container.insert(m_container.end(), _element);
    };
    
    T* First() const
    {
        return Empty() ? m_container.begin() : 0;
    };
    
    T* Last() const
    {
        return Empty() ? m_container.end() : 0;
    };
    
    T Find(const T _element) const
    {
        if(Empty())
        {
            return 0;
        }
        iter_t it = find_if(m_container.begin(), m_container.end(), Compare(_element));
        return *it;
    };
    
    T Remove(T _element)
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
        T ret = *it;
       
        m_container.erase(it);
        
        return ret;
    };
    
    void RemoveAll()
    {
        m_container.clear();
    };
    
    void RemoveDelete(T _element)
    {
        /*delete */Remove(_element);
    };
    
    void RemoveDeleteAll()
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
    };
    
    T operator[](const size_t _index) const
    {
        if(typeid(Container<T, allocator<T> >) == typeid(vector<T*>))
        {
            vector<T*>* vec = (vector<T*>*) &m_container;
            
            return *(*vec)[_index];
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
        return *it;
    };

    class Compare
    {
        public:
            Compare(T _val):
            val(_val){}
            
        bool operator()(const T _param)const
        {
            return (val == _param);
        }
        
        T val;
    };

private:
    /* data */
    tContainers(const tContainers& _cont);
    tContainers& operator=(const tContainers& _cont);
    
    Container<T, allocator<T> > m_container;
    
};



#endif /* __T_CONTAINERS2_H__ */

