/*
Michael Afonin, 310514997
*/

#ifndef SHELL_H
#define SHELL_H

/*Defining different command types*/
#define PWD 1
#define CD 2
#define NANO 3
#define FCAT 4
#define CAT 5
#define WC 6
#define CP 7
#define PIPE 8
#define SORT 9
#define GREP 10
#define MAN 11
#define EXIT 12

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
void getArgs(char[10][256], char*, int);
int checkInput(char*, int, int*);

/*Parsing functions*/
int getCommandType(char*);
int countParameters(char*);

/*Utility functions*/
void printPWD();
int changeDirectory(char*);
void printManPage(char*);

#endif