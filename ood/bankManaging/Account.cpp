#include "AccountFactory.h"
#include "Bank.h"

#include "Account.h"
#include "AccountImpl.h"
#include "Observer.h"


using namespace std;

Account::Account(Subject* _subj, const string& _accType):Observer((Subject*)_subj, _accType)
{
    m_account = AccountFactory::Create(_accType);
    if(!m_account)
    {
        throw("Failed");
    }
    m_type = _accType;
    
//    m_subj->Attach(this, m_type);
}

Account::~Account()
{
    delete m_account;
    m_account = 0;
    
//    m_subj->Detach(this, m_type);
}

void Account::Update(Subject* _subj)
{
    if(_subj)
    {
        m_account->Update();
    }
}
