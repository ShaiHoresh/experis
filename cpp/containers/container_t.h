#ifndef __CONTAINER_T_H__
#define __CONTAINER_T_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 

template <class ConType>
class Container_t
{
public:
    Container_t();
    Container_t(const Container_t& _con);
    virtual Container_t& operator=(const Container_t& _con);
    virtual ~Container_t ();
    
    virtual bool Append(const ConType* _con, int _index) = 0;
    virtual bool Prepend(const ConType* _con, int _index) = 0;
    virtual bool Insert(const ConType* _con) = 0;

    virtual bool Contains(ConType _con) const = 0;
    virtual ConType* Find(ConType _con) const = 0;
    virtual int Index(ConType _con) const = 0;

    unsigned int Count() const;
    bool IsEmpty() const;

    virtual ConType* Remove(ConType _con);
    virtual void RemoveAll();
/*    
    virtual void RemoveAndDelete(ConType _con);
    virtual void RemoveAndDeleteAll();*/

protected:
    /* data */
    int m_numOfElements;
};

template <class ConType>
Container_t<ConType>::Container_t()
{
    m_numOfElements = 0;
}

template <class ConType>
Container_t<ConType>& Container_t<ConType>::operator=(const Container_t<ConType>& _con)
{
    m_numOfElements = _con.m_numOfElements;
    
    return *this;
}

template <class ConType>
Container_t<ConType>::~Container_t()
{}

template <class ConType>
unsigned int Container_t<ConType>::Count() const
{
    return m_numOfElements;
}

template <class ConType>
bool Container_t<ConType>::IsEmpty() const
{
    return m_numOfElements == 0;
}

#endif /* __CONTAINER_T_H__ */

