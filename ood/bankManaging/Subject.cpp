#include <map>
#include <string>

#include "Subject.h"
#include "Observer.h"



using namespace std;

Subject::Subject()
{
}

Subject::~Subject() {}

void Subject::Attach(Observer* _obs, const string& _message)
{
    if(_obs)
    {
        m_observers.insert(pair<string, Observer*>(_message, _obs));
    }
}


void Subject::Detach(Observer* _obs, const string& _message)
{
    m_observers.erase(_message); 
}

void Subject::DeleteAll()
{
    for(multimap<string, Observer*>::iterator it = m_observers.begin(); it != m_observers.end(); ++it)
    {
        delete it->second;
    }
}



/*    multimap<string, Observer*> m_observers; 
*/
