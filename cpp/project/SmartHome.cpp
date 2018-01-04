#include <unistd.h>
#include <dlfcn.h>

#include "SmartHome.h"
#include "AgentData.h"
#include "Agent.h"
#include "Hub.h"
#include "Parse.h"
#include "SOLoader.h"




SmartHome::SmartHome(const std::string& _config, const std::string& _SOpath)
: m_handle(0)
{
    m_hub = new Hub;
    m_agents = new std::vector<std::tr1::shared_ptr<Agent> >;
    m_config = new Parse(_config, &m_agentsData);
    m_funcs = new std::map<std::string, std::string>;
    m_load = new SOLoader(_SOpath, m_funcs);
    InitAgents(_SOpath);
}

SmartHome::~SmartHome()
{
    delete m_agents;
    delete m_hub;
    delete m_funcs;
    delete m_config;
    delete m_load;
    if(m_handle)
    {
        dlclose(m_handle);
    }
}

typedef void*(*Create)(std::tr1::shared_ptr<AgentData> _data, std::string _type, Hub* _hub);

//Factory!!!
void SmartHome::InitAgents(const std::string& _SOpath)
{
    std::string so;
//    void* handle;
    for(unsigned int i = 0; i < m_agentsData.size(); ++i)
    {
        so = _SOpath;
        so += m_funcs->find(m_agentsData[i]->m_type)->second;
        
        m_handle = dlopen(so.c_str(), RTLD_LAZY);
        //handle error
        Create create = (Create)dlsym(m_handle, "CreateAgent");
        //handle error
        std::tr1::shared_ptr<Agent>  agent((Agent*)create(m_agentsData[i], m_agentsData[i]->m_type.c_str(), m_hub));
        //handle error
        m_agents->push_back(agent);
    }
    
//    dlclose(handle);
}
