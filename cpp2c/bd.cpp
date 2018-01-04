#include <iostream>

class B
{
public:
    inline virtual void foo() {std::cout << "B's foo" << std::endl;}
    void baz() {std::cout << "B's baz" << std::endl;}
    
//    int a;
};

class D: public B
{
public:
    inline virtual void foo() {std::cout << "D's foo" << std::endl;}
    void baz() {std::cout << "D's baz" << std::endl;}
};

int main()
{
    B b, *pb1, *pb2;
    D d, *pd1, *pd2;
    
    pb1 = &b;
    pb2 = &d;
    pd1 = &d;
    
    
    b.foo();
    pb1->foo();
    pb2->foo();
    ((B)d).foo();
    
    b.baz();
    pb2->baz();
    
    
    std::cout << ((pb2 == pd1) ? "true" : "false") << std::endl;
    
    std::cout << &pb2 << std::endl;
    std::cout << &pd1 << std::endl;
    
    return 0;
}
