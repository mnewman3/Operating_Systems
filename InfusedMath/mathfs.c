#define FUSE_USE_VERSION 30

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <fuse/fuse.h>

#include "math_ops.c"

// COLORS!!!!11!!!!!!111
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define OP_TABLE_SIZE 7
#define NUM_ARGS 3

struct operation {
    char * name;
    void (*op)();
    char * op_description;
    int num_args;
};
typedef struct operation operation;

operation op_table[] = {
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
        if(strcmp(token, op_table[i].name) == 0) {
            return &op_table[i];
        }
    }
    return NULL;
}

// FUSE function implementations.
static int mathfs_getattr(const char *path, struct stat *stbuf)
{
    printf("%s-- In getattr, path: %s --%s\n", KMAG, path, KNRM);
    int ret = 0;
    char * token;
    char * commands[NUM_ARGS-1];   // args -1 b/c dont store command in here

    memset(stbuf, 0, sizeof(struct stat));

    //checks to see if just
    if(strcmp(path, "/") == 0){
        printf("%s-- Good shit, you're at the root --%s\n", KMAG, KNRM);
        stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 2;
        return 0;
    } else {
        printf("%s-- getattr: not root dir --%s\n", KMAG, KNRM);
    }

    token = strtok((char*)path, "/");

    // check if valid cmd from struct
    operation * op = is_valid_op(token);

    // invalid operation = no entry error
    if(op == NULL) {
        printf("%s-- Error: invalid operation dumbass --%s\n", KMAG, KNRM);
        return -ENOENT;
    } else {
        printf("%s-- getattr: valid operation --%s\n", KMAG, KNRM);
    }

    // fill array with arguments
    int i;
    for(i = 0; i < (op->num_args); i++) {
        token = strtok(NULL, "/");
        commands[i] = token;
        printf("%s-- arg%d : %s --%s\n", KMAG, i, token, KNRM);
    }

    // check if path is operation folder
    if(commands[0] == NULL) {
        printf("%s-- Good shit, you're in the operation folder: %s --%s\n", KMAG, path, KNRM);
        stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 3;
        return 0;
    }

    printf("%s-- getattr: finished filling args array --%s\n", KMAG, KNRM);

    // check if has more arguments than can take in
    token = strtok(NULL, "/");
    if(token != NULL){
        printf("%s-- Error: too many args --%s\n", KMAG, KNRM);
        return -ENOENT;
    } else {
        printf("%s-- getattr: valid number of args --%s\n", KMAG, KNRM);
    }

    // check if doc
    if(strcmp(commands[0], "doc") == 0){
        if(commands[1] != NULL) {
            printf("%s-- Error: docs and too many args --%s\n", KMAG, KNRM);
            return -ENOENT;
        }
        printf("%s-- valid doc has: %s --%s\n", KMAG, op->op_description, KNRM);
        stbuf->st_mode = S_IFREG | 0444;
        stbuf->st_nlink = 1;
        stbuf->st_size = strlen(op->op_description);
        return 0;
    } 
    

    return ret;

}

static int mathfs_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset,
            struct fuse_file_info *fi)
{
    printf("%s-- In readdir, path: %s --%s\n", KMAG, path, KNRM);
    (void) offset;
    (void) fi;
    return 0;

}       

static int mathfs_open(const char *path, struct fuse_file_info *fi)
{
    printf("%s-- In open, path: %s --%s\n", KMAG, path, KNRM);
    return 0;

}

static int mathfs_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
    printf("%s-- In read, path: %s --%s\n", KMAG, path, KNRM);
    (void) fi;
    return 0;

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
