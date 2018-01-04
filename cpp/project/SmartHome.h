#ifndef __SMART_HOME_H__
#define __SMART_HOME_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 

#include <tr1/memory>
#include <vector>
#include <map>
#include <string>

class Parse;
class AgentData;
class Agent;
class Hub;
class SOLoader;

class SmartHome
{
public:
    SmartHome(const std::string& _config, const std::string& _SOpath);
    virtual ~SmartHome();

private:
    void InitAgents(const std::string& _SOpath);

private:
    Parse* m_config;
    SOLoader* m_load;
    std::vector<std::tr1::shared_ptr<AgentData> > m_agentsData;
    std::map<std::string, std::string>* m_funcs;
    std::vector<std::tr1::shared_ptr<Agent> >* m_agents;
    Hub* m_hub;
    void* m_handle;
};

#endif /* __SMART_HOME_H__ */

