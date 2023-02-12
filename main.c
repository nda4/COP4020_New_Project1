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
    char filename[20];

    printf("Please Enter Filename: ");

    scanf("%s", filename);

    FILE * fp;
    printf("%s\n\n", filename);

    fp = fopen(filename, "r");

	// printf("Attempt:");
    if(fp == NULL){
        printf("Couldn't open file: %s\n", filename);
        return 1;
    }
    anEntry* entryTable = malloc(sizeof(anEntry));
    lookAhead = lexan(fp);
    // match(BEGIN);
    

    fclose(fp);
    free(entryTable);

    
    return 0;
}
