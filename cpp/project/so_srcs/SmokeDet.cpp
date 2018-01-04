#include <unistd.h>
#include <iostream>

#include "SmokeDet.h"
#include "ICreator.h"
#include "IHub.h"

SmokeDet::SmokeDet(std::tr1::shared_ptr<AgentData> _data, Hub* _hub)
:Sensor(_hub, _data)
{
    pthread_create(&m_thread, 0, PublishEv, (void*)this);
}


SmokeDet::~SmokeDet()
{
    pthread_cancel(m_thread);
    pthread_join(m_thread, 0);
}

void* SmokeDet::PublishEv(void* _object)
{
    ((SmokeDet*)_object)->CreateEvent();
    return 0;
}

void SmokeDet::CreateEvent()
{
    while(true)
    {
        sleep(3);
        std::tr1::shared_ptr<Event> event(new Event("Fire"));
        std::cout << "SmokeDet: Fire detected" << std::endl;
        Publish(event);
    }
}

bool SmokeDet::IsRelevant(const std::tr1::shared_ptr<Event>& _event)
{
    return true;
}
        
void SmokeDet::GetEvent(const std::tr1::shared_ptr<Event>& _event)
{}

void Tell(std::map<std::string, std::string>* m_funcs)
{
    m_funcs->insert(std::pair<std::string, std::string>("SmokeDet", "SmokeDet.so"));
}

void* CreateAgent(std::tr1::shared_ptr<AgentData> _data, std::string _type, Hub* _hub)
{
    if(_type == "SmokeDet")
    {
        SmokeDet* smokeDet = new SmokeDet(_data, _hub);
        return (void*)smokeDet;
    }
    return 0;
}







