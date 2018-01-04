#ifndef __VECTOR_H__
#define __VECTOR_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 

#include "container_t.h"

template <class VecType>
class Vector: public Container_t<VecType>
{
public:
    Vector(int _size = 4, int _ext = 4);
    Vector(const Vector& _con);
    virtual Vector& operator=(const Vector& _con);
    virtual ~Vector ();
    
    virtual bool Append(const VecType* _con, int _index);
    virtual bool Prepend(const VecType* _con, int _index);
    virtual bool Insert(const VecType* _con);

    virtual bool Contains(VecType _con) const;
    virtual VecType* Find(VecType _con) const;
    virtual int Index(VecType _con) const;

    virtual VecType* Remove(VecType _con);
    virtual void RemoveAll();
/*    
    virtual void RemoveAndDelete(VecType* _con);
    virtual void RemoveAndDeleteAll();*/
    
private:
    VecType** m_array;
    int m_capacity;
    int m_ext;
    
private:
    void Copy(VecType** _src);
    void Extend();
    void ShiftRight(int _index);
    void ShiftLeft(int _index);
};

template <class VecType>
Vector<VecType>::Vector(int _size, int _ext)
{
    m_array = new VecType*[_size];
    m_ext = _ext;
    m_capacity = _size;
}

template <class VecType>
Vector<VecType>::~Vector()
{
    delete[] m_array;
}

template <class VecType>
Vector<VecType>& Vector<VecType>::operator=(const Vector<VecType>& _con)
{
    m_ext = _con.m_ext;
    m_capacity = _con.m_capacity;
    
    Container_t<VecType>::operator=(_con);
    
    m_array = new VecType*[m_capacity];
    
    for(int i = 0; i < _con.m_numOfElements; ++i)
    {
        m_array[i] = _con.m_array[i];
    }
    
    return *this;
}

template <class VecType>
bool Vector<VecType>::Append(const VecType* _con, int _index)
{
    if(_index > this->m_numOfElements)
    {
        return false ;
    }
    
    if(this->m_numOfElements == m_capacity)
    {
        Extend();
    }
    
    ShiftRight(_index);
    m_array[_index] = (int*)_con;
    this->m_numOfElements++;
    
    return true;
}

template <class VecType>
bool Vector<VecType>::Prepend(const VecType* _con, int _index)
{
    if(_index > this->m_numOfElements)
    {
        return false ;
    }
    
    if(this->m_numOfElements == m_capacity)
    {
        Extend();
    }
    
    ShiftRight(_index - 1);
    m_array[_index] = (int*)_con;
    this->m_numOfElements++;
    
    return true;
}

template <class VecType>
bool Vector<VecType>::Insert(const VecType* _con)
{
    return Append(_con, this->m_numOfElements);
}

template <class VecType>
bool Vector<VecType>::Contains(VecType _con) const
{
    for(int i = 0; i < this->m_numOfElements; ++i)
    {
        if(*m_array[i] == _con)
        {
            return true;
        }
    }
    
    return false;
}

template <class VecType>
VecType* Vector<VecType>::Find(VecType _con) const
{
    for(int i = 0; i < this->m_numOfElements; ++i)
    {
        if(*m_array[i] == _con)
        {
            return m_array[i];
        }
    }
    
    return 0;
}

template <class VecType>
int Vector<VecType>::Index(VecType _con) const
{
    for(int i = 0; i < this->m_numOfElements; ++i)
    {
        if(*m_array[i] == _con)
        {
            return i;
        }
    }
    
    return -1;
}

template <class VecType>
void Vector<VecType>::Extend()
{
    VecType** vector = new VecType*[m_capacity + m_ext];
    if(!vector)
    {
        //  TODO something
    }
    for(int i = 0; i < this->m_numOfElements; ++i)
    {
        vector[i] = m_array[i];
    }
    delete[] m_array;
    m_array = vector;
}

template <class VecType>
void Vector<VecType>::ShiftRight(int _index)
{
    if(_index > this->m_numOfElements)
    {
        return;
    }
    
    for(int i = this->m_numOfElements; i > _index && i > 0; --i)
    {
        m_array[i] = m_array[i - 1];
    }
}

template <class VecType>
void Vector<VecType>::ShiftLeft(int _index)
{
    if(_index > this->m_numOfElements)
    {
        return;
    }
    
    for(int i = this->m_numOfElements; i > _index && i > 0; --i)
    {
        m_array[i - 1] = m_array[i];
    }
}


template <class VecType>
void Vector<VecType>::Remove(VecType _con)
{
    VecType* ret = 0;
    for(int i = 0; i < this->m_numOfElements; ++i)
    {
        if(*m_array[i] == _con)
        {
            ret = m_array[i];
            ShiftLeft(i);
        }
    }
    
    return ret;
}

/*

    virtual void Remove(VecType* _con);
    virtual void RemoveAll();
    
    virtual void RemoveAndDelete(VecType _con);
    virtual void RemoveAndDeleteAll();
*/















#endif /* __VECTOR_H__ */

