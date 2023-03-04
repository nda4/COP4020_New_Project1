#include "pars.h"
#include "Definitions"

int lookAhead = 0;
int iValue = 12;
int isIntMatch = 0;

char op1[MAX];
char op2[MAX];
char opcode[MAX];

void error(int t){
    printf("Error found on line %d\n", lineNo);
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
    else if(t == REDEF){
        printf("Redefintion Error\n");
    }
    else if(t == UNDEF){
        printf("Undefined Value Error\n");
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
    if(lookAhead == ID){
        match(ID);
    }
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

void write(){
    printf("\n\tR0 = %s\n", op1);
    printf("\n\tR1 = %s\n", op2);
    printf("\n\tR0 = R0 %c R1\n", operand);
    printf("\n\t%s = R0\n\n", opcode);
}

void expression(){
    strcpy(op1, currentIDLexeme);
    term();
    while(lookAhead == PLUS || lookAhead == MINUS){
        match(lookAhead);
        strcpy(op2, currentIDLexeme);
        term();
        write(op1, op2, opcode);
    }
}

int newLookup(char* arr){
    int i = 12;
        while(myTable[i].type != NOT_FOUND){
            
            if(strcmp(arr, myTable[i].charValue) == 0){
                return 1;
            }
            i++;
        }
    return 0;
}

void intMatch(){
    while(lookAhead == INT_VAL){
        isIntMatch = 1;
        match(INT_VAL);
        
        while(lookAhead != SEMICOLON){
            match(ID);
            while(lookAhead == COMMA){
                match(COMMA);
                match(ID);
            }
        }
        
        
        isIntMatch = 0;
        match(SEMICOLON);
    }
}

void assignStmt(){
    
    if(lookAhead == INT_VAL){
        intMatch();
    }
    for(int i = 0; i < MAX; i++){
        opcode[i] = currentIDLexeme[i];
    }
    match(ID);
    if(lookAhead != EQUALS){
        error(EQUALS);
    }
    else{
        match(lookAhead);
        expression();
        match(SEMICOLON);
    }
}
