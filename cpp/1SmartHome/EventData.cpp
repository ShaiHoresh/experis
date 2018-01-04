#include <ctime>
#include <sstream>
#include "EventData.h"


Event::Event(const AgentData* _data)
{
    m_type = _data->m_type;
    m_floor = _data->m_floor;
    m_room = _data->m_room;
    
    
    time_t t = time(0);
    struct tm* now = localtime(&t);
    std::stringstream timeStamp;
    timeStamp << now->tm_hour << "::" << now->tm_min << "::" << now->tm_sec;
    m_time = timeStamp.str();
    
    m_payload = "shalom";
}

Event::Event(const Event& _event)
{
    m_time = _event.m_time;
    m_type = _event.m_type
    m_floor = _event.m_floor;
    m_room = _event.m_room;
    m_payload = _event.m_payload;
}
