#ifndef __BUILDING_T_H__
#define __BUILDING_T_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 

template <class T>
class Building_t
{
public:
    Building_t<T>(T& _id);
    Building_t(const Building_t& _bld);
    virtual ~Building_t<T>();
    const Building_t<T>& operator=(const Building_t<T>& _bld);
    
    void SetBuildingID(const T& _newID);
    const T GetBuildingID() const;

private:
    T m_ID;
};

template <class T>
Building_t<T>::Building_t(T& _id)
{
    m_ID = _id;
}

template <class T>
Building_t<T>::Building_t(const Building_t& _bld)
{
    m_ID = _bld.GetBuildingID();
}

template <class T>
Building_t<T>::~Building_t()
{}

template <class T>
const Building_t<T>& Building_t<T>::operator=(const Building_t<T>& _bld)
{
    m_ID = _bld.GetBuildingID();
    return *this;
}


template <class T>
void Building_t<T>::SetBuildingID(const T& _newID)
{
    m_ID = _newID;
}

template <class T>
const T Building_t<T>::GetBuildingID() const
{
    return m_ID;
}

#endif /* __BUILDING_T_H__ */

