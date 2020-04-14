#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

/*This function provides the "pwd" action*/
void printPWD()
{
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("%s\n", cwd);
}

/*This function provides the "cd" action*/
int changeDirectory(char* newDir)
{
    int result = chdir(newDir);
    printf("Moved to ");
    printPWD();
    return result;
}

/*This function provides the "Cat >" and "nano" action*/
int writeToFile(char* filename)
{
    char line[1024];
    FILE* infile = NULL;
    infile = fopen(filename, "w");
    if(!infile)
        return FALSE;
    while(TRUE)
    {
        fgets(line, 1024, stdin);
        if(strlen(line) == 1){
            fclose(infile);
            return TRUE;
        }
        fputs(line, infile);
    }
}

/*This function provides the "cat" action*/
int readFile(char* filename)
{
    char line[1024], s;
    FILE* infile = NULL;
    infile = fopen(filename, "r");
    if(!infile)
        return FALSE;
    s = fgetc(infile);
    while(s != EOF)
    {
        putchar(s);
    }
    if (feof(infile))
    {
        fclose(infile); 
        return TRUE;
    }
    else
    {
        fclose(infile); 
        return FALSE;
    }
}

/*This function provides the "wc" action*/
int counter(char* filename, char* options)
{
    int lineFlag = FALSE, wordFlag = FALSE, charFlag = FALSE;
    int lineCount = 0, wordCount = 0, charCount = 0;
    int i;
    char s;
    FILE* infile = NULL;
    infile = fopen(filename, "r");
    if(!infile)
        return FALSE;

    for(i=0; i<3; i++)
    {
        if(options[i] == 'l') lineFlag = TRUE;
        if(options[i] == 'w') wordFlag = TRUE;
        if(options[i] == 'c') charFlag = TRUE;
    }

    s = fgetc(infile);
    while(s != EOF)
    {
        if(s != '\n') charCount++;
        if(s == '\n') lineCount++;
        if(s == ' ' || s == '\n') wordCount++;
    }
    if (feof(infile))
    {
        fclose(infile); 
        return TRUE;
    }
    else
    {
        fclose(infile); 
        return FALSE;
    }
}

/*This function provides the "cp" action*/
int copyFiles(char* source, char* destination)
{
    char line[1024], s;
    FILE *src = NULL, *dst = NULL;
    src = fopen(source, "r");
    dst = fopen(destination, "r");
    if(!src)
        return FALSE;
    if(!dst)
        return FALSE;
    
    s = fgetc(src);
    while(s != EOF)
    {
        fputc(s, dst);
    }
    if (feof(src))
    {
        fclose(src);
        fclose(dst);
        return TRUE;
    }
    else
    {
        fclose(src);
        fclose(dst);
        return FALSE;
    }
}

/*This function provides the "pipe" action*/

/*This function provides the "sort" action*/

/*This function provides the "grep" action*/
int grepFile(char* filename, char* pattern, char grepFlag)
{
    int lineFlag = FALSE;
    int lineCount = 0;
    int i = 0;
    char s, temp[1024];
    FILE* infile = NULL;
    infile = fopen(filename, "r");
    if(!infile)
        return FALSE;

    if(grepFlag == 'c') lineFlag = TRUE;

    s = fgetc(infile);
    while(s != EOF)
    {
        i = 0;
        while(s != ' ')
        {
            temp[i] = s;
            s = fgetc(infile);
        }
    }
    if (feof(infile))
    {
        fclose(infile); 
        return TRUE;
    }
    else
    {
        fclose(infile); 
        return FALSE;
    }
}

