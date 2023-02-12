#include "pars.h"

int lookAhead = 0;

void error(){
    // printf("error found on line%d", lineNo);
    exit(1);
}

void match(int t, FILE * fp){
    if(lookAhead == t){
        lookAhead = lexan(fp);
        printf("nice");
    }
    else
        printf("syntax error\n");
    error();
}
