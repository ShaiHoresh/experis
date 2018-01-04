#include <iostream>

#include "Pqueue.h"

int main()
{
    SafeQueue<std::string> q(5);
    
    std::cout << q.Remove() << std::endl;

    q.Insert("Ido");
    q.Insert("Shai");
    q.Insert("Yaodav");
    
    q.Insert("Ido");
    q.Insert("Shai");
    q.Insert("Yaodav");
    
    std::cout << q.Remove() << std::endl;
    std::cout << q.Remove() << std::endl;
    
    return 0;
}
