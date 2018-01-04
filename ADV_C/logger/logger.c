/*#include <stdio.h> */         /* FILE* */
#include <stdlib.h>         /* atexit */
#include <pthread.h>        /* pthread_self */
#include <sys/timeb.h>      /* struct timeb */
#include <unistd.h>         /* getpid */
#include <string.h>         /* strcpy */
#include "../../inc/Logger.h"

/*
#pragma​ ​ GCC​ ​ diagnostic​ ​ push
#pragma​ ​ GCC​ ​ diagnostic​ ​ ignored​ ​ "-Wvariadic-macros"

# define MYLOG(FormatLiteral, ...)  fprintf (stderr, "%s(%d): " FormatLiteral "\n", __FILE__, __LINE__, __VA_ARGS__)

#define MYFPRINTF(format, ...) fprintf(_log, format, ## __VA_ARGS__)
*/

#define DEFAULT_NAME "logfile"__DATE__ __TIME__

/*#define LOG_FORMAT "%s %d %d %c %s@%s:%d %s\n"*/
#define LOG_FORMAT "%s %d %d %c %s@%s:%d %s\n"

#define TD_FORMAT "%Y-%m-%d %H:%M:%S"

#define NUM_OF_VERBOSITIES LOG_NONE

struct LogData
{
    Verbosity       m_logLevel;
    Log             m_log;
    char*           m_moduleName;
    int             m_pid;          /* check if it is from int type */
} ;


static LogData* g_log = NULL;


/* TODO write comments */
static LogData* LogCreate(char* _confFileName);

static void LogClose(); 

static void LogDestroy(LogData** g_log);

static LogData* ApplyConfArgs(ConfigData** _configData, LogData* g_log)
{
    int i;
    char ver[] = {'T', 'D', 'I', 'W', 'E', 'C', 'S', 'F'};
    for(i = 0; i < NUM_OF_VERBOSITIES; ++i)
    {
        if((*_configData)->m_verbosity[4] == ver[i])
        {
            (g_log)->m_logLevel = i;
            break;
        }
    }
    if(i == NUM_OF_VERBOSITIES)
    {
        (g_log)->m_logLevel = NUM_OF_VERBOSITIES;
    }
   /* if((*_configData)->m_logName == "0")
    {
        strcpy((*_configData)->m_logName, DEFAULT_NAME);
    }*/
    return g_log;
}

static LogData* LogCreate(char* _confFileName)
{
    LogData* g_log;
    ConfigData* confData;
    
    confData = calloc(1, sizeof(ConfigData));
    if(NULL == confData)
    {
        /* print error note */
        return NULL;
    }
    
    strcpy(confData->m_logName, DEFAULT_NAME);
/*    confData->m_logName = "asdf";*/
    GetConfigData(_confFileName, &confData);
    
    g_log = malloc(sizeof(LogData));
    if(NULL == g_log)
    {
        free(confData);
        /* print error note */
        return NULL;
    }
    
    g_log = ApplyConfArgs(&confData, g_log);
    if(NULL == g_log)
    {
        free(confData);
        /* print error note */
        return NULL;
    }
    
    g_log->m_log = fopen(confData->m_logName, "a+");
    
    free(confData);
    
    return g_log;
}

LogData* LogGet(char* _confFileName)
{
    if(!g_log   )
    {
        g_log = LogCreate(_confFileName);
        atexit(&LogClose);      /* TODO should be part of LogCreate */
    }
    
    return g_log;
}

static void GetTime(char* _dateTime, size_t _size)
{
    time_t t; 
    struct tm* info;
    struct timeb timer_msec;
    unsigned short milli; 

    ftime(&timer_msec);
    milli = timer_msec.millitm; 

    time(&t);
    info = localtime(&t);

    strftime (_dateTime, 32, TD_FORMAT, info);
    sprintf(_dateTime, "%s.%d", _dateTime, milli);
    
    return;
}

/*            WriteLog(log, __FILE__, __LINE__, __func__, level, message)*/

static char GetLevel(Verbosity _level)
{
    char verLevels[] = {'T', 'D', 'I', 'W', 'E', 'C', 'S', 'F', 'N'};
    return verLevels[_level];
}

void LogWrite(LogData* _log, const char* _funcName ,const char* _fileName, int _lineNum, Verbosity _level, char* _message)
{
    char dateTime[32];
    
    if(_log->m_logLevel < _level)
    {
        GetTime(dateTime, 32);
        
        fprintf(_log->m_log, LOG_FORMAT, dateTime, getpid(), (int)pthread_self(), GetLevel(_level), _funcName, _fileName, _lineNum, _message);
    }

}

static void LogClose()
{
    LogDestroy(&g_log);
}

static void LogDestroy(LogData** g_log)
{
    if(g_log)
    {
        fclose((*g_log)->m_log);
        free(*g_log);
        *g_log = NULL;
    }
}


