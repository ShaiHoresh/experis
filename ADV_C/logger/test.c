#include "../../inc/Logger.h"
#include <unistd.h>

int main()
{
    int i, j;
    LogData* log;
    char message[1024];
    for(i = 1; i <= 10; ++i)
    {
        log = LogGet("config1.txt");
        WRITELOG(log, LOG_FATAL, message, "I was here %d times", i);  
    }
    for(j = 1; j <= 10; ++j)
    {
        log = LogGet("config.txt");
        WRITELOG(log, LOG_TRACE, message, "I was here %d times", j);  
    }
    return 0;
}
