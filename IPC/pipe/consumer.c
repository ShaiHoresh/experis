#include <stdlib.h> /* atoi, abort*/
#include <stdio.h> /*printf, fprintf, stderr, */
#include <sys/types.h> /* mkfifo, open */
#include <sys/stat.h> /* mkfifo, open*/
#include <fcntl.h> /* open MACROs */
#include <unistd.h> /* fork, usleep, pause, getppid */
       
/*#define PATH /home/shai/Desktop/work/IPC/pipe*/
#define BUF_SIZE 13 

int main()
{
    int fd, numRead;
    char buffer[BUF_SIZE];
    
    fd = open("PATH", O_RDONLY);

    for(;;)
    {
        usleep(200000);
        numRead = (int)read(fd, buffer, BUF_SIZE);
        if (numRead <= 0)
        {
            break;
        }
        
        printf("recieved: %s\n", buffer);
    }
    close(fd);
    
    return 0;        
}


