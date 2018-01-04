#include "Observer.h"
#include "Subject.h"

Observer::~Observer()
{
    if(m_subj)
    {
        m_subj->Detach(this, m_whoAmI);
    }
}

Observer::Observer(Subject* _subj, const string& _type)
{
    if(_subj)
    {
        m_subj = _subj;
        m_whoAmI = _type;
        m_subj->Attach(this, m_whoAmI);
    }
}
