#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

int checkInput(char *cmdLine, char args[10][256], int paramCount, int* exitFlag)
{
    int i = 0, j = 0;
    int errorFlag = FALSE;
    char word[256];
    
    while(cmdLine[i] != ' ' && cmdLine[i] != '\n')
    {
        /*Get command into a temp variable and store it*/
        word[j++] = cmdLine[i++];
    }
    word[j] = '\0';
    i++;

    switch(getCommandType(word))
    {
        case PWD:
            /*Check input parametrs*/
            if(paramCount != 1)
            {
                printf("PWD takes no parameters.\n");
                errorFlag = TRUE;
            }
            break;
        case CD:
            /*Check input parametrs*/
            if(paramCount != 2)
            {
                printf("cd takes exactly 1 parameter.\n");
                errorFlag = TRUE;
            }
            break;
        case FCAT:
            /*Check input parametrs*/
            if(cmdLine[i] != '>')
            {
                printf("Cat has to be followed by > sign.\n");
                errorFlag = TRUE;
            }
            if(paramCount != 3)
            {
                printf("Cat takes exactly 1 parameter.\n");
                errorFlag = TRUE;
            }
            break;
        case NANO:
            /*Check input parametrs*/
            if(paramCount != 2)
            {
                printf("nano takes exactly 1 parameter.\n");
                errorFlag = TRUE;
            }
            break;
        case CAT:
            /*Check input parametrs*/
            if(paramCount != 2)
            {
                printf("cat takes exactly 1 parameter.\n");
                errorFlag = TRUE;
            }
            break;
        case WC:
            /* TODO: Check input parametrs in a better way*/
            if(paramCount != 3)
            {
                printf("wc takes exactly 1 flag and 1 parameter.\n");
                errorFlag = TRUE;
                break;
            }

            if(cmdLine[i] == '-')
            {
                /*Read the flags*/
                i++;
                while(cmdLine[i] != ' ')
                {
                    if(cmdLine[i] != 'l' && cmdLine[i] != 'w' && cmdLine[i] != 'c')
                    {
                        printf("Bad flag passed: %c\n", cmdLine[i]);
                        errorFlag = TRUE;
                    }
                    i++;
                }
            }
            break;
        case CP:
            /*Check input parametrs*/
            if(paramCount != 3)
            {
                printf("cp takes exactly 2 parameters.\n");
                errorFlag = TRUE;
            }
            break;
        case SORT:
            /* TODO: Check input parametrs in a better way*/
            if(paramCount < 2 || paramCount > 3)
            {
                printf("sort takes exactly 1 parameter and 1 possible flag.\n");
                errorFlag = TRUE;
            }
            break;
        case GREP:
            /*Check input parametrs*/
            if(paramCount < 3 || paramCount > 4 )
            {
                printf("grep takes exactly 1 pattern and 1 parameter with 1 possible flag.\n");
                errorFlag = TRUE;
                break;
            }

            if(cmdLine[i] == '-')
            {
                /*Read the flag*/
                i++;
                if(cmdLine[i] == ' ')
                {
                    printf("No flag was specified.\n");
                    errorFlag = TRUE;
                    break;
                }
                if(cmdLine[i+1] != ' ')
                {
                    printf("Exactly one flag is allowed.\n");
                    errorFlag = TRUE;
                    break;
                }
                if(cmdLine[i] != 'c')
                {
                    printf("Unknown flag.\n");
                    errorFlag = TRUE;
                    break;
                }
            }
            break;
        case MAN:
            /*Check input parametrs*/
            if(paramCount != 2)
            {
                printf("man takes exactly 2 parameters.\n");
                errorFlag = TRUE;
            }
            break;
        case EXIT:
            /*Check input parametrs*/
            if(paramCount != 1)
            {
                printf("exit takes no parameters.\n");
                errorFlag = TRUE;
                break;
            }
            *exitFlag = TRUE;
            break;
        default:
            printf("Unknown command: %s\n", word);
    }
            
    return errorFlag;
}