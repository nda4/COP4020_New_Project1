#include "lex.h"
#include "pars.h"


#define nameLength 30
anEntry myTable[TABLELENGTH / sizeof(anEntry)];


int lexan(FILE *fp){
    int numLexeme[MAX];
    char idLexeme[MAX];
    int numLexemeID;
    int type;

    int idLexemeID;
    char nextChar;
    
    do{
        int uSwitch = 0;
        numLexemeID = 0;
        idLexemeID = 0;

        nextChar = fgetc(fp);
        if(nextChar == '\n'){
            lineNo++;
        }
        else if(nextChar == ';'){
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
        else if(nextChar == ' ' || nextChar == '\t'){
        }
        else if(nextChar == '~'){
            do{
                nextChar = fgetc(fp);
            }while(nextChar != '\n');
            ungetc(nextChar, fp);
        }
        else if(isdigit(nextChar)){
            do{
                numLexeme[numLexemeID]=nextChar;
                numLexemeID++;
                nextChar = fgetc(fp);
            }while(isdigit(nextChar));
            numLexeme[numLexemeID] = '\0';
            ungetc(nextChar, fp); 
            return NUM;
        }
        else if((isalpha(nextChar) != 0 || nextChar == '_') && nextChar != '\n' && nextChar != ';' && nextChar != ' '){
            if(nextChar == '_')
                error(ENDUNDER);
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
            ungetc(nextChar, fp);
            if(uSwitch == 1){
                error(ENDUNDER);
            }
            idLexeme[idLexemeID] = '\0';
            type = lookup(idLexeme);
            return type;
        }
        else if (nextChar == EOF){
            return DONE;
        }
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
    myTable[i].charValue = ("%s", arr);
    myTable[i].type = ID;
    return ID;
}