/*This function provides the "man" action*/
void printManPage(char* cmd)
{
    switch(getCommandType(cmd))
    {
        case PWD:
            printf("PWD - present working directory.\n");
            printf("Shows the current directory the user is working with.\n");
            printf("Usage example:\n");
            printf("  +: pwd\n");
            printf("  /home/User/Documents/Simple-Shell/shell\n");
            printf("\n");
            printf("No parameters are to be passed to the function.\n");
            break;
        case CD:
            printf("cd - change directory.\n");
            printf("Changes the current working directory to the specified directory.\n");
            printf("Usage example:\n");
            printf("  +: cd Documents/research\n");
            printf("\n");
            printf("One parameter is passed - either an absolute or a relative path.\n");
            break;
        case NANO:
            printf("nano - write to file.\n");
            printf("Writes the stdin input to the specified file. Terminated with ^C.\n");
            printf("Usage example:\n");
            printf("  +: nano file1.txt\n");
            printf("  Line 1\n");
            printf("  Line 2\n");
            printf("  Line 3\n");
            printf("^C\n");
            printf("\n");
            printf("One parameter is passed - the name of the target file.\n");
            break;
        case FCAT:
            printf("Cat - write to file.\n");
            printf("Writes the stdin input to the specified file. Terminated with empty line.\n");
            printf("Usage example:\n");
            printf("  +: Cat > file1.txt\n");
            printf("  Line 1\n");
            printf("  Line 2\n");
            printf("  Line 3\n");
            printf("\n");
            printf("One parameter is passed - the name of the target file.\n");
            break;
        case CAT:
            printf("cat - get file contents.\n");
            printf("Writes the file input to screen (stdin).\n");
            printf("Usage example:\n");
            printf("  +: cat file1.txt\n");
            printf("  Line 1\n");
            printf("  Line 2\n");
            printf("  Line 3\n");
            printf("\n");
            printf("One parameter is passed - the name of the target file.\n");
            break;
        case WC:
            printf("wc - counts the amount of words/chars/lines ina file.\n");
            printf("Writes the stdin input to the specified file. Terminated with ^C.\n");
            printf("Usage example:\n");
            printf("  +: wc -l file1.txt\n");
            printf("  4\n");
            printf("\n");
            printf("One flag can be chosen:\n");
            printf("  -l for line count;\n");
            printf("  -w for word count;\n");
            printf("  -c for character count.\n");
            printf("One parameter is passed - the name of the target file.\n");
            break;
        case CP:
            printf("cp - copy a file.\n");
            printf("Makes a copy of the source file with the destination file's name.\n");
            printf("Usage example:\n");
            printf("  +: cp file1.txt file2.txt\n");
            printf("\n");
            printf("Two parameters are passed - the first one is the source file and the second one is the target/destination file.\n");
            break;
        case PIPE:
            printf("| - pipe operator.\n");
            printf("Takes the output of the first command as the input of the second command.\n");
            printf("Usage example:\n");
            printf("  +: cat file1.txt | grep Line\n");
            printf("  Line 1\n");
            printf("  New Line\n");
            printf("  Line 5\n");
            break;
        case SORT:
            printf("sort - sort file lines.\n");
            printf("Sorts a file in lexical order (regular or reversed) and displays the output.\n");
            printf("Usage example:\n");
            printf("  +: sort -r file1.txt\n");
            printf("  Line 3\n");
            printf("  Line 2\n");
            printf("  Line 1\n");
            printf("\n");
            printf("One flag is possible: -r, which reverses the order of the sort.\n");
            printf("One parameter is passed - the name of the file to be sorted.\n");
            break;
        case GREP:
            printf("grep - find patterns in file.\n");
            printf("Looks for patterns in a file. Displays either the found lines or their count.\n");
            printf("Usage example:\n");
            printf("  +: grep Line file1.txt\n");
            printf("  Line 1\n");
            printf("  New Line\n");
            printf("  Line 5\n");
            printf("\n");
            printf("One flag is possible: -c, which displays the count of the found lines instead the lines themselves.\n");
            printf("One parameter is passed - the name of the file to be scanned.\n");
            break;
        case MAN:
            printf("man - display manpage.\n");
            printf("Shows the manual page for the specified command.\n");
            printf("Usage example:\n");
            printf("  +: man cp\n");
            printf("  [cp manpage].\n");
            printf("\n");
            printf("Two parameters are passed - the first one is the source file and the second one is the target/destination file.\n");
            printf("\n");
            printf("One parameter is passed - the name of the command.\n");
            break;
        case EXIT:
            printf("exit - exit the simple shell.\n");
            printf("Exits the simple shell and returns to the regular shell.\n");
            printf("Usage example:\n");
            printf("  +: exit\n");
            printf("  user@station:~$\n");
            printf("\n");
            printf("No parameters are passed to the command.\n");
            break;
        default:
            printf("Unknown command, thus has no manpage: %s\n", cmd);
    }
}
