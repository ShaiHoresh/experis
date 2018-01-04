#include <list>
#include <vector>
#include <iostream>
#include <algorithm>

void Print(int i)
{
    std::cout << i << " ";
}

struct Sum
{
    Sum():s(0){}
    int operator()(int i) 
    {
        s += i;
        return s;
    }
    int s;
};

int main (int argc, char const* argv[])
{
    std::list<int> cont;
    std::vector<int> vec;
    
    for (unsigned int i = 0; i < 10; ++i)
    {
        cont.push_back(i);
        vec.push_back(i);
    }
    
    std::cout << "\nvector:" << std::endl;
    for_each(vec.begin(), vec.end(), Print);
    std::cout << std::endl;
    Sum s = for_each(vec.begin(), vec.end(), Sum());
    std::cout << s.s << std::endl;
    
    std::cout << "\nlist:" << std::endl;
    for_each(cont.begin(), cont.end(), Print);
    std::cout << std::endl;
    Sum s1 = for_each(cont.begin(), cont.end(), Sum());
    std::cout << s1.s << std::endl;
    
    return 0;
}

