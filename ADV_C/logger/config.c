#include <stdio.h>
#include <string.h>

#include "config.h"


void GetConfigData(char* _confFileName, ConfigData** _configData)
{
    FILE* fdConfig;
    char name[32], value[32], buffer[64];
    
    
    fdConfig = fopen(_confFileName, "r");
    if(NULL == fdConfig)
    {
        return;
    }
   
    while(NULL != fgets(buffer, 63, fdConfig))
    {
        sscanf(buffer,"[ \n%[^] \n ]", name);
        if(0 == strcmp(name, "#"))
        {
            while(NULL != fgets(buffer, 63, fdConfig))
            {        
                sscanf(buffer, " \n%[^ =] = %[^ \n ]", name, value);
                if(strcmp(name, "File") == 0)
                {
                    strcpy((*_configData)->m_logName, value);
                }
                if(strcmp(name, "Level") == 0)
                {
                    strcpy((*_configData)->m_verbosity, value);
                }
    /*
                if(strcmp(name, "Path") == 0)
                {
                    _configData.m_path;
                }
    */
            }
        }
    }

    printf("%s %s\n", (*_configData)->m_logName, (*_configData)->m_verbosity);

    fclose(fdConfig);
    return;
}
