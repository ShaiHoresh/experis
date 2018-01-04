#include <tr1/memory>

#include "Sensor.h"
#include "Event.h"
#include "Hub.h"


Sensor::Sensor(Hub* _hub, const std::tr1::shared_ptr<AgentData> _data)
: Agent(_hub, _data)
{}

Sensor::~Sensor()
{}

void Sensor::Publish(std::tr1::shared_ptr<Event> _event)
{
    m_hub->InsertEvent(_event);
}

