#include "test2.h"


void runpipe(commandPtr comm){
    int pid;

    if(pipe(comm->fd) == 0){

        switch(pid = fork()){
            case 0: /* child process */
                dup2(comm->fd[0], 0);
                close(comm->fd[1]);
                execvp(comm->args[0], comm->args);
                exit(0);
            default: /* parent */
                dup2(comm->fd[1], 1);
                close(comm->fd[0]);
                execvp(comm->next->args[0], comm->next->args);
                exit(0);
            case -1:
                perror("fork");
                exit(1);
        }

    }else{
        //pipe failed
    }
}

builtinsPtr ht = NULL;

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

void my_changeDir(){

}

void my_exit(){

}
int main(void){
    initializeHT();


    return 0;
}