#ifndef __PARSE_H__
#define __PARSE_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 

#include <tr1/memory>
#include <fstream>

class Parse
{
public:
    Parse(const std::string& _confName, std::vector<std::tr1::shared_ptr<AgentData> >* _agentsData);
    
private:
    bool AnalyzeLine(std::tr1::shared_ptr<AgentData> _agent, std::string& _line);
    void ParseAgentData();
    bool IsValid(std::tr1::shared_ptr<AgentData> _agent);

private:    
    std::ifstream m_file;
    std::vector<std::tr1::shared_ptr<AgentData> >* m_agentsData;
};


#endif /* __PARSE_H__ */

