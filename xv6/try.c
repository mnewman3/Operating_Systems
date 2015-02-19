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
		printf(stdout, "--IN CHILD--\n");
		printf(stdout, "this should not have tracing enabled\n");
		exit();
	} else {
		printf(stdout, "IN PARENT...killing child\n");
		printf(stdout, "waiting for child to die...\n");
		wait();
	}
	printf(stdout, "disabling tracing...\n-- system calls from proc: %d --\n", trace(0));
	printf(stdout, "tracing disabled\n");
	printf(stdout, "-- system calls from proc: %d --\n", trace(0));
	printf(stdout, "-- system calls from proc: %d --\n", trace(0));
	return 0;
}