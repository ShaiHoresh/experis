
/* TODO check each include if needed */
#include <stdlib.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <semaphore.h>
#include <errno.h>
#include <stdio.h> /* sprintf, perror */
#include <unistd.h> /* sleep */

#include "MsgQ.h"

int main(int argc, char **argv)
{
    int msgQID;
    int rcv = 0, ret;
    int clients = 0;
    MsgStruct msgStruct;
    sem_t* sem;
    Params par = {0, 0, 10, 200000, 1, PATH};
    
    ParseOptions(&par, argc, argv);
    
    /* open a new semaphore */
    sem = sem_open(SEM_NAME, O_CREAT, 0666, 0);
    if(sem == SEM_FAILED)
    {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }
    
    
    msgQID = EstablishMessageQueue(&par);
    printf("msgQID = %d\n", msgQID);
    InitialMsgStruct(&msgStruct);

    /*wait to the first message*/    
    sleep(5);
    
    for(;;)
    {
        rcv = RecieveMessage(&msgStruct, msgQID, CLIENTS, IPC_NOWAIT);
        if(0 == rcv)
        {
            usleep(500000);
            continue;
        }
        
        printf("rcv = %d\n",rcv);

        PrintMessage(&msgStruct);
        ReturnMessage(&msgStruct, msgQID);

        ret = sem_getvalue(sem, &clients);
        if(-1 == ret)
        {
            perror("sem_getvalue");
            exit(EXIT_FAILURE);
        }
        
        if(clients == 0)
        {
            break;
        }
    }
    
    /*commit suicide*/
    msgctl(msgQID, IPC_RMID, NULL); /* errors? */
    
    ret = sem_destroy(sem);
    if(-1 == ret)
    {
        perror("sem_getvalue");
        exit(EXIT_FAILURE);
    }
    
    return 0;
}


