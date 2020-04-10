#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

int parseLine(char *cmdLine, dataLine *parsed)
{
    int words = 0, i = 0, j = 0;
    char s, word[256];
    printf("%s\n", cmdLine);
    do
    {
        j = 0;
        s = cmdLine[i++];
        while(s != ' ' && s != '\n')
        {
            /*Get each word into a temp variable and store it*/
            word[j++] = s;
            s = cmdLine[i++];
        }
        word[j] = '\0';
        printf("Word is \"%s\"\n", word);
        words++;
    } while (s != '\n');
    
    printf("Entered %d parameters\n", words);
    return 1;
}