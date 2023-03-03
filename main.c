//Noah Daniel Arwine
//COP4020_Spring_2023
//Project 1
//Lexical Analyser and Parser


#include "pars.h"



/*
    Naturally, main is used to run the program. It initilizes by hard defining 10 items to be kept in the identifier struct. I am unsure
    if that will be needed for the second project.
*/

FILE * fp;
int lineNo;

anEntry myTable[TABLELENGTH / sizeof(anEntry)];

int main()
{   
    
    
    char* preDefinitions[12] = {"begin", "end", ";", "+", "-", "=", "*", "/", "(", ")", "int", ","};
    for(int i = 0; i < 13; i++){
        myTable[i].charValue = preDefinitions[i];
        // printf("%s\n" , myTable[i].charValue);
        // printf("%d\n" , myTable[i].type);
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
    myTable[10].type = INT_VAL;
    myTable[11].type = COMMA;
    myTable[12].type = NOT_FOUND;

    // printf("\n**********\nPrelim Values: \n");
    for(int i = 0; i < 13; i++){
        myTable[i].charValue = preDefinitions[i];
        // printf("Slot %d\t", i);
        // printf("%s\t" , myTable[i].charValue);
        // printf("%d\n" , myTable[i].type);
    }
    // printf("END Prelim Values\n**********\n\n");

    // printf("TEST1\t%d", myTable[10].type);
    
    lineNo = 1; 
    char filename[20];
    printf("Please Enter Filename: (automatic)\n");

    scanf("%s", filename);
    printf("\n");

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
