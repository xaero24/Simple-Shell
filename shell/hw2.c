/*
Michael Afonin, 310514997
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include "shell.h"


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
                    for(i = 0; i<words; i++)
                    {
                        if(strcmp(args[i], "|") == 0) pipeFlag = TRUE;
                    }
                    if(pipeFlag)
                    {
                        /*Piped command execution*/
                        printf("Pipe is not implemented, only first command will be executed.\n");
                        errorFlag = executeCommand(args, 0, i-1);
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
                if(strcmp(args[0], "cd") == 0 && status == 0)
                {
                    chdir(args[1]);
                }
                if(status == 512) break;
            }
        }
    }
    return 0;
}