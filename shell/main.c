#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include "shell.h"

int main(int argc, char* argv[])
{
    int childPID, status;
    int cont = TRUE;
    char command[LINE_LEN];
    dataLine *line = (dataLine*)malloc(sizeof(dataLine));
    while(cont)
    {
        printf("$ ");
        fgets(command, 1024, stdin);

        childPID = fork();
        if(childPID == 0)
        {
            /*Parse line, get params and execute*/
            cont = parseLine(command, line);
        }
        else
        {
            waitpid(childPID, &status, WUNTRACED);
        }
    }
    return 0;
}