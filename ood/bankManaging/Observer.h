#ifndef __OBSERVER_H__
#define __OBSERVER_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 

#include <string>

using namespace std;

class Subject;

class Observer 
{
public:

    virtual	~Observer();
    
    virtual void Update(Subject* _subj) = 0;
    
protected:
    Observer(Subject* _subj, const string& _type);
       
    Subject* m_subj;
    string m_whoAmI;
    
    //add Copy CTOR and op=
};

#endif /* __OBSERVER_H__ */

