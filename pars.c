#include "pars.h"
#include "Definitions"

int lookAhead = 0;
int iValue = 12;

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
    // printf("%d\t", lookAhead);
    factor();
    while(lookAhead == TIMES || lookAhead == DIVIDE){
        match(lookAhead);
        factor();
    }
}

void expression(){
    // printf("%d\t", lookAhead);
    term();
    while(lookAhead == PLUS || lookAhead == MINUS){
        match(lookAhead);
        term();
    }
}

int newLookup(char* arr){
    int i = 12;
    printf("\n->NEWLOOKUP VAL %d\n" , myTable[i].type);
        while(myTable[i].type != NOT_FOUND){
            printf("TEST\t%s\t", myTable[i].charValue);
            printf("%s\t" , arr);
            printf("%d\t", strcmp(arr, myTable[i].charValue));
            printf("%d\n" , myTable[i].type);
            if(strcmp(arr, myTable[i].charValue) == 0){
                printf("VALUE RETURNED%s\n", myTable[i].charValue);
                return 1;
            }
            // printf("%d\n", myTable[i].type);
        }
    // printf("TEST2\t%s\t", myTable[i].charValue);
    // printf("%s\t" , arr);
    // printf("%d\n", strcmp(arr, myTable[i].charValue));
    return 0;
}

void intMatch(){
    // printf("FINAL %d\n", newLookup("int"));
    while(lookAhead == INT_VAL){
        
        // printf("\nCIDLEX-T = %s\n", currentIDLexeme);
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
    match(ID);
    // printf("%d\t", lookAhead);
    if(lookAhead != EQUALS){
        error(EQUALS);
    }
    else{
        match(lookAhead);
        expression();
        match(SEMICOLON);
    }
}
