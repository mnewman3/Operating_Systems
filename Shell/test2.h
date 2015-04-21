// Michael Newman, Mark Conley, Pavan Purohit
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
    int argcount;
    struct command * next;

};

typedef struct builtins * builtinsPtr;
struct builtins {
    // struct builtins key;
    char * key;
    int (*functionPtr)();
    UT_hash_handle hh; /* makes structure a hash table */
};

void runpipe(commandPtr);

int my_changeDir(commandPtr);

int my_exit(commandPtr);