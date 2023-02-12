#ifndef LEX
#define LEX

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