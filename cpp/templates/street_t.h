#ifndef __STREET_T_H__
#define __STREET_T_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 

#include <vector>
#include "building_t.h"



template <class StreetType, class BuildingType>
class Street_t
{
public:
    Street_t();
    Street_t(const Street_t& _street);
    virtual ~Street_t();
    const Street_t& operator=(const Street_t& _bld);
    
    void AddBuilding2Street(const Building_t<BuildingType>* _newBuilding);
    Building_t<BuildingType>* GetBuildingID(const BuildingType _id) const;
    
    void SetStreetID(StreetType& _newName);
    StreetType GetStreetID() const;

private:
    StreetType m_ID;
    std::vector<Building_t<BuildingType>*> m_buildings;
};


template <class StreetType, class BuildingType>
Street_t<StreetType, BuildingType>::Street_t()
{}

template <class StreetType, class BuildingType>
Street_t<StreetType, BuildingType>::Street_t(const Street_t& _street)
{
    m_ID = _street.m_ID;
}

template <class StreetType, class BuildingType>
Street_t<StreetType, BuildingType>::~Street_t()
{}

template <class StreetType, class BuildingType>
const Street_t<StreetType, BuildingType>& Street_t<StreetType, BuildingType>::operator=(const Street_t<StreetType, BuildingType>& _bld)
{
    m_ID = _bld.m_ID;
    return *this;
}

template <class StreetType, class BuildingType>
void Street_t<StreetType, BuildingType>::AddBuilding2Street(const Building_t<BuildingType>* _newBuilding)
{
    m_buildings.insert(m_buildings.end(), _newBuilding);
}

template <class StreetType, class BuildingType>
Building_t<BuildingType>* Street_t<StreetType, BuildingType>::GetBuildingID(const BuildingType _id) const
{
    typename std::vector<Building_t<BuildingType>*>::iterator it = m_buildings.begin();
    
    while((**it).GetBuildingID() != m_ID)
    {
        ++it;
    }
    
    return (*it);
}

template <class StreetType, class BuildingType>
StreetType Street_t<StreetType, BuildingType>:: GetStreetID() const
{
    return m_ID;
}


#endif /* __STREET_StreetType_H__ */

