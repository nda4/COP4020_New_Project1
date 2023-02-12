#ifndef PARS
#define PARS

#include "lex.h"




void match(int t, FILE * fp);
void assignStmt();
void express();
void term();
void factor();
void fail();
extern int lookAhead;



#endif