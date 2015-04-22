#define FUSE_USE_VERSION 30

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <ctype.h>
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
    char* (*op)();
    char * op_description;
    int num_args;
};
typedef struct operation operation;

operation op_table[] = {
    {"factor", factor, "Computes the prime factors of a number.\nThe file factor/n contains the prime factors of n.", 1},
    {"fib", fib, "Produce a fibonacci sequence.\nThe file fib/n contains the first n fibonacci numbers.", 1},
    {"add", add, "Adds two numbers.\nThe file add/a/b contains the sum of a plus b.", 2},
    {"sub", subtract, "Subtracts two numbers.\nThe file sub/a/b contains the difference a minus b.", 2},
    {"mul", multiply, "Multiplies two numbers.\nThe file mul/a/b contains the product of a times b.", 2},
    {"divi", divide, "Divides two numbers.\nThe file dib/a/b contains the quotient a/b.", 2},
    {"exp", exponent, "Raise a number to an exponent.\nThe file exp/a/b contains a raised to the power of b.", 2}
};

operation * get_op(char * token){
    if (token == NULL)  return NULL;
    int i;
    for (i = 0; i <= OP_TABLE_SIZE; i++){
        if (strcmp(token, op_table[i].name) == 0) {
            return &op_table[i];
        }
    }
    return NULL;
}

int isNumeric (const char * s)
{
    if (s == NULL || *s == '\0' || isspace(*s))  return 0;
    char * p;
    strtod (s, &p);
    return *p == '\0';
}

// FUSE function implementations.
static int mathfs_getattr(const char *path, struct stat *stbuf)
{
    printf("%s-- In getattr, path: %s --%s\n", KMAG, path, KNRM);

    // int ret = 0;
    // char * token;
    char * commands[NUM_ARGS+1];   // args +1 b/c space to check for extra command (invalid)

    memset(stbuf, 0, sizeof(struct stat));

    //checks to see if just root
    if(strcmp(path, "/") == 0){
        printf("%s-- Good shit, you're at the root --%s\n", KMAG, KNRM);
        stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 2;
        return 0;
    } else {
        printf("%s-- getattr: not root dir --%s\n", KMAG, KNRM);
    }

    // fills commands array
    commands[0] = strtok((char*)path, "/");
    int i;
    for (i=1; i < NUM_ARGS+1; i++) {
        commands[i] = strtok(NULL, "/");
    }

/* begin checking commands array from back to front */

    // too many args
    if (commands[3] != NULL) {
        return -ENOENT;
    }
    
    // 2nd arg - file or nothing
    else if (commands[2] != NULL) {
        if (strcmp(commands[1], "doc") == 0) {
            printf("%sdoc then more error on path: %s%s\n", KMAG, path, KNRM);
            return -ENOENT;
        }
        else if (isNumeric(commands[2]) != 0) {
            printf("%s-- valid 2nd number: %s --%s\n", KMAG, commands[2], KNRM);
            stbuf->st_mode = S_IFREG | 0444;
            stbuf->st_nlink = 1;
            stbuf->st_size = strlen(commands[2])+1;
            return 0;
        }
        else {
            return -ENOENT;
        }
    }
    
    // 1st arg - doc or (number as file or folder)
    else if (commands[1] != NULL) {
        
        operation * op = get_op(commands[0]);
        if (isNumeric(commands[1]) != 0) {
            
            if (op == NULL)  return -ENOENT;
            
            if (op->num_args == 1) {
                printf("%s-- valid 1st number as file: %s --%s\n", KMAG, commands[1], KNRM);
                stbuf->st_mode = S_IFREG | 0444;
                stbuf->st_nlink = 1;
                stbuf->st_size = strlen(commands[1])+1;
            }
            else {
                printf("%s-- valid 1st number as folder: %s --%s\n", KMAG, commands[1], KNRM);
                stbuf->st_mode = S_IFDIR | 0755;
                stbuf->st_nlink = 1;
            }
            return 0;

        }
        else if (strcmp(commands[1], "doc") == 0) {
            printf("%s-- valid doc --%s\n", KMAG, KNRM);
            stbuf->st_mode = S_IFREG | 0444;
            stbuf->st_nlink = 1;
            stbuf->st_size = strlen(op->op_description)+1;
            return 0;
        }
        else {
            return -ENOENT;
        }
    }

    // operation
    else if (get_op(commands[0]) != NULL) {
        printf("%s-- valid operation: %s --%s\n", KMAG, commands[0], KNRM);
        stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 3;
        return 0;
    }

    return -ENOENT;
}

static int mathfs_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset,
            struct fuse_file_info *fi)
{
    printf("%s-- In readdir, path: %s --%s\n", KMAG, path, KNRM);
    (void) offset;
    (void) fi;

    filler(buf, ".", NULL, 0);
    filler(buf, "..", NULL, 0);

    if (strcmp(path, "/") == 0){
        printf("%s-- In readdir at ROOT --%s\n", KMAG, KNRM);
        int i;
        for(i = 0; i < OP_TABLE_SIZE; i++){
            char * op_name = op_table[i].name;
            printf("%s-- adding: %s --%s\n", KMAG, op_name, KNRM);
            filler(buf, op_name, NULL, 0);
        }
    } 
    else if(strlen(path) > 1 && get_op((char*)path+1) != NULL){
        filler(buf, "doc", NULL, 0);
    } 

    return 0;
}       

static int mathfs_open(const char *path, struct fuse_file_info *fi)
{
    printf("%s-- In open, path: %s --%s\n", KMAG, path, KNRM);

    /* 
     * Should only need to check for the flags b/c fuse calls getattr to verify is a 
     * valid file before attempting to open
     */
    if ((fi->flags & 3) != O_RDONLY) {
        return -EACCES;
    }

    return 0;
}

static int mathfs_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
    printf("%s-- In read, path: %s --%s\n", KMAG, path, KNRM);

    // size_t len;
    (void) fi;

    // lookup file size

    /* Comented out for testing - do not remove */
    // len = strlen(hello_str);
    // if (offset < len) {
    //     if (offset + size > len)
    //         size = len - offset;
    //     memcpy(buf, hello_str + offset, size);
    // } else
    //     size = 0;

    // return size;

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
