/*
Exercise:1
----------------
- Send bytes from Producer (parent) to Consumer (child)
- Producer sends N messages, Consumer reads in a forever loop
- Use usleep() to simulate work load
- Discover how different timing influence number of reads
*/
#include <stdlib.h> /* atoi, abort*/
#include <stdio.h> /*printf, fprintf, stderr, */
#include <unistd.h> /* fork, usleep, pause, getppid */
#include <sys/wait.h> /* waitpid */

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

void FullBuffer(char* _buffer, size_t _size, char _ch)
{
    size_t i;
    for(i = 0; i < _size; ++i)
    {
        _buffer[i] = (char)(_ch + 'a');
    }
}

void ChildReadBufferAndPrint(int* pfd, char* buffer, Params par)
{        
    int numRead;
    close(pfd[1]);
    printf("\nin child process\n");
    for(;;)
    {
        usleep(100000);
        numRead = read(pfd[0], buffer, par.m_size);
        if (numRead <= 0)
        {
            break;
        }
        write(STDOUT_FILENO, buffer, (size_t)numRead);
        write(STDOUT_FILENO, "\n", 1);
    }
    write(STDOUT_FILENO, "\n", 1);
    close(pfd[0]);
    exit(EXIT_SUCCESS);
}

void ParentWritingToBuffer(int* pfd, char* buffer, Params par, int childId)
{
    int i, numRead;
    close(pfd[0]);
    printf("in parent process\n");
    for(i = 0; i < par.m_cycles; ++i)
    {
        usleep(100000);
        FullBuffer(buffer, par.m_size, (char)i);
        numRead = write(pfd[1], buffer, par.m_size);
        if (numRead <= 0)
        {
            break;
        }
    }
    close(pfd[1]);
    waitpid(-1, &childId, 0);
    exit(EXIT_SUCCESS);
}

int main (int argc, char **argv)
{
    int childId;
    int pfd[2];
    char* buffer;
    Params par = {5, 128};

    ParseOptions(&par, argc, argv);
    printf("%d, %d\n", par.m_size, par.m_cycles);

    buffer = malloc(par.m_size * sizeof(char));
    if(NULL == buffer)
    {
        printf("buffer malloc failed\n");
        exit(EXIT_FAILURE);
    }

    if(-1 == pipe(pfd))
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    childId = (int)fork();
    if(childId < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if(childId == 0)
    {
        ChildReadBufferAndPrint(pfd, buffer, par);
    }
    else
    {
        ParentWritingToBuffer(pfd, buffer, par, childId);
    }
    
    return 0;
}
