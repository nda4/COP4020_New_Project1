/*
    Main() was written specifically for the files provided by the project.
    As such, it is hardcoded to not accept any other files except those
    named by the project. Aka a1-a8.
*/
#include "pars.h"

int main()
{   
    char* preDefinitions[2] = {"begin", "end"};
    for(int i = 0; i < 2; i++){
        myTable[i].charValue = preDefinitions[i];
    }
    // printf("%s", myTable[0].charValue);
    // printf("%s", myTable[1].charValue);
    

    FILE * fp;
    int i = 1;
    char filename[2];

    while(i < 9){
        filename[0] = 'a';
        filename[1] = i + '0';
        fp = fopen(filename, "r");
	printf("Attempt: %d\n", i);
        if(fp == NULL){
            printf("Couldn't open file: %s\n", filename);
            return 1;
        }
        anEntry* entryTable = malloc(sizeof(anEntry));
        lookAhead = lexan(fp);
        // match(BEGIN);
        

        fclose(fp);
        free(entryTable);
        i++;
    }
    

    
    return 0;
}
