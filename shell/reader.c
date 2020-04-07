#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

int parseLine(char *cmdLine, dataLine *parsed)
{
    int words = 1, i = 0;
    char s;
    printf("%s\n", cmdLine);
    do
    {
        s = cmdLine[i++];
        if(s == ' ')
        {
            /*Get each word into a temp variable and store it*/
            words++;
        }
    } while (s != '\n');
    
    printf("Entered %d parameters\n", words);
    return 1;
}