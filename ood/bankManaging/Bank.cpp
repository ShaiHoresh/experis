#include <string>
#include <iostream>


#include "Bank.h"
#include "Account.h"


using namespace std;

Bank Bank::m_bank;

Bank::~Bank()
{
    DeleteAll();
}

void Bank::Destroy()
{
    DeleteAll();
}

bool Bank::OpenAccount(const string& _type)
{
    try
    {
        new Account(this, _type); 
    }
    catch(const char* str)
    {
        std::cout << "Failed" << std::endl;
        return false;
    }
    
    
    return true;
}

void Bank::Notify(const string& _whoAmI)
{
    std::pair <multimap<string, Observer*>::iterator, multimap<string, Observer*>::iterator> ret;
    ret = m_observers.equal_range(_whoAmI);
    for (multimap<string, Observer*>::iterator it = ret.first; it != ret.second; ++it)
    {
        it->second->Update(this);
    }

}

void Bank::GiveBonus()
{
    Notify("Family");
}

void Bank::Invest()
{
    Notify("Stock");
}

void Bank::Meeting()
{
    Notify("Saving");
}
