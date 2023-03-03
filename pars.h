//Noah Daniel Arwine
//COP4020_Spring_2023
//Project 1
//Lexical Analyser and Parser


#ifndef PARS
#define PARS

#include "lex.h"

/*
    Calls lex.h and accepts or rejects the data found there. First run is AssignStmt which calls Expression. Expression calls the rest.
    If the lex.h returns a value that does not match an expected value, the line number kept in lex is returned along with the error
    code describing the problem
*/


void match(int t);
void assignStmt();
int newLookup();
void intMatch();
void expression();
void term();
void factor();
void error(int t);
extern int lookAhead;
extern int lineNo;
extern int iValue;
extern int isIntMatch;
extern FILE *fp;
// extern char* currentIDLexeme;



#endif