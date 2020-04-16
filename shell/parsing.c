/*
Michael Afonin, 310514997
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

int getCommandType(char* cmd)
{
    if(strcmp(cmd, "pwd") == 0 ) return PWD;
    else if(strcmp(cmd, "cd") == 0 ) return CD;
    else if(strcmp(cmd, "nano") == 0 ) return NANO;
    else if(strcmp(cmd, "Cat") == 0 ) return FCAT;
    else if(strcmp(cmd, "cat") == 0 ) return CAT;
    else if(strcmp(cmd, "wc") == 0 ) return WC;
    else if(strcmp(cmd, "cp") == 0 ) return CP;
    else if(strcmp(cmd, "sort") == 0 ) return SORT;
    else if(strcmp(cmd, "grep") == 0 ) return GREP;
    else if(strcmp(cmd, "man") == 0 ) return MAN;
    else if(strcmp(cmd, "exit") == 0 ) return EXIT;
    else return FALSE;
}

int countParameters(char* line)
{
    int words = 1, i = 0;
    
    while (line[i] != '\0')
    {
        if(line[i++] == ' ') words++;
    }
    return words;
}

int secondCountParameters(char* line)
{
    int words = 1, i = 0;
    
    while (line[i] != '\0')
    {
        if(line[i++] == ' ') words++;
        if(line[i] == '|') return words-1;
    }
    return words;
}

void getArgs(char args[10][256], char* line, int words)
{
    int i = 0, j = 0, k = 0;

    while(i<words)
    {
        k = 0;
        while (line[j] != ' ' && line[j] != '\0')
        {
            if(line[j] == '\"')
            {
                j++;
                while(line[j] != '\"')
                {
                    args[i][k] = line[j];
                    k++;
                    j++;
                }
            }
            args[i][k] = line[j];
            k++;
            j++;
        }
        args[i][k] = '\0';
        j++;
        i++;
    }
}