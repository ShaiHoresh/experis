#ifndef __SUBJECT_H__
#define __SUBJECT_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 

#include <map>
#include <string>


class Observer;

class Subject 
{
public:
	virtual ~Subject();

    virtual void Attach(Observer* _obs, const std::string& _message);
    virtual void Detach(Observer* _obs, const std::string& _message);
    
    void DeleteAll();
    
    int GetNumOfAcc()const {return m_observers.size();}
    
protected:
	Subject();
	virtual void Notify(const std::string& _whoAmI)=0;
    std::multimap<std::string, Observer*> m_observers; 
};

#endif /* __SUBJECT_H__ */

