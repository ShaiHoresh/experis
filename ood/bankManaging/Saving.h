#ifndef __SAVING_ACCOUNT_H__
#define __SAVING_ACCOUNT_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 

#include <string>
#include <iostream>
#include "AccountImpl.h"

class SavingAcc: public AccountImpl
{
public:
    SavingAcc():AccountImpl(){}
    virtual ~SavingAcc(){}
    
    virtual void Update(){std::cout << "Saving account rsvp" << std::endl;}

private:
    /* data */
};

#endif /* __SAVING_ACCOUNT_H__ */

