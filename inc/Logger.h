#ifndef __LOGER_H__
#define __LOGER_H__

/** 
 *  @file Logger.h
 *  @brief Log generator, to be implanted in source codes to create a log file during running.
 *	
 *  @author Shai Horesh (shihoresh@gmail.com)
 * 
 *  @bug No bug known
 */

#include <stdio.h> /* FILE* */
#include "../ADV_C/logger/config.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wvariadic-macros"

#define WRITELOG(log, level, message, ...) \
            sprintf(message, __VA_ARGS__); \
            LogWrite(log, __FUNCTION__, __FILE__, __LINE__, level, message)

#pragma GCC diagnostic pop

typedef struct LogData LogData;
typedef FILE* Log;

typedef enum
{
    LOG_TRACE = 0,
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_CRITICAL,
    LOG_SEVERE,
    LOG_FATAL,
    LOG_NONE
} Verbosity;


/**
 * @brief Get a log to write new data to.
 * @param[in] none
 * @return Log stream.
 */
LogData* LogGet(char* _confFileName);
 
/**
 * @brief write needed data in desired format.
 * @param[in] _log - given from LogGet function
 * @param[in] _funcName function name - use macro __FUNCTION
 * @param[in] _fileName file name - use macro __FILE__
 * @param[in] _lineNum line num - use macro __LINE__
 * @param[in] _module module name
 * @param[in] _message relevant message
 */
void LogWrite(LogData* _log, const char* _funcName ,const char* _fileName, int _lineNum, Verbosity _level, char* _message);

#endif /* #ifndef __LOGER_H__ */
