/*
 * Michael Newman, Mark Conley, Pavan Purohit
 * tokenizer.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef enum {false, true} Boolean;
 
/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */
 
struct TokenizerT_ {
    char *tokens;
    char *delimiters;
    int tokenIndex;   // current index in the tokens array (used when getting single tokens)
    int length;      // length of the tokens char array
};
 
typedef struct TokenizerT_ TokenizerT;
 
/*
 * TKCreate creates a new TokenizerT object for a given set of separator
 * characters (given as a string) and a token stream (given as a string).
 * 
 * TKCreate should copy the two arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */
 
TokenizerT *TKCreate(char *separators, char *ts){
    if(ts == NULL || strlen(ts) <= 0) return NULL;
 
    // Allocate memory for our tokenizer;
    TokenizerT * tk  = (TokenizerT*)malloc(sizeof(TokenizerT));
    if(!tk) return NULL;
    // send in strings, get back pointers for the vars in tk (reduce_string does the malloc)
    tk->tokens     = ts;
    tk->delimiters = separators;
 
    tk->length = strlen(tk->tokens);  // get len of token string
    tk->tokenIndex = 0;
 
    return tk;
}
 
/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */
 
void TKDestroy(TokenizerT *tk){
    if(tk == NULL)  return;
    free(tk->tokens);
    free(tk->delimiters);
    free(tk);
}
 
/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */
 
char *TKGetNextToken(TokenizerT *tk){
    if(tk == NULL) {
        return NULL;
    }
    int startIndex = tk->tokenIndex;
    if(startIndex >= (tk->length))  return NULL;  // Current index is at the end of the character array return

    char *tokenString = tk->tokens;
    char *delimString = tk->delimiters;

    // if we found a pipe send back the pipe, increment index by 1
    if(tokenString[startIndex] == '|') {
      tk->tokenIndex ++;
      char* token = (char*) malloc(sizeof(char) * 2);
      token[0] = '|';
      token[1] = '\0';
      return token;
    }

    int i;
    Boolean foundDelim = false;
    Boolean foundEnd = false;
    Boolean inSingleQuote = false;
    Boolean inDoubleQuote = false;
    Boolean foundPipe = false;

    /* Loop through the token string till we find a delimiter or the end of the string */
    for(i = startIndex; (!foundDelim && !foundEnd) || inSingleQuote || inDoubleQuote; i++) {
         if(tokenString[i] == '\0' || tokenString[i] == '\n'){  // end of string
            foundEnd = true;
            if(inSingleQuote || inDoubleQuote) { // if end of string and in a quote -> error, return NULL
                return NULL;
            }
        } else if (tokenString[i] == '\"') {  // found single quote
            if (inSingleQuote) {
                return NULL;
            } else if (inDoubleQuote) {
                i++;
                break;
            } else if (i == startIndex) {
                inDoubleQuote = true;
            } else { // found quotes middle of string
                i++;
                break;
            }
        } else if(tokenString[i] == '\'') { // found double quote
            if (inDoubleQuote) {
                return NULL;
            } else if (inSingleQuote) {
                i++;
                break;
            } else if (i == startIndex) {
                inSingleQuote = true;
            } else { // found quotes middle of string
                i++;
                break;
            }
        } else {
            char currentChar = tokenString[i];
            if(currentChar == '|' && !inSingleQuote && !inDoubleQuote) {
                foundPipe = true;
                break;
            }
            int j;

            // loop through the delimiters to check if current character is delimiter
            for(j = 0; delimString[j] != '\0'; j++){
                if(delimString[j] == currentChar){
                    foundDelim = true;
                    break;
                }
            }
        }
    }


    int tokenLength = (i - startIndex);  // get the length from the start index and current index

    if (inSingleQuote || inDoubleQuote) {  // token is two chars less cause of quotes
        tokenLength --;
        startIndex += 1;
    }
    if(foundPipe) {
        tokenLength++;
    }

    char *token = (char*) malloc( sizeof(char) * (tokenLength) );
    if (!token) {
        return NULL;
    }

    snprintf(token, tokenLength, "%s", &tokenString[startIndex]);
    
    tk->tokenIndex = i;
    return token;
}
 
/*
 * main will have two string arguments (in argv[1] and argv[2]).
 * The first string contains the separator characters.
 * The second string contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */
 
// int main(int argc, char **argv){
//     if(argc != 3){
//         printf("   ERROR:     Incorrect number of arguments \n\n");
//         printf("   Usage:     Takes in two string arguments \n");
//         printf("                    1) Sperator characters \n");
//         printf("                    2) String of tokens seperated by seperator characters \n");
//         printf("              Returns each token printed on seperate lines \n");
//         exit(-1);
//     }
 
//     /* empty string */
//     if(strlen(argv[2]) == 0){
//       exit(8);
//     }

//     TokenizerT *tk;
//     tk = TKCreate(argv[1], argv[2]);
     
//     char *token;
//     while( (token = TKGetNextToken(tk)) != NULL ){
//       printString(token);   // Print token with bracketed hex
//       free(token);         // TKGetNextToken() mallocs so we must free here
//     }
 
//     TKDestroy(tk);
//     return 0;
// }