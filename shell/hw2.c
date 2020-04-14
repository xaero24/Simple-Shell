#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include "shell.h"

/*
TODO: Remove all TODOs
*/

int main(int argc, char* argv[])
{
    int childPID, status, words = 1, i = 0;
    int exitFlag = FALSE, pipeFlag = FALSE;
    char command[LINE_LEN];
    char args[10][256];
    while(exitFlag == FALSE)
    {
        printf("+: ");
        fgets(command, 1024, stdin);
        command[strlen(command) - 1] = '\0';
        printf("GOT \"%s\" len %ld\n", command, strlen(command));
        if(strlen(command) > 0)
        {
            words = countParameters(command);
            getArgs(args, command, words);

            childPID = fork();
            if(childPID == 0)
            {
                /*Parse line, get params and execute*/
                exitFlag = parseLine(command, pipeFlag, args);
            }
            else
            {
                waitpid(childPID, &status, WUNTRACED);
                if(status != 0)
                {
                    printf("Process %d terminated with status %d\n", childPID, status);
                    if(status == -1)
                    {
                        printf("An error occured in process %d\n", childPID);
                    }
                    exitFlag = status;
                }
            }
        }
    }
    return 0;
}