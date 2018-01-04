//#include <iostream>
//#include "SharedPtr.h"

//using namespace advcpp;

//class Dog
//{
//public:
//    static const int m_legs = 4;
//    static const int m_mouth = 1;
//};

//int main (int argc, char const* argv[])
//{
//    
//    
//    SharedPtr<int> first(new int);
//    std::cout << "counter 1: " << first.Count() << std::endl;
//    SharedPtr<int> second = first;
//    SharedPtr<int> third;
//    
//    third = first;
//    
//    SharedPtr<int> FIRST(new int), SECOND(FIRST);
//    
//    SECOND = first;
//    
//    SharedPtr<Dog> dog(new Dog);
//    std::cout << "the dog has " << dog->m_legs << " legs" << std::endl;
//    std::cout << "the dog has " << (*dog).m_mouth << " mouth" << std::endl;
//    
//    if(second == first)
//    {
//        std::cout << "== works" << std::endl;
//        SharedPtr<int> ScopeIp(new int);
//        std::cout << "in ScopeIp: " << ScopeIp.Count() << std::endl;
//    }
//    
//    SharedPtr<int> ScopeIp(new int);
//    std::cout << "out ScopeIp: " << ScopeIp.Count() << std::endl;
//    
//    if(FIRST != first)
//    {
//        std::cout << "!= works" << std::endl;
//    }
//    
//    std::cout << "counter 1: " << first.Count() << std::endl;
//    std::cout << "counter 2: " << FIRST.Count() << std::endl;
//    
//    return 0;
//}

#include <memory>
#include <vector>
#include <unistd.h>
#include <pthread.h>
#include <iostream>

#include "SharedPtr.h"
#include "mu_test.h"

using namespace advcpp;

void* CreadHundredPtr(SharedPtr<int>* _a)
{
    std::vector< SharedPtr<int> > ptrs;
    for(unsigned int i = 0; i < 1000; ++i)
    {
        ptrs.push_back(*_a);
    }
    
    pause();
    
    return 0;
}

void* assignHundredPtr(SharedPtr<int>* _a)
{
    SharedPtr<int> newPtr(new int(0));
    std::vector< SharedPtr<int> > ptrs;
    for(unsigned int i = 0; i < 1000; ++i)
    {
        ptrs.push_back(newPtr);
    }
    
    for(unsigned int i = 0; i < 1000; ++i)
    {
        ptrs[i] = *_a;
    }
    
    pause();
    
    return 0;
}

/*----------------------------------*/

UNIT(COPY_CTOR)

SharedPtr<int> ptr(new int(1));
pthread_t* threads = new pthread_t[100];
for(unsigned int i = 0; i < 100; ++i)
{
    pthread_create(threads + i, 0, (void* (*)(void *))CreadHundredPtr, &ptr);
}

sleep(2);

ASSERT_THAT(100001 == ptr.Count());

for(unsigned int i = 0; i < 100; ++i)
{
    pthread_cancel(threads[i]);
    pthread_join(threads[i], 0);
}

ASSERT_THAT(1 == ptr.Count());

delete[] threads;

END_UNIT

/*----------------------------------*/

UNIT(assignment_operator)

SharedPtr<int> ptr(new int(1));
pthread_t* threads = new pthread_t[100];
for(unsigned int i = 0; i < 100; ++i)
{
    pthread_create(threads + i, 0, (void* (*)(void *))assignHundredPtr, &ptr);
}

sleep(2);

ASSERT_THAT(100001 == ptr.Count());

for(unsigned int i = 0; i < 100; ++i)
{
    pthread_cancel(threads[i]);
    pthread_join(threads[i], 0);
}

ASSERT_THAT(1 == ptr.Count());

delete[] threads;

END_UNIT

/*----------------------------------*/

UNIT(derefrence_operator)

SharedPtr<int> ptr(new int(1));
*ptr = 2;
ASSERT_THAT(2 == *ptr);

END_UNIT

/*----------------------------------*/

UNIT(arrow_operator)

SharedPtr< SharedPtr<int> > ptr(new SharedPtr<int>(new int(1)));
ASSERT_THAT(1 == ptr->Count());

END_UNIT

/*----------------------------------*/

//UNIT(operator_bool)

//SharedPtr<int> a(0);
//ASSERT_THAT(!a);

//SharedPtr<int> b(new int(1));
//ASSERT_THAT(b);

//END_UNIT

/*----------------------------------*/

UNIT(operator_equal)

SharedPtr<int> a(0);
SharedPtr<int> b(a);

ASSERT_THAT(a == b);

SharedPtr<int> c(new int(0));
ASSERT_THAT(a != c);

END_UNIT

class Base
{
public:
    int a;
    Base(int _in = 3):a(_in){}    
};
class Derived: public Base
{
public:
    int b;
    Derived(int _in = 3):Base(), b(_in){}    

};
UNIT(base_derived)

SharedPtr<Derived> pd(new Derived(5));
ASSERT_THAT(pd->b == 5 && pd->a == 3);

SharedPtr<Base> pb(new Derived(5));
pb = pd;

SharedPtr<Base> pq(new Derived(4));

ASSERT_THAT(pd == pd);
ASSERT_THAT(pb != pq);
END_UNIT

TEST_SUITE(sharedPtr)

    TEST(COPY_CTOR)
    TEST(assignment_operator)
    TEST(derefrence_operator)
    TEST(arrow_operator)
//    TEST(operator_bool)
    TEST(operator_equal)
    TEST(base_derived)

END_SUITE
