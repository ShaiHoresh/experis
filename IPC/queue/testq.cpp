#include <iostream>


#include "Pqueue.h"

int main()
{
    PQueue q(5);
    
    q.Insert(1);
    q.Insert(3);
    q.Insert(2);
    
    std::cout << q.Remove() << std::endl;
    std::cout << q.Remove() << std::endl;
    std::cout << q.Remove() << std::endl;
    
    return 0;
}
