#include "pars.h"

FILE * fp;
int lineNo;

int main()
{   
    
    
    char* preDefinitions[10] = {"begin", "end", ";", "+", "-", "=", "*", "/", "(", ")"};
    for(int i = 0; i < 10; i++){
        myTable[i].charValue = preDefinitions[i];
    }
    myTable[0].type = BEGIN;
    myTable[1].type = END;
    myTable[2].type = SEMICOLON;
    myTable[3].type = PLUS;
    myTable[4].type = MINUS;
    myTable[5].type = EQUALS;
    myTable[6].type = TIMES;
    myTable[7].type = DIVIDE;
    myTable[8].type = OPENQ;
    myTable[9].type = CLOSEQ;
    
    lineNo = 1; 
    char filename[20];
    printf("Please Enter Filename: (automatic)\n\n");

    scanf("%s", filename);

    fp = fopen(filename, "r");

    if(fp == NULL){
        printf("Couldn't open file: %s\n", filename);
        return 1;
    }
    anEntry* entryTable = malloc(sizeof(anEntry));
    lookAhead = lexan(fp);
    if(lookAhead == BEGIN){
        lookAhead = lexan(fp);
        while(!feof(fp) && lookAhead != END){
            assignStmt();
        }
       }
    else{
        fclose(fp);
        free(entryTable);
        error(BEGIN);
    }

    // match(BEGIN);
    printf("PROGRAM LEGAL: SUCCESS\n\n");


    fclose(fp);
    free(entryTable);

    
    return 0;
}
