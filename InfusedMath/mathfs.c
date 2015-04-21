#define FUSE_USE_VERSION 30

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <fuse/fuse.h>
#include "math_ops.c"

#define OP_TABLE_SIZE 7
#define NUM_ARGS 3

struct operation {
    char * name;
    char * (*op)();
    char * op_description;
    int num_args;
};
typedef struct operation operation;

const operation op_table[] = {
    {"factor", factor, "Computes the prime factors of a number.\nThe file factor/n contains the prime factors of n.", 1},
    {"fib", fib, "Produce a fibonacci sequence.\nThe file fib/n contains the first n fibonacci numbers.", 2},
    {"add", add, "Adds two numbers.\nThe file add/a/b contains the sum of a plus b.", 2},
    {"sub", subtract, "Subtracts two numbers.\nThe file sub/a/b contains the difference a minus b.", 2},
    {"mul", multiply, "Multiplies two numbers.\nThe file mul/a/b contains the product of a times b.", 2},
    {"divi", divide, "Divides two numbers.\nThe file dib/a/b contains the quotient a/b.", 2},
    {"exp", exponent, "Raise a number to an exponent.\nThe file exp/a/b contains a raised to the power of b.", 2}
};

operation * is_valid_op(char * token){
    int i;
    for(i = 0; i <= OP_TABLE_SIZE; i++){
        if(strcmp(token, op_table[i]->name) == 0) {
            return op_table[i];
        }
    }
    return NULL;
}

// FUSE function implementations.
static int mathfs_getattr(const char *path, struct stat *stbuf)
{

    int ret = 0;
    char * token;
    char * commands[NUM_ARGS];

    memset(stbuf, 0, sizeof(struct stat));

    //checks to see if just
    if(strcmp(path, "/") == 0){
        stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 2;
        return 0;
    }
    
    char * p = path;
    token = strtok(p, "/");
    
    // check if valid cmd from struct
    operation * op = is_valid_op(token);

    // for(int i = 0; i <= OP_TABLE_SIZE; i++){
    //     if(strcmp(token, op_table[i].name) == 0) {
    //         op = op_table[i];
    //         break;
    //     }
    // }

    if(op == NULL) {
        // dis bad -> error
    }

    int i;
    for(i = 0; i < op->num_args; i++) {
        
        token = strtok(NULL, "/");

        commands[i] = token;
    }

    //error shouldn't happen do stuff
    token = strtok(NULL, "/");
    if(token == NULL){

    }

    //check if doc
    if(strcmp(commands[1], "doc") == 0){
        printf("%s",op->op_description);
    }
    

    return ret;

}

static int mathfs_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset,
            struct fuse_file_info *fi)
{
    (void) offset;
    (void) fi;

}       

static int mathfs_open(const char *path, struct fuse_file_info *fi)
{

}

static int mathfs_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
    (void) fi;

}

static struct fuse_operations mathfs_oper = {
    .getattr = mathfs_getattr,
    .readdir = mathfs_readdir,
    .open = mathfs_open,
    .read = mathfs_read,
};

int main(int argc, char **argv)
{
    return fuse_main(argc, argv, &mathfs_oper, NULL);
}
