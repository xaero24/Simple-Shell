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
    int exitFlag = FALSE, pipeFlag = FALSE, errorFlag = FALSE;
    char command[LINE_LEN];
    char args[10][256];
    while(exitFlag == FALSE)
    {
        pipeFlag = FALSE;
        printf("+: ");
        fgets(command, 1024, stdin);
        command[strlen(command) - 1] = '\0';
        if(strlen(command) > 0)
        {
            words = countParameters(command);
            getArgs(args, command, words);
            childPID = fork();
            if(childPID == 0)
            {
                errorFlag = checkInput(command, words, &exitFlag);
                if(errorFlag) return 1;
                else
                {
                    /*execute command*/
                    if(exitFlag == TRUE) return 2;
                    printf("Execute command\n");
                    for(i = 0; i<words; i++)
                    {
                        if(strcmp(args[i], "|") == 0) pipeFlag = TRUE;
                    }
                    if(pipeFlag)
                    {
                        /*Piped command execution*/
                        errorFlag = executeCommand(args, 0, i-1);
                        errorFlag = executeCommand(args, i+1, words-1);
                    }
                    else
                    {
                        /*Non-piped command execution*/
                        errorFlag = executeCommand(args, 0, words-1);
                    }
                    
                    return 0;
                }
            }
            else
            {
                waitpid(childPID, &status, WUNTRACED);
                if(status == 512) break;
            }
        }
    }
    return 0;
}