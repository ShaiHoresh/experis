#include "Hub.h"



Hub::Hub()
{

}


Hub::~Hub ();

void Hub::InsertToHubsQ(const Event& _event)
{
    Event* event = new Event;
    event = _event;             //TODO make it safer...
    m_EventQ.Push(event);
}

void Hub::PublishEvent();

bool Hub::Subscribe(Agent* _agent);

static void* Publish(Hub* _hub);

void Hub::Notify(const Event& _event)
{
    for(std::map<Agent*, std::string>::iterator it = m_map.begin(); it != m_map.end(); ++it)
    {
        if(it->second == _event.m_type)
        {
            
        }
    }
}




/*
m_map.insert(std::pair<Agent*, std::string>())

{
	for (std::map<Agent*,EventListener*>::iterator it=m_EventSender.begin(); it!=m_EventSender.end(); ++it)
	{
		if(it->second->IsRelevantEvent(_event))
		{
			it->second->SendEvent( _event);	
		}	
	}
}

*/
