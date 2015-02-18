/*
* Test program for testing system calls and trace system call
*/
#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"


int stdout = 1;

int
main(int argc, char *argv[]) 
{
	// test code goes here
	printf(stdout, "printing stuff\n");
	printf(stdout, "enabling tracing\n");
	printf(stdout, "system calls from proc: %d\n", trace(1));
	printf(stdout, "printing again\n");
	printf(stdout, "and again\n");
	
	int pid;
	pid = fork();
	if(pid == 0){
		printf(stdout, "in child\n");
	} else {
		printf(stdout, "in parent...killing child\n");
		kill(pid);
		printf(stdout, "waiting...\n");
		wait();
	}
	return 0;
}