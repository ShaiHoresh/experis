#ifndef __AGENT_DATA_H__
#define __AGENT_DATA_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 


class AgentData
{
public:
    AgentData();

    std::string  m_id;
    std::string  m_type;
    std::string  m_floor;
    std::string  m_room;
    std::string  m_log;
    std::string  m_config;
};

AgentData::AgentData()
:m_id(""), m_type(""), m_floor(""), m_room(""), m_log(""), m_config("")
{}



#endif /* __AGENT_DATA_H__ */

