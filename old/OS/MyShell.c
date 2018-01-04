#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define STR_LENGTH 128
#define PARAM_LENGTH 32

int Read_Command(char* _command, char** _tokens);

int main()
{
    int status, forkVal, readCmdVal;
    char command[STR_LENGTH];
    char* parameters[PARAM_LENGTH];
    
    nice(10);
    
    while(1)
    {
        printf("A very primitive shell!! >>  ");

        readCmdVal = Read_Command(command, parameters);
        
        if(readCmdVal)
        {
            return 0;
        }
        
        forkVal = fork();
        if(forkVal > 0)
        {
            /*parent code*/
            waitpid (-1, &status, 0);
        }
        else if(forkVal < 0)
        {
            /*fork error*/
            printf("fatal error\n");
            return -1;
        }
        else
        {
            /*child code*/
            execvp(parameters[0], parameters);
            printf("command not found\n");
            return -1;
        }
    }
    return 0;
}

int Read_Command(char* _command, char** _parameters)
{

    int i = 0;
    
    fgets(_command, STR_LENGTH, stdin);    
    _parameters[i] = strtok(_command, " \n");
    if(strcmp(_parameters[0], "exit") == 0)
    {
        printf("exited normally\n");
        return 1;
    }
    while(NULL != _parameters[i])
    {
        i++;
        _parameters[i] = strtok(NULL, " \n");
    }
    _parameters[i + 1] = NULL;

    return 0;
}


