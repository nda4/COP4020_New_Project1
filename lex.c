#include "lex.h"
#include "pars.h"


#define nameLength 30
char* currentIDLexeme;


int lexan(FILE *fp){
    int numLexeme[MAX];
    char idLexeme[MAX];
    int numLexemeID;
    int type;

    int idLexemeID;
    char nextChar;

    //  for(int i = 0; i < 11; i++){
    //     // myTable[i].charValue = preDefinitions[i];
    //     printf("%s\n" , myTable[i].charValue);
    //     printf("%d\n" , myTable[i].type);
    // }
    
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
                // printf("%c", nextChar);
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
            // printf("%s ", idLexeme);
            currentIDLexeme = ("%s", idLexeme);
            // printf("%s " , currentIDLexeme);
            if(newLookup(currentIDLexeme) != 0){
                // printf("CHECK HERE%s\n",  currentIDLexeme);
                error(REDEF);
            }

            type = lookup(idLexeme);
            // printf("\t");
            return type;
        }
        else if (nextChar == EOF){
            return DONE;
        }
    }while(!feof(fp));
    return 0;
}

int lookup(char* arr){
    // printf("BEEG TEST = %s\n" , myTable[6].charValue);
    int i = 0;
    do{
        if(strcmp(arr, myTable[i].charValue) == 0){
            // printf("Ival = %d\n", i);
            // printf("%s\n" , myTable[i].charValue);
            // printf("%d\n" , myTable[i].type);
            return myTable[i].type;
        }
        i++;
    }while(myTable[i].type != NOT_FOUND);
    myTable[i].charValue = ("%s", arr);
    myTable[i].type = ID;
    myTable[i+1].type = NOT_FOUND;
    printf("\n***\n'%s' inserted at slot ", arr);
    printf("%d\n", i);
    printf("%s\n", myTable[i].charValue);
    printf("%d==", i+1);
    printf("%d\n***\n", myTable[i+1].type);
    return ID;
}


