#ifndef __PERSON_H__
#define __PERSON_H__

#include <string>
using namespace std;

class Person
{
public:
    Person(const string _id, const string _name, const string _phone);
    virtual ~Person ();
    
    string GetName() const;
    string GetID() const;
    string GetPhone() const;
    
    Person& operator<(const Person& _per) const;

private:
    /* data */
    string m_name;
    string m_id;
    string m_phone;
    
    Person(const Person& _per);
    Person& operator=(const Person& _per);
};

#endif /* __PERSON_H__ */

