#include <dirent.h>
#include <cstdlib>
#include <dlfcn.h>

#include "SOLoader.h"

typedef void(*Tell)(std::map<std::string, std::string>*);

SOLoader::SOLoader(const std::string& _path, std::map<std::string, std::string>* _funcs)
: m_funcs(_funcs)
//, m_handle(0)
{
    
    struct dirent **namelist;
    
    int sos = scandir((char*)_path.c_str(), &namelist, 0, alphasort);

    std::string name; // RAII
    while(sos--)
    {
        name = "./SOs/";
        name += (namelist[sos]->d_name);
        if(namelist[sos]->d_name[0] == '.')
        {
            free(namelist[sos]);
            continue;
        }
        
        void* handle = dlopen(name.c_str(), RTLD_NOW);
        if(0 == handle)
        {
            throw "dlopen failed";
        }
        Tell tell = (Tell)dlsym(handle, "Tell");
        if(0 == tell)
        {
            throw "dlsym failed";
        }
        tell(m_funcs);
        dlclose(handle);
        free(namelist[sos]);
    }
    free(namelist);
}

SOLoader::~SOLoader()
{
//    if(m_handle)
//    {
//        dlclose(m_handle);
//    }
}

