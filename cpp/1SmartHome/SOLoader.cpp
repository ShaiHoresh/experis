#include <dirent.h>
#include <dlfcn.h>//dynamic loading
#include <unistd.h>//chdi
#include <vector>
#include <iostream>
#include <string>



#include "SOLoader.h"

typedef void(*GetFuncs)(std::vector<std::string>*);

SOLoader::SOLoader(std::string _path, std::map<std::string, std::ifstream> _soTypes)
{
    
/*    if( 0 != chdir(m_path.c_str()))
    {
        throw("chdir failed");
    }
*/    
    struct dirent **namelist;
    if(scandir(".", &namelist, NULL, alphasort) == -1) 
    {
        throw("scandir failed");
    }
    
    ScanFiles(&namelist, _soTypes);
}

void SOLoader::ScanFiles(struct dirent*** _list, std::map<std::string, std::ifstream> _soTypes)
{
    for (int i = 0; i < 10; i += 1)
    {
        std::cout << (*_list[i])->d_name << std::endl;;
        if((std::string)(*_list[i])->d_name != "." && (std::string)_list[i]->d_name != "..")
        {
           GetFuncNames (m_TypeName,_list[i]->d_name);
        }
        delete(_list[i]);

    }
}
