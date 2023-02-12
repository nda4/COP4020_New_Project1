#ifndef PARS
#define PARS

#include "lex.h"




void match(int t);
void assignStmt();
void expression();
void term();
void factor();
void error(int t);
extern int lookAhead;
extern int lineNo;
extern FILE *fp;



#endif