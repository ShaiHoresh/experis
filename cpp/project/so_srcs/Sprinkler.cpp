#include <ctime>
#include <cstdlib>
#include <iostream>

#include "Sprinkler.h"
#include "ICreator.h"
#include "IHub.h"

Sprinkler::Sprinkler(std::tr1::shared_ptr<AgentData> _data, Hub* _hub):
Agent(_hub, _data)
{
    m_hub->Subscribe(this);
}

Sprinkler::~Sprinkler()
{
}

bool Sprinkler::IsRelevant(const std::tr1::shared_ptr<Event> _event)
{
    return _event->GetTopic() == "Fire";
}
        
        
void Sprinkler::GetEvent(const std::tr1::shared_ptr<Event> _event)
{
    std::cout << "Sprinkler got event: " << _event->GetTopic() << std::endl;
}

void Tell(std::map<std::string, std::string>* m_funcs)
{
    m_funcs->insert(std::pair<std::string, std::string>("Sprinkler", "Sprinkler.so"));
}

void* CreateAgent(std::tr1::shared_ptr<AgentData> _data, std::string _type, Hub* _hub)
{
    if(_type == "Sprinkler")
    {
        Sprinkler* sprinkler = new Sprinkler(_data, _hub);
        return (void*)sprinkler;
    }
    return 0;
}







