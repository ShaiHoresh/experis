#ifndef __ACCOUNT_IMPL_H__
#define __ACCOUNT_IMPL_H__

#include <string>

class AccountImpl
{
public:
    AccountImpl(){}
    virtual ~AccountImpl(){}

    virtual void Update() = 0;
    
private:
    AccountImpl(const AccountImpl& _accImpl);
    void operator=(const AccountImpl& _accImpl);
};

#endif /* __ACCOUNT_IMPL_H__ */

