//Noah Daniel Arwine
//COP4020_Spring_2023
//Project 1
//Lexical Analyser and Parser

#ifndef LEX
#define LEX


/*
    lex provides the ability to iterate and identify the strings found in a file. It returns an int value taht represents
    a type of string. If an Identifer is found, it adds it to a list for later use.
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

typedef struct{
    char* charValue;
    int type;
}anEntry;

extern anEntry myTable[TABLELENGTH / sizeof(anEntry)]; // the actual symboltable

#endif  