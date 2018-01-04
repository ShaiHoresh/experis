#include <ctype.h> /*isprint*/
#include <stdio.h> /*printf, fprintf, stderr, */
#include <stdlib.h> /* atoi, abort*/
#include <unistd.h> /* fork, usleep, pause, getppid */
#include <sys/wait.h> /* waitpid */
/*#include <errno.h>*/
/*#include <signal.h>*/
/*#include <getopt.h>*/


typedef struct params
{
    int m_parentSig;
    int m_childSig;
    int m_sleep;
}params;

void ActionFunc1(int _sig, siginfo_t *_siginfo, void *_context)
{
    printf("Sending PID: %ld\n", (long)_siginfo->si_pid);
    /*kill((long)_siginfo->si_pid, _sig);*/
}

int ParseOptions(params* _par, int argc, char **argv)
{
    int w;
    
    while ((w = getopt(argc, argv, "p:c:s:")) != -1)
    {
        switch (w)
        {
            case 'p':
                _par->m_parentSig = atoi(optarg);
                break;
            case 'c':
                _par->m_childSig = atoi(optarg);
                break;
            case 's':
                _par->m_sleep = atoi(optarg);
                break;
            case '?':
                if (optopt == 'w')
                fprintf (stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint(optopt))
                    fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
                return 0;
            default:
                abort();
        }
    }
    return 1;
}

int main (int argc, char **argv)
{
    struct sigaction sa, sb;
    int forkRet, status;
    params par = {4, 6, 50};

    ParseOptions(&par, argc, argv);
    printf ("p = %d, c = %d, s = %d\n", par.m_parentSig, par.m_childSig, par.m_sleep);
    
    
    forkRet = (int)fork();
    if(forkRet < 0)
    {
        /*fork error*/
        printf("fatal error\n");
        return -1;
    }
    else if(forkRet > 0)
    {
        /*parent code*/
        sa.sa_sigaction = ActionFunc1;
        sa.sa_flags = SA_SIGINFO;
        
        sigaction(par.m_parentSig, &sa, NULL);
        printf("in parent process\n");
        usleep((unsigned int)par.m_sleep * 1000);
        kill(forkRet, par.m_parentSig);
        waitpid(forkRet, &status, 0);
        printf("exiting parent process\n");
    }
    else
    {
        /*child code*/
        sb.sa_sigaction = ActionFunc1;
        sb.sa_flags = SA_SIGINFO;
        
        sigaction(par.m_childSig, &sb, NULL);
        pause();
        printf("in child process\n");
        kill(getppid(), par.m_parentSig);
        printf("exiting child process\n");
    }

    return 0;
}
