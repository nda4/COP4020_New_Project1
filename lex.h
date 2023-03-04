//Noah Daniel Arwine
//COP4020_Spring_2023
//Project 2
//Lexical Analyser and Parser + Int Checker

#ifndef LEX
#define LEX


/*
    lex provides the ability to iterate and identify the strings found in a file. It returns an int value taht represents
    a type of string. If an Identifer is found, it adds it to a list for later use.

    Project 2 additional info: Adds steps to perform checks for "int" calls. If the value is not defined before a call, it fails, 
    if it is already defined and attempts to define again, it fails. Basic register representation is also presented, although it 
    is imperfect
*/


#include "Definitions"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// #include "SymbolTable"


#define MAX 30
#define TABLELENGTH 100


int lexan(FILE *fp);
int lookup(char* arr); 
extern int lineNo;
extern char* currentIDLexeme;
extern int isIntMatch;
extern int firstDef;

extern char operand;

typedef struct{
    char* charValue;
    int type;
}anEntry;

extern anEntry myTable[TABLELENGTH / sizeof(anEntry)]; // the actual symboltable

#endif  