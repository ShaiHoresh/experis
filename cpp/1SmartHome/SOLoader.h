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
#include <fstream>


class SOLoader
{
public:
    SOLoader(std::string, std::map<std::string, std::ifstream>);
    virtual ~SOLoader ();
    
    void ScanFiles(struct dirent*** _list, std::map<std::string, std::ifstream> _soTypes);
    
private:
    /* data */
    SOLoader(const SOLoader&);
    SOLoader& operator=(const SOLoader&);
};

#endif /* __SO_LOADER_H__ */

