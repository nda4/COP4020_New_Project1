#include "lex.h"
#include "pars.h"


#define nameLength 30
char* currentIDLexeme;
int firstDef = 0;

char operand;


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
        else if(nextChar == '+'){
            operand = '+';      
            return PLUS; 
    }
        else if(nextChar == '-'){
            operand = '-';    
            return MINUS;   
    }
        else if(nextChar == '*'){
            operand = '*';
            return TIMES;       
    }
        else if(nextChar == '/'){
            operand = '/'; 
            return DIVIDE;      
    }
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
            for(int i = 0; i < 10; i++){
                currentIDLexeme[i] = numLexeme[i];
            }
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
                if((isalpha(nextChar) != 0 || nextChar != '_' || isdigit(nextChar) != 0) && nextChar != '\n' && nextChar != ';' && nextChar != ' ')
                    uSwitch = 0;
            }while((isalpha(nextChar) != 0 || nextChar == '_' || isdigit(nextChar) != 0) && nextChar != '\n' && nextChar != ' ' && nextChar != ';');
            ungetc(nextChar, fp);
            if(uSwitch == 1){
                error(ENDUNDER);
            }
            idLexeme[idLexemeID] = '\0';
            currentIDLexeme = ("%s", idLexeme);
            
            if(isIntMatch == 1){
                if(newLookup(currentIDLexeme) != 0)
                    error(REDEF);
                firstDef = 1;
            }

            type = lookup(idLexeme);
            firstDef = 0;
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
    }while(myTable[i].type != NOT_FOUND);
    if(firstDef == 0)
        error(UNDEF);
    myTable[i].charValue = strdup(arr);
    myTable[i].type = ID;
    myTable[i+1].type = NOT_FOUND;

    

    return ID;
}


