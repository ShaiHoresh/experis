#include <vector>
#include <iostream>
#include <fstream>

#include "AgentData.h"
#include "Parse.h"

Parse::Parse(const std::string& _confName, std::vector<std::tr1::shared_ptr<AgentData> >* _agentsData)
{
    if(!_agentsData)
    {
        throw "vector uninitialized";
    }
    
    m_agentsData = _agentsData;
    m_file.open(_confName.c_str(), std::ifstream::in);
    //error handling
    
    while(m_file.good())
    {
        ParseAgentData();
    }
    m_file.close();
}

void Parse::ParseAgentData()
{
    std::tr1::shared_ptr<AgentData> agent(new AgentData);
    
    std::string line;
    getline(m_file, line);
    while(m_file.good() && !line.empty())
    {
        AnalyzeLine(agent, line);   //TODO take care to false value returned from func
        getline(m_file, line);
    }
    
    if(!IsValid(agent))
    {
//        TODO throw an exception / write to log
    }
    else
    {
        m_agentsData->push_back(agent);
    }
}

bool Parse::AnalyzeLine(std::tr1::shared_ptr<AgentData> _agent, std::string& _line)
{
    std::string token = " = ";
    if(_line[0] == '[')
    {
        _agent->m_id = _line.substr(1, _line.length() - 2);
        return true;
    }
     
    std::string cat = _line.substr(0, _line.find(token));
    _line.erase(0, _line.find(token) + token.size());
    
    if(cat == "type")
    {
        _agent->m_type = _line;
    }
    else if(cat == "room")
    {
        _agent->m_room = _line;
    }
    else if(cat == "floor")
    {
        _agent->m_floor = _line;
    }
    else if(cat == "log")
    {
        _agent->m_log = _line;
    }
    else if(cat == "config")
    {
        _agent->m_config = _line;
    }
    else
    {
        return false;
    }

    return true;
}

bool Parse::IsValid(std::tr1::shared_ptr<AgentData> _agent)
{
    if(_agent->m_type.empty() || _agent->m_room.empty() || _agent->m_floor.empty())
    {
        return false;
    }
    
    return true;
}

