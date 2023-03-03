#include "pars.h"
#include "Definitions"

int lookAhead = 0;
int iValue = 12;
int isIntMatch = 0;
char* op1;
char* op2;
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
    printf("\n");
    exit(1);
}

void match(int t){
    // printf("%d->%d\n", lookAhead, t);
    if(lookAhead == t){
        lookAhead = lexan(fp);
    }
    else{
        printf("Syntax ");
        error(t);
    }
}

void factor(){
    // printf("%d\t", lookAhead);
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
    // printf("%d\t", lookAhead);
    factor();
    while(lookAhead == TIMES || lookAhead == DIVIDE){
        match(lookAhead);
        factor();
    }
}

void write(){
    printf("\n\tr0 = %s\n", op1);
    printf("\n\tr1 = %s\n", op2);
    printf("\n\tr0 = %s + %s\n", op1, op2);
    printf("\n\t%s = r0\n\n", opcode);
}

void expression(){
    // printf("%d\t", lookAhead);
    // printf("PREPRE TEST = %s\n\n", currentIDLexeme);
    op1 = strdup(currentIDLexeme);
    // printf("&\nTEST = %s\n&", op1);
    term();
    while(lookAhead == PLUS || lookAhead == MINUS){
        match(lookAhead);
        // printf("PRETEST = %s", currentIDLexeme);
        op2 = strdup(currentIDLexeme);
        // printf("&\nTEST2 = %s\n&", op2);
        term();
        write(op1, op2, opcode);
    }
}

int newLookup(char* arr){
    int i = 12;
        if(myTable[i].type != NOT_FOUND)
            // printf("\nVal at slot %d = %s\n", i, myTable[i].charValue);
        while(myTable[i].type != NOT_FOUND){
            
            if(strcmp(arr, myTable[i].charValue) == 0){
                return 1;
            }
            i++;
            // printf("%d\n", myTable[i].type);
        }
    // printf("TEST2\t%s\t", myTable[i].charValue);
    // printf("%s\t" , arr);
    // printf("%d\n", strcmp(arr, myTable[i].charValue));
    return 0;
}

void intMatch(){
    while(lookAhead == INT_VAL){
        isIntMatch = 1;
        match(INT_VAL);
        
        while(lookAhead != SEMICOLON){
            // printf("%d ", lookAhead);
            // printf("\nCIDLEX = %s\n", currentIDLexeme);
            // if(newLookup(currentIDLexeme) != 1){
            //     error(REDEF);
            // }
            match(ID);
            // printf("LOOK2 = %d\n" ,lookAhead);
            // printf("\nBefore Comma: %d\n" , lookAhead);
            // printf("%d", COMMA);
            while(lookAhead == COMMA){
                match(COMMA);
                // printf("\nCIDLEX2 = %s\n", currentIDLexeme);
                // if(newLookup(currentIDLexeme) != 1){
                //     error(REDEF);
                // }
                match(ID);
            }
        }
        
        // printf("BEFORE SEMI %d\n", lookAhead);
        
        isIntMatch = 0;
        match(SEMICOLON);
        // printf("TEST");
    }
}

void assignStmt(){
    // printf("TEST%d\t" , lookAhead);
    if(lookAhead == INT_VAL){
        
        // printf("TEST %s", currentIDLexeme);
        intMatch();
    }
    // printf("MEDIUMRARE STEAK IS BEST CO/OKED A LITTLE = %s\n", currentIDLexeme);
    for(int i = 0; i < MAX; i++){
        opcode[i] = currentIDLexeme[i];
    }
    // printf("Test-1 = %s\n", opcode);
    match(ID);
    // printf("%d\t", lookAhead*;
    if(lookAhead != EQUALS){
        error(EQUALS);
    }
    else{
        match(lookAhead);
        expression();
        match(SEMICOLON);
    }
}
