#include "SymbolTable"
#include "Definitions"
#include "lex.h"

// #define ID    300
// #define NUM   301
// #define BEGIN 400
// #define END   401
// #define DONE  500
// #define NOT_FOUND -1



#define nameLength 30
anEntry myTable[TABLELENGTH / sizeof(anEntry)];

int lineNo = 0;
int lexan(FILE *fp){
    // struct entry entryTable[TABLELENGTH];
    
    int* numLexeme;
    char idLexeme[MAX];
    
    lineNo++;
    int numLexemeID;
    int type;

    int idLexemeID;
    char nextChar;
    
    do{
        numLexemeID = 0;
        idLexemeID = 0;

        nextChar = fgetc(fp);
        // printf("%c ", nextChar);
            
        if(nextChar == '\n'){
            // printf("test1");
            lineNo++;
        }
        else if(nextChar == '~'){
            // printf("test2");
            do{
                nextChar = fgetc(fp);
            }while(nextChar != '\n');
        }
        else if(isdigit(nextChar) != 0){
            // printf("test3");
            do{
                numLexeme[numLexemeID]=nextChar;
                numLexemeID++;
                nextChar = fgetc(fp);
            }while(isdigit(nextChar) != 0);
            ungetc(nextChar, fp); 
            return NUM;
        }
        else if(isalpha(nextChar) != 0){
            // printf("test4");
            do{
                idLexeme[idLexemeID] = nextChar;
                idLexemeID++;
                nextChar = fgetc(fp);
            }while(isalpha(nextChar) != 0);
            ungetc(nextChar, fp);
            type = lookup(idLexeme);
            return type;
        }
        else if (nextChar == EOF){
            // printf("test5");
            return DONE;
        }
        else{
            // printf("test6");
            return nextChar;
        }
    }while(!feof(fp));
    return 0;
}

int lookup(char* arr){
    int i = 0;
    do{
        // printf("%s\n", arr);
        // printf("%d\n\n", strcmp(arr, myTable[i].charValue));
        if(strcmp(arr, myTable[i].charValue) == 127){
            // printf("\npos\n\n");
            return myTable[i].type;
        }
        i++;
    }while(myTable[i].type != 0);
    myTable[i].charValue = arr;
    myTable[i].type = ID;
    // printf("\n\n\n");
    
    // printf("\n%s\n", myTable[i].charValue);
    // printf("\n%d\n", myTable[i].type);
    return ID;
}

//The following is specifically the symbol table


