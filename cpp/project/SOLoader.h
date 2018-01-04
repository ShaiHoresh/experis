#ifndef __SO_LOADER_H__
#define __SO_LOADER_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 

#include <string>
#include <map>


class SOLoader
{
public:
    SOLoader(const std::string& _path, std::map<std::string, std::string>* _funcs);
    virtual ~SOLoader();
    
private:
    std::map<std::string, std::string>* m_funcs;
/*    void* m_handle;*/
};

#endif /* __SO_LOADER_H__ */

