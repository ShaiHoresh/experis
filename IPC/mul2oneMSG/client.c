#include <semaphore.h>  /* well... semaphore! */
#include <stdlib.h>     /* EXIT_FAILURE */
#include <fcntl.h>      /* O_* macros */
#include <stdio.h>      /* perror */
#include <unistd.h>     /* usleep */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "MsgQ.h"

int main(int argc, char **argv)
{
    /* declarations */
    sem_t* sem;
    int ret, msgQID;
    size_t i;
    MsgStruct msgStruct;
    pid_t pid, myPid;
    Params par = {0, 0, 5, 500000, 1, PATH};
    
    
    
    
    /* sem_open O_RDWR? */
    sem = sem_open(SEM_NAME, 0);
    if(sem == SEM_FAILED)
    {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }
    
    /* sem_post */
    ret = sem_post(sem);
    if(-1 == ret)
    {
        perror("sem_post");
        exit(EXIT_FAILURE);
    }
    
    msgQID = ConnectMessagQueue(&par);
    printf("msgQID = %d\n", msgQID);
    
    myPid = getpid();
    
    /* limited loop */
    for(i = 0; i < par.m_numOfCycles; ++i)
    {
        InitialMsgStruct(&msgStruct);
        SendMessage(&msgStruct, msgQID);
        pid = RecieveMessage(&msgStruct, msgQID, SERVER, 0);
        if(pid != myPid)
        {
            SendMessage(&msgStruct, msgQID);
        }
        usleep(500000);
    }
    
    ret = sem_wait(sem);
    if(-1 == ret)
    {
        perror("sem_wait");
        exit(EXIT_FAILURE);
    }
    
    return 0;
}   
