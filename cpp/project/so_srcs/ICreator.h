#ifndef __ICREATOR_H__
#define __ICREATOR_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 

#include <tr1/memory>

#include <string>
#include <map>

class AgentData;
class Hub;

extern "C" void Tell(std::map<std::string, std::string>* m_funcs);
extern "C" void* CreateAgent(std::tr1::shared_ptr<AgentData> _data, std::string _type, Hub* _hub);

#endif /* __ICREATOR_H__ */

