#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

int parseLine(char *cmdLine, int pipeFlag, char args[10][256])
{
    int i = 0, j = 0;
    int paramCount;
    int exitFlag = FALSE;
    char word[256], src[256], dst[256];
    char flags[3] = "000", grepFlag;
    
    while(cmdLine[i] != ' ' && cmdLine[i] != '\n')
    {
        /*Get command into a temp variable and store it*/
        word[j++] = cmdLine[i++];
    }
    word[j] = '\0';
    i++;

    paramCount = countParameters(cmdLine);
    if(strlen(cmdLine) == 1) return exitFlag;

    switch(getCommandType(word))
    {
        case PWD:
            /*Check input parametrs*/
            if(paramCount != 1)
            {
                printf("PWD takes no parameters.\n");
                break;
            }
            /* TODO: Check for errors*/
            printPWD();
            break;
        case CD:
            /*Check input parametrs*/
            if(paramCount != 2)
            {
                printf("cd takes exactly 1 parameter.\n");
                break;
            }
            
            j = 0;
            while(cmdLine[i] != '\n')
            {
                word[j++] = cmdLine[i++];
            }
            word[j] = '\0';

            if(changeDirectory(word) != 0)
                printf("An error occured on dir change. Try again.\n");
            break;
        case FCAT:
            /*Check input parametrs*/
            if(cmdLine[i] != '>')
            {
                printf("Cat has to be followed by > sign.\n");
                break;
            }
            if(paramCount != 3)
            {
                printf("Cat takes exactly 1 parameter.\n");
                break;
            }
            i+=2;

            j = 0;
            while(cmdLine[i] != '\n')
            {
                word[j++] = cmdLine[i++];
            }
            word[j] = '\0';

            if(writeToFile(word) == FALSE)
            {
                printf("Failed creating file.\n");
            }
            break;
        case NANO:
            /*Check input parametrs*/
            if(paramCount != 2)
            {
                printf("nano takes exactly 1 parameter.\n");
                break;
            }

            j = 0;
            while(cmdLine[i] != '\n')
            {
                word[j++] = cmdLine[i++];
            }
            word[j] = '\0';

            if(writeToFile(word) == FALSE)
            {
                printf("Failed creating file.\n");
            }
            break;
        case CAT:
            /*Check input parametrs*/
            if(paramCount != 2)
            {
                printf("cat takes exactly 1 parameter.\n");
                break;
            }
            
            j = 0;
            while(cmdLine[i] != '\n')
            {
                word[j++] = cmdLine[i++];
            }
            word[j] = '\0';

            if(readFile(word) == FALSE)
            {
                printf("Failed reading file.\n");
            }
            break;
        case WC:
            /* TODO: Check input parametrs in a better way*/
            if(paramCount != 3)
            {
                printf("wc takes exactly 1 flag and 1 parameter.\n");
                break;
            }

            if(cmdLine[i] == '-')
            {
                /*Read the flags*/
                i++;
                j = 0;
                while(cmdLine[i] != ' ')
                {
                    flags[j++] = cmdLine[i++];
                }
                flags[j] = '\0';
            }

            j = 0;
            while(cmdLine[i] != '\n')
            {
                word[j++] = cmdLine[i++];
            }
            word[j] = '\0';

            if(counter(word, flags) == FALSE)
            {
                printf("Failed reading file.\n");
            }
            break;
        case CP:
            /*Check input parametrs*/
            if(paramCount != 3)
            {
                printf("cp takes exactly 2 parameters.\n");
                break;
            }

            j = 0;
            while(cmdLine[i] != ' ')
            {
                src[j++] = cmdLine[i++];
            }
            src[j] = '\0';

            j = 0;
            while(cmdLine[i] != '\n')
            {
                dst[j++] = cmdLine[i++];
            }
            dst[j] = '\0';

            if(copyFiles(src, dst) == FALSE)
            {
                printf("Failed reading or creating file.\n");
            }
            break;
        case SORT:
            /* TODO: Check input parametrs in a better way*/
            if(paramCount < 2 || paramCount > 3)
            {
                printf("sort takes exactly 1 parameter and 1 possible flag.\n");
                break;
            }
            break;
        case GREP:
            /*Check input parametrs*/
            if(paramCount < 3 || paramCount > 4 )
            {
                printf("grep takes exactly 1 pattern and 1 parameter with 1 possible flag.\n");
                break;
            }

            if(cmdLine[i] == '-')
            {
                /*Read the flag*/
                i++;
                if(cmdLine[i] == ' ')
                {
                    printf("No flag was specified.\n");
                    break;
                }
                grepFlag = cmdLine[i];
                if(cmdLine[i+1] != ' ')
                {
                    printf("Exactly one flag is allowed.\n");
                    break;
                }
                if(cmdLine[i] != 'c')
                {
                    printf("Unknown flag.\n");
                    break;
                }
                i++;
            }

            j = 0;
            while(cmdLine[i] != ' ')
            {
                word[j++] = cmdLine[i++];
            }
            word[j] = '\0';
            i++;

            j = 0;
            while(cmdLine[i] != '\n')
            {
                src[j++] = cmdLine[i++];
            }
            src[j] = '\0';

            if(grepFile(src, word, grepFlag) == FALSE)
            {
                printf("Failed reading file.\n");
            }
            break;
        case MAN:
            /*Check input parametrs*/
            if(paramCount != 2)
            {
                printf("man takes exactly 2 parameters.\n");
                break;
            }

            j = 0;
            while(cmdLine[i] != '\n')
            {
                word[j++] = cmdLine[i++];
            }
            word[j] = '\0';
            printManPage(word);
            break;
        case EXIT:
            /*Check input parametrs*/
            if(paramCount != 1)
            {
                printf("exit takes no parameters.\n");
                break;
            }
            exitFlag = TRUE;
            break;
        default:
            printf("Unknown command: %s\n", word);
    }
            
    return exitFlag;
}