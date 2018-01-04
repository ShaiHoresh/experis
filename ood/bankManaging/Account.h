#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 
#include <string>


#include "Observer.h"

class AccountImpl;

class Account: public Observer
{
public:
    Account(Subject* _subj, const std::string& _accType); 
    virtual ~Account();

    virtual void Update(Subject* _subj); 
    
private:
    AccountImpl* m_account;
    std::string m_type;
    
    Account& operator=(const Account& _acc);
    Account(const Account& _acc);
};

#endif /* __ACCOUNT_H__ */

