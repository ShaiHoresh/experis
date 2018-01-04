#include <iostream>

#include "Thread.h"

void foo(int i)
{
    std::cout << "i = " << i << std::endl;
}

class Cat
{
public:
    Cat()
    : m_legs(4)
    {}
    
    void* GetNOS(void*)
    {
        std::cout << m_souls << std::endl;
        return static_cast<void*>(&m_souls);
    }
    
    void SetLegs(std::size_t _new)
    {
        m_legs = _new;
    }
    
private:
    static std::size_t m_souls;
    std::size_t m_legs;
};
    
std::size_t Cat::m_souls = 9;

int main (int argc, char const* argv[])
{
    Cat c;
    advcpp::sync::Thread<Cat> cat(c, &Cat::GetNOS);
    
    cat.Join();
    
    return 0;
}
