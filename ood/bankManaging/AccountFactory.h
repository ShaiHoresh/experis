#ifndef __ACCOUNT_FACTORY_H__
#define __ACCOUNT_FACTORY_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 

/*
    includes and forward declration
*/
#include <string>
#include "AccountImpl.h"
#include "Family.h"
#include "Saving.h"
#include "Stock.h"


class Account;
using namespace std;


class AccountFactory
{
public:
    static AccountImpl* Create(const string& _type)
    {
        AccountImpl* account = 0;
        if(_type == "Family")
        {
            account = new FamilyAcc;
        }
        else if(_type == "Saving")
        {
            account = new SavingAcc;
        }
        else if(_type == "Stock")
        {
            account = new StockAcc;
        }
        
        if(account)
        {
            return account;
        }
        return 0;
    }
    
    static void Destroy(AccountImpl* _account)
    {
        // detach??
        delete _account;
    }

private:
    AccountFactory();
    AccountFactory(const AccountFactory&);
    AccountFactory& operator=(const AccountFactory&);
};

#endif /* __ACCOUNT_FACTORY_H__ */

