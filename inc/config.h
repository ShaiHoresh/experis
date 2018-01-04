#ifndef __CONFIG_H__
#define __CONFIG_H__


typedef struct ConfigData /*remove to config.h*/
{
    char*   m_logName;
    char*   m_verbosity;
/*    char*   m_path;*/
}ConfigData;

void GetConfigData(char* _confFileName, ConfigData** _configData);


#endif /* #ifndef __CONFIG_H__ */
