#include <stdio.h>
#include <string.h>
#include "tokenizer.c"

#define KNRM  "\x1B[0m"
#define KCYN  "\x1B[36m"
#define NUM_ARG 50
#define MAX_LEN 50

// int run_command(char** params)
// {
//     pid_t pid = fork();
//     if (pid == -1) {
//         char* error = strerror(errno);
//         printf("fork: %s\n", error);
//         return 1;
//     }else if (pid == 0) {
//         // Execute command
//         execvp(params[0], params);  

//         // Error occurred
//         char* error = strerror(errno);
//         printf("shell: %s: %s\n", params[0], error);
//         return 0;
//     }

//     // Parent process
//     else {
//         // Wait for child process to finish
//         int childStatus;
//         waitpid(pid, &childStatus, 0);
//         return 1;
//     }
// }

int main(int argc, char **argv) { 
    printf("\n");
    while (1) {
        printf("%s$%s ", KCYN, KNRM);

        char str[MAX_LEN];
        int i;
        fgets(str, MAX_LEN, stdin);

        if (strlen(str) <= 1) {
            continue;
        }

        /* remove newline, if present */
        // i = strlen(str)-1;
        // if( str[ i ] == '\n') {
        //   str[i] = '\0';
        // }

        printf("This is your string: %s\n", str);

        TokenizerT *tk;
        tk = TKCreate(" ", str);
         
        char *token;
        while( (token = TKGetNextToken(tk)) != NULL ){
            // printString(token);   // Print token with bracketed hex
            free(token);         // TKGetNextToken() mallocs so we must free here
        }

        TKDestroy(tk);
    }

    return 0;
}