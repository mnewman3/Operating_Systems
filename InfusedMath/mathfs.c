#define FUSE_USE_VERSION 30

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <fuse/fuse.h>

#define OP_TABLE_SIZE 7
#define NUM_ARGS 3

struct operation {
    char * name;
    char * (*op)();
    char * opDescription;
};
typedef struct operation operation;

const operation op_table[] = {
    {"factor", factor, "Computes the prime factors of a number.\nThe file factor/n contains the prime factors of n."},
    {"fib", fib, "Produce a fibonacci sequence.\nThe file fib/n contains the first n fibonacci numbers."},
    {"add", add, "Adds two numbers.\nThe file add/a/b contains the sum of a plus b."},
    {"sub", subtract, "Subtracts two numbers.\nThe file sub/a/b contains the difference a minus b."},
    {"mul", multiply, "Multiplies two numbers.\nThe file mul/a/b contains the product of a times b."},
    {"divi", divide, "Divides two numbers.\nThe file dib/a/b contains the quotient a/b."},
    {"exp", exponent, "Raise a number to an exponent.\nThe file exp/a/b contains a raised to the power of b."}
};

// FUSE function implementations.
static int mathfs_getattr(const char *path, struct stat *stbuf)
{

    int ret = 0;
    char * commands[NUM_ARGS];

    memset(stbuf, 0, sizeof(struct stat));

    //checks to see if just 
    if(strcmp(path, "/") == 0){
        stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 2;
        return 0;
    }

    commands = strtok(path, "/");

    while( commands != NULL ){


        
        commands = strtok(NULL, path);
   }

    for(int i = 0; i <= OP_TABLE_SIZE; i++){

        //invalid operation do something
        if(i == OP_TABLE_SIZE){

        }

        //char * curr = op_table[i].name;
        operation * op_ptr = op_table[i];
        if(strcmp(op_ptr->name, commands) == 0){

        }
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
