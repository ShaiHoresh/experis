#ifndef __CONFIG_H__
#define __CONFIG_H__


typedef struct ConfigData 
{
    char   m_logName[32];
    char   m_verbosity[32];
/*    char*   m_path;*/
}ConfigData;

void GetConfigData(char* _confFileName, ConfigData** _configData);


#endif /* #ifndef __CONFIG_H__ */
