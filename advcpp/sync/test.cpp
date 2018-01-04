// protected priority queue

//#include <string>
//#include <iostream>

//#include "SafePQ.h"

//int main (int argc, char const* argv[])
//{
//    advcpp::sync::SafePQ<std::pair<int, std::string> > pq;
//    
//    std::cout << pq.Empty() << std::endl;
//    
//    pq.Push(std::pair<int, std::string>(4, "Yosi"));
//    pq.Push(std::pair<int, std::string>(11, "Gilad"));
//    pq.Push(std::pair<int, std::string>(2, "Ilan"));
//    pq.Push(std::pair<int, std::string>(6, "Rita"));
//    
//    
//    std::cout << pq.Empty() << std::endl;
//    
//    while (!pq.Empty())
//    {
//        std::cout << pq.TopAndPop().second << std::endl;
//    }
//    
//    std::cout << pq.Empty() << std::endl;
//    
//    return 0;
//}

// Thread Test

//#include <iostream>

//#include "Thread.h"

//void foo(int i)
//{
//    std::cout << "i = " << i << std::endl;
//}

//class Cat
//{
//public:
//    Cat()
//    : m_legs(4)
//    {}
//    
//    void* GetNOS(void*)
//    {
//        std::cout << m_souls << std::endl;
//        return static_cast<void*>(&m_souls);
//    }
//    
//    void SetLegs(std::size_t _new)
//    {
//        m_legs = _new;
//    }
//    
//private:
//    static std::size_t m_souls;
//    std::size_t m_legs;
//};
//    
//std::size_t Cat::m_souls = 9;

//int main (int argc, char const* argv[])
//{
//    Cat c;
//    advcpp::sync::Thread<Cat> cat(c, &Cat::GetNOS);
//    
//    cat.Join();
//    
//    return 0;
//}

#include "ThreadPool.h"
#include "Task.h"
#include <unistd.h>
#include <stdexcept>



class Example: public advcpp::Task
{
public:
    Example (){}
//    ~Example (){}
    void Set(int _i)
    {
        m_nothing = _i;
    }
    virtual void Go()
    {
        std::cout << "Example::Go No. " << m_nothing << std::endl;
        sleep(2);
    }

private:
    int m_nothing;
};

class Nothing: public advcpp::Task
{
public:
    Nothing(){}
    
    void Set(int _i)
    {
        m = _i;
    }
    virtual void Go()
    {
        std::cout << "Nothing::Go No. " << m << std::endl;
        sleep(3);
    }
    int m;
};

#define NUMOFTHREADS 50
int main (int argc, char const* argv[])
{
    advcpp::sync::ThreadPool pool(8);
    
    std::tr1::shared_ptr<Example> arrEx[NUMOFTHREADS];
//    std::tr1::shared_ptr<Nothing> arrNo[30];
    try{
        for (unsigned int i = 0; i < NUMOFTHREADS; ++i)
        {
            arrEx[i] = std::tr1::shared_ptr<Example> (new Example);
//            arrNo[i] = std::tr1::shared_ptr<Nothing> (new Nothing);
            
            arrEx[i]->Set(i);
//            arrNo[i]->Set(i * i);

            pool.Add(i, arrEx[i]);
//            pool.Add(i * i, arrNo[i]);
        }
        sleep(5);
    } catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
//    
//    pool.Resize(15);
//    
//    
//    try{
//        for (unsigned int i = 50; i < 100; ++i)
//        {
//            arrEx[i] = std::tr1::shared_ptr<Example> (new Example);
////            arrNo[i] = std::tr1::shared_ptr<Nothing> (new Nothing);
//            
//            arrEx[i]->Set(i);
////            arrNo[i]->Set(i * i);

//            pool.Add(i, arrEx[i]);
////            pool.Add(i * i, arrNo[i]);
//        }
//    } catch (std::exception& e)
//    {
//        std::cout << e.what() << std::endl;
//    }    
    
    pool.Shutdown();
//    pool.BruteShutdown();
//    pool.FullyGracefulShutdown();
    
    return 0;
}

