// Michael Newman, Mark Conley, Pavan Purohit
#include "test2.h"

builtinsPtr ht = NULL;

void runpipe(commandPtr comm){
    int pid;

    if(pipe(comm->fd) == 0){

        switch(pid = fork()){
            case 0: /* child process */
                dup2(comm->fd[0], 0);
                close(comm->fd[1]);
                execvp(comm->next->args[0], comm->next->args);
                exit(0);
            default: /* parent */
                dup2(comm->fd[1], 1);
                close(comm->fd[0]);
                execvp(comm->args[0], comm->args);
                exit(0);
            case -1:
                perror("fork");
                exit(1);
        }

    }else{
        //pipe failed
    }
}

int runfork(commandPtr comm) {
    int pid = fork();
    switch(pid) {
        case 0: /* child process */
            printf("in child\n");
            runpipe(comm);
        default: /* parent */
            printf("in parent\n");
        case -1:
            perror("fork");
            exit(1);
    }
    return pid;
}

void runcommand(commandPtr comm) {
    if(comm == NULL)  return;

    builtinsPtr search;
    // builtin
    if(HASH_FIND_STR(ht, (comm->args[0]), search) != NULL) {
        if (comm->next != NULL) {
            printf("error, builtin functions take one parameter\n");
            return;
        } else {
            (search->functionPtr)(comm);
        }
    } else { // not builtin
        runfork(comm);
    }

}


/* initilizes built in commands cd and exit */
void initializeHT(){

    builtinsPtr builtin_cd = (builtinsPtr)malloc(sizeof(struct builtins));
    builtin_cd->key = (char *)malloc(sizeof("cd"));
    builtin_cd->key = "cd";
    builtin_cd->functionPtr = &my_changeDir;

    HASH_ADD_STR(ht, key, builtin_cd);

    builtinsPtr builtin_exit = (builtinsPtr)malloc(sizeof(struct builtins));
    builtin_exit->key = (char *)malloc(sizeof("exit"));
    builtin_exit->key = "exit";
    builtin_exit->functionPtr = &my_exit;

    HASH_ADD_STR(ht, key, builtin_exit);

}

int my_changeDir(commandPtr command){

    /* invalid number of arguments */
    if(command->argcount > 2){
        printf("error: too many arguments\n");
        return 0;
    }

    /* goto home directory */
    if(command->argcount == 1){
        if(chdir(getenv("HOME")) == 0) {
            return 1;
        } else {
            printf("error: unable to return to home directory\n");
            return 0;
        }
    }

    /* successful change of dir */
    if(chdir(command->args[1]) == 0){
        return 1;
    } 

    /* unable to change directory */
    return 0;

}

int my_exit(commandPtr command){

    if(command->args[1] == NULL){
        exit(0);
    }

    exit(atoi(command->args[1]));
}

int main(void){
    initializeHT();


    return 0;
}