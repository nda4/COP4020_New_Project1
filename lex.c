#include "lex.h"
#include "pars.h"

// #define ID    300
// #define NUM   301
// #define BEGIN 400
// #define END   401
// #define DONE  500
// #define NOT_FOUND -1



#define nameLength 30
anEntry myTable[TABLELENGTH / sizeof(anEntry)];


int lexan(FILE *fp){
    // struct entry entryTable[TABLELENGTH];
    int numLexeme[MAX];
    char idLexeme[MAX];
    // lineNo++;
    int numLexemeID;
    int type;

    int idLexemeID;
    char nextChar;
    
    do{
        int uSwitch = 0;
        // printf("TEST");
        numLexemeID = 0;
        idLexemeID = 0;

        nextChar = fgetc(fp);
        // printf("\nVALUE: %c\n", nextChar);
        // printf("TEST");
        if(nextChar == '\n'){
            // printf("NEWLINE");
            lineNo++;
        }
        else if(nextChar == ' ' || nextChar == '\t'){
            // printf("SPACE");
        }
        else if(nextChar == '~'){
            // printf("TILDA");
            do{
                nextChar = fgetc(fp);
                // printf("%c", nextChar);
            }while(nextChar != '\n');
            ungetc(nextChar, fp);
        }
        else if(isdigit(nextChar)){
            // printf("DIGIT RUNNER");
            do{
                numLexeme[numLexemeID]=nextChar;
                numLexemeID++;
                nextChar = fgetc(fp);
                // printf("%c", nextChar);
            }while(isdigit(nextChar));
            numLexeme[numLexemeID] = '\0';
            ungetc(nextChar, fp); 
            // printf("%c", nextChar);
            return NUM;
        }
        else if((isalpha(nextChar) != 0 || nextChar == '_') && nextChar != '\n' && nextChar != ';' && nextChar != ' '){
            if(nextChar == '_')
                error(ENDUNDER);
            // printf("ALPHA");
            do{
                idLexeme[idLexemeID] = nextChar;
                idLexemeID++;
                nextChar = fgetc(fp);
                if(nextChar == '_' && uSwitch != 1)
                    uSwitch = 1;
                else if(nextChar == '_' && uSwitch == 1)
                    exit(DOUBLEUNDER);
                if((isalpha(nextChar) != 0 || nextChar != '_') && nextChar != '\n' && nextChar != ';' && nextChar != ' ')
                    uSwitch = 0;
            }while((isalpha(nextChar) != 0 || nextChar == '_') && nextChar != '\n' && nextChar != ' ' && nextChar != ';');
            if(uSwitch == 1){
                // printf("ENDED HERE: %d\n", ENDUNDER);
                error(ENDUNDER);
            }
            idLexeme[idLexemeID] = '\0';
            ungetc(nextChar, fp);
            type = lookup(idLexeme);
            return type;
        }
        else if (nextChar == EOF){
            // printf("EOF");
            return DONE;
        }
        else if(nextChar == ';'){
            // printf("SEMICOLON");
            return SEMICOLON;
        }
        else if(nextChar == '+')
            return PLUS;
        else if(nextChar == '-')
            return MINUS;
        else if(nextChar == '*')
            return TIMES;
        else if(nextChar == '/')
            return DIVIDE;
        else if(nextChar == '(')
            return OPENQ;
        else if(nextChar == ')')
            return CLOSEQ;
        else if(nextChar == '=')
            return EQUALS;
    }while(!feof(fp));
    return 0;
}

int lookup(char* arr){
    int i = 0;
    do{
        if(strcmp(arr, myTable[i].charValue) == 0){
            return myTable[i].type;
        }
        i++;
    }while(myTable[i].type != 0);
    myTable[i].charValue = ("%s\0", arr);
    myTable[i].type = ID;
    // printf("TEST2");
    return ID;
}

//The following is specifically the symbol table


