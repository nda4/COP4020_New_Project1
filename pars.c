#include "pars.h"
#include "Definitions"

int lookAhead = 0;

void error(int t){
    printf("Error found on line %d\n", lineNo);
    // printf("ENDED HERE: %d\n", t);
    if(t == ID){
        printf("Expected Identifier\n");
    }
    else if(t == NUM){
        printf("Expected Number Value\n");
    }
    else if(t == BEGIN){
        printf("Expected 'begin' Statement\n");
    }
    else if(t == END){
        printf("Expected 'end' Statement\n");
    }
    else if(t == SEMICOLON){
        printf("Expected Semicolon\n");
    }
    else if(t == PLUS || t == MINUS){
        printf("Expected Operator\n");
    }
    else if(t == TIMES || t == DIVIDE){
        printf("Expected Operator\n");
    }
    else if(t == EQUALS){
        printf("Expected '='\n");
    }
    else if(t == CLOSEQ){
        printf("Expected Closing Quote\n");
    }
    else if(t == DOUBLEUNDER){
        printf("Double Underscores Illegal\n");
    }
    else if(t == ENDUNDER){
        printf("Identifiers Must Not Start or End With Underscore\n");
    }
    else if(t == OPENQ){
        printf("Expected Opening Quote\n");
    }
    printf("\n");
    exit(1);
}

void match(int t){
    if(lookAhead == t){
        lookAhead = lexan(fp);
    }
    else{
        printf("Syntax ");
        error(t);
    }
}

void factor(){
    if(lookAhead == ID)
        match(ID);
    else if(lookAhead == NUM)
        match(NUM);
    else if(lookAhead == OPENQ){
        match(OPENQ);
        expression();
        match(CLOSEQ);
    }
    else
        error(ID);
}

void term(){
    factor();
    while(lookAhead == TIMES || lookAhead == DIVIDE){
        match(lookAhead);
        factor();
    }
}

void expression(){
    term();
    while(lookAhead == PLUS || lookAhead == MINUS){
        // printf("AExpression");
        match(lookAhead);
        term();
    }
}

void assignStmt(){
    match(ID);
    // printf("IDMATCHED\n");

    if(lookAhead != EQUALS){
        // printf("%d", lookAhead);
        error(EQUALS);
    }
    else{
        match(lookAhead);
        // printf("EXPRESSION");
        expression();
        match(SEMICOLON);
    }
}
