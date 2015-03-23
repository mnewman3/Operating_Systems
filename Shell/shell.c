#include <stdio.h>
#include <string.h>
#include "tokenizer.c"

#define KNRM  "\x1B[0m"
#define KCYN  "\x1B[36m"
#define NUM_ARG 50
#define MAX_LEN 50
#define NUM_SEPERATORS 10

int main(int argc, char **argv) { 
    printf("\n");
    while (1) {
        printf("%s$%s ", KCYN, KNRM);

        char* str = (char*) malloc(sizeof(char) * MAX_LEN);
        char* seperators = (char*) malloc(sizeof(char) * NUM_SEPERATORS);
        seperators[0] = ' ';

        int i;
        fgets(str, MAX_LEN, stdin);

        if (strlen(str) <= 1) {
            continue;
        }

        TokenizerT *tk;
        tk = TKCreate(seperators, str);
         
        char *token;
        while( (token = TKGetNextToken(tk)) != NULL ){
            // printString(token);   // Print token with bracketed hex
            if(strlen(token) == 0) {
                continue;
            }
            printf("%s\n", token);
            free(token);         // TKGetNextToken() mallocs so we must free here
        }

        TKDestroy(tk);
    }

    return 0;
}