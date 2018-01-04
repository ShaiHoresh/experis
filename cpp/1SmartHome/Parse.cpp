#include <vector>
#include <iostream>
#include <fstream>

#include "AgentData.h"

using namespace std;


class Parse
{
public:
    Parse(const std::string&);
    
private:
    bool AnalyzeLine(AgentData* _agent, std::string& _line);
    void ParseAgentData();
    bool IsValid(AgentData* _agent);

private:    
    std::ifstream m_file;
};


Parse::Parse(const std::string& _confName)
{
    m_file.open(_confName.c_str(), std::ifstream::in);
    std::string line;
    
    int i = 0;
    while(m_file.good())
    {
        cout << i++ << ": ";
        ParseAgentData();
    }
    
}

void Parse::ParseAgentData()
{
    std::string line;
    AgentData* agent = new AgentData;
    
    getline(m_file, line);
    while(m_file.good() && !line.empty())
    {
        AnalyzeLine(agent, line);
        getline(m_file, line);
    }
    
    if(!IsValid(agent))
    {
        cout << '\t' << agent->m_id << " deleted\n";
        delete agent;
        // TODO throw an exception
    }
    /*
    else
    {
        push to container
    }
    */
}

bool Parse::AnalyzeLine(AgentData* _agent, std::string& _line)
{
    std::string token = " = ";
    if(_line[0] == '[')
    {
        _agent->m_id = _line.substr(1, _line.length() - 2);
        cout << _agent->m_id << std::endl;
        return true;
    }
     
    std::string cat = _line.substr(0, _line.find(token));
    _line.erase(0, _line.find(token) + token.size());
    
    if(cat == "type")
    {
        _agent->m_type = _line;
        //cout << _agent->m_type << std::endl;
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

bool Parse::IsValid(AgentData* _agent)
{
    if(_agent->m_type.empty() || _agent->m_room.empty() || _agent->m_floor.empty())
    {
        return false;
    }
    
    return true;
}

int main()
{
    Parse("config.txt");
    return 0;
}
