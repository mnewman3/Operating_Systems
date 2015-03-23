#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "uthash.h"

typedef struct command * commandPtr;
struct command {
    int fd[2];
    char * args[50];
    struct command * next;

};

struct builtins_HT {
    // struct builtins key;
    char * key;
    void (*functionPtr)();
    UT_hash_handle hh; /* makes structure a hash table */
};

void runpipe(commandPtr);