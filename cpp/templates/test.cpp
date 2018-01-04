#include <iostream>
#include <cstring>

//#include "building_t.h"
#include "street_t.h"



int main()
{
    int x = 5, y = 3;
    Building_t<int> bld(x), bld2(y);
    std::cout << "Hi" << std::endl;

    std::cout << bld2.GetBuildingID() << std::endl;    
    bld2 = bld;
    std::cout << bld2.GetBuildingID() << std::endl;
    
    Street_t<int, int> street();
    street.AddBuilding2Street(&bld);
    
    std::cout << street.SetStreetID(&x) << std::endl;
    
    return 0;
}
