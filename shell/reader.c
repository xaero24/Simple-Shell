#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

int checkInput(char *cmdLine, int paramCount, int* exitFlag)
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
                break;
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
            if(paramCount < 2 || paramCount > 3)
            {
                printf("wc takes 1 possible flag and 1 parameter.\n");
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
            }if(cmdLine[i] == '-')
            {
                /*Read the flag*/
                i++;
                if(cmdLine[i] != 'c')
                {
                    printf("Bad flag passed: %c\n", cmdLine[i]);
                    errorFlag = TRUE;
                    break;
                }
                if(cmdLine[i+1] != ' ')
                {
                    printf("Only one flag is supported.\n");
                    errorFlag = TRUE;
                    break;
                }
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
                    printf("Unknown flag: %c.\n", cmdLine[i]);
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
            errorFlag = TRUE;
    }
            
    return errorFlag;
}


int executeCommand(char args[10][256], int startIndex, int endIndex)
{
    int i = 0, j = 0;
    int errorFlag = FALSE;
    char word[256];

    switch(getCommandType(args[startIndex]))
    {
        case PWD:
            printPWD();
            break;
        case CD:
            if(changeDirectory(args[startIndex+1]) == -1)
            {
                printf("An error ccured while changing directory.\n");
                errorFlag = TRUE;
            }
            break;
        case FCAT:
            if(writeToFile(args[startIndex+2]) == FALSE)
            {
                printf("Error writing to file %s\n", args[startIndex+2]);
                errorFlag = TRUE;
            }
            break;
        case NANO:
            if(writeToFile(args[startIndex+1]) == FALSE)
            {
                printf("Error writing to file %s\n", args[startIndex+1]);
                errorFlag = TRUE;
            }
            break;
        case CAT:
            if(readFile(args[startIndex+1]) == FALSE)
            {
                printf("Error reading file %s\n", args[startIndex+1]);
                errorFlag = TRUE;
            }
            break;
        case WC:
            if(counter(args[startIndex+2], args[startIndex+1]) == FALSE)
            {
                printf("Error reading file %s\n", args[startIndex+2]);
                errorFlag = TRUE;
            }
            break;
        case CP:
            if(counter(args[startIndex+1], args[startIndex+2]) == FALSE)
            {
                printf("Error reading file %s\n", args[startIndex+2]);
                errorFlag = TRUE;
            }
            break;
        case SORT:
            if(endIndex-startIndex == 1)
            {
                if(execlp(
                    args[startIndex],
                    args[startIndex],
                    args[startIndex+1],
                    NULL
                    ) == -1)
                    {
                        printf("An error occured sorting file %s\n", args[startIndex+1]);
                        errorFlag = TRUE;
                    }
            }
            else if(endIndex-startIndex == 2)
            {
                if(execlp(
                    args[startIndex],
                    args[startIndex],
                    args[startIndex+1],
                    args[startIndex+2],
                    NULL
                    ) == -1)
                    {
                        printf("An error occured sorting file %s\n", args[startIndex+1]);
                        errorFlag = TRUE;
                    }
            }
            break;
        case GREP:
            if(endIndex-startIndex == 2)
            {
                if(execlp(
                    args[startIndex],
                    args[startIndex],
                    args[startIndex+1],
                    args[startIndex+2],
                    NULL
                    ) == -1)
                    {
                        printf("An error occured grepping file %s\n", args[startIndex+1]);
                        errorFlag = TRUE;
                    }
            }
            else if(endIndex-startIndex == 3)
            {
                if(execlp(
                    args[startIndex],
                    args[startIndex],
                    args[startIndex+1],
                    args[startIndex+2],
                    args[startIndex+3],
                    NULL
                    ) == -1)
                    {
                        printf("An error occured grepping file %s\n", args[startIndex+1]);
                        errorFlag = TRUE;
                    }
            }
            break;
        case MAN:
            printManPage(args[startIndex+1]);
            break;
        default:
            printf("Unknown command: %s\n", word);
            errorFlag = TRUE;
    }
            
    return errorFlag;
}