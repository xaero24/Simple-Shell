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
#define SORT 9
#define GREP 10
#define MAN 11
#define EXIT 12

/*Defining global useful vars*/
#define TRUE 1
#define FALSE 0

#define LINE_LEN 1024

/*Function definitions*/
int checkInput(char*, int, int*);
int executeCommand(char[10][256], int, int);

/*Parsing functions*/
int getCommandType(char*);
int countParameters(char*);
int secondCountParameters(char*);
void getArgs(char[10][256], char*, int);

/*Utility functions*/
void printPWD();
int changeDirectory(char*);
int writeToFile(char*);
int readFile(char*);
int counter(char*, char*);
int copyFiles(char*, char*);
void printManPage(char*);

#endif