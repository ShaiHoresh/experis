/*
Exercise: 2
----------------
- Create/Destroy special fifo file
- Send bytes from Producer (Ping) to Consumer (Pong)
- Ping sends N messages, Pong reads in a forever loop
- Use usleep() to simulate work load
- Discover how different timing influence number of reads
*/

#include <stdlib.h> /* atoi, abort*/
#include <stdio.h> /*printf, fprintf, stderr, */
#include <sys/types.h> /* mkfifo, open */
#include <sys/stat.h> /* mkfifo, open*/
#include <fcntl.h>
#include <unistd.h> /* fork, usleep, pause, getppid */
       
/*#define PATH /home/shai/work/IPC/pipe*/
#define PERMISSIONS 0777

typedef struct Params
{
    size_t m_cycles;
    size_t m_size;
}Params;

int ParseOptions(Params* _par, int argc, char **argv)
{
    int w;
    
    while ((w = getopt(argc, argv, "c:s:")) != -1)
    {
        switch (w)
        {
            case 'c':
                _par->m_cycles = (size_t)atoi(optarg);
                break;
            case 's':
                _par->m_size = (size_t)atoi(optarg);
                break;
            case '?':
                
            default:
                abort();
        }
    }
    return 1;
}

void FillBuffer(char* _buffer, size_t _size, char _ch)
{
    size_t i;
    for(i = 0; i < _size; ++i)
    {
        _buffer[i] = (char)(_ch + 'a');
    }
}

int main(int argc, char **argv)
{
    int i, fd, numRead, fifoRet;
    char* buffer;
    
    Params par = {26, 15};
    ParseOptions(&par, argc, argv);

    buffer = malloc(par.m_size * sizeof(char));
    if(NULL == buffer)
    {
        printf("buffer malloc failed\n");
        exit(EXIT_FAILURE);
    }
    
    fifoRet = mkfifo("PATH", PERMISSIONS);
    if(fifoRet != 0)
    {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }
    
    fd = open("PATH", O_WRONLY); /* check errors! */

    for(i = 0; i < par.m_cycles; ++i)
    {
        /*usleep(100000);*/
        FillBuffer(buffer, par.m_size, (char)i);
        numRead = (int)write(fd, buffer, par.m_size);
        write(STDOUT_FILENO, buffer, par.m_size);
        if(numRead <= 0)
        {
            perror("write");
            break;
        }
    }
    
    close(fd);
    unlink("PATH");
    
    return 0;
}
