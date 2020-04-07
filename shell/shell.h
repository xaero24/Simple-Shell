#ifndef SHELL_H
#define SHELL_H

/*Defining different command types*/


/*Defining global useful vars*/
#define TRUE 1
#define FALSE 0

#define LINE_LEN 1024

/*Data structure for holding the parsed line*/
typedef struct
{
    int argCount;
    char* argList;
} dataLine;

/*Function definitions*/
int parseLine(char*, dataLine*);

#endif