#include <iostream>

#include "SmartHome.h"

int main (int argc, char const* argv[])
{
    SmartHome* sh = new SmartHome(argv[1], argv[2]);
    
    int a;
    std::cin >> a;
    
    delete sh;
    
    return 0;
}

