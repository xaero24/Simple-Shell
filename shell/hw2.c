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
    int childPID, status, words = 1;
    int exitFlag = FALSE, pipeFlag = FALSE, errorFlag = FALSE;
    char command[LINE_LEN];
    char args[10][256];
    while(exitFlag == FALSE)
    {
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
                errorFlag = checkInput(command, args, words, &exitFlag);
                if(errorFlag) return 1;
                else
                {
                    /*execute command*/
                    if(exitFlag == TRUE) return 2;
                    printf("Execute command\n");
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