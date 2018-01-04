#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <poll.h>

#define EVENT_SIZE  (sizeof (struct inotify_event))
#define EVENT_BUF_LEN     (1024 * (EVENT_SIZE + 16))

void* Detect(char* _path, char** _fileName)
{
    int fd = 0, wd = 0, length = 0, i = 0;
    struct inotify_event *event = NULL;
    char buffer[EVENT_BUF_LEN];
    
    fd = inotify_init();
    if(fd < 0)
    {
        return NULL;
    }
    
    wd = inotify_add_watch(fd, _path, IN_CREATE | IN_MOVED_TO);
    
    length = read(fd, buffer, EVENT_BUF_LEN); 

    if(length < 0)
    {
        return NULL;
    }
        
    while(i < length) 
    {
        event = (struct inotify_event *) &buffer[i];
        if(event->len)
        {
            sprintf(*_fileName, "%s", event->name);
        }
        i += EVENT_SIZE + event->len;
    }
    
    inotify_rm_watch(fd, wd);

    close(fd);
    
    return _fileName;
}
