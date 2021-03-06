#define _GNU_SOURCE 
#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#define STACK_SIZE (1024* 1024)

static char child_stack[STACK_SIZE];
char *const child_args[] = {
   "/bin/bash",
    NULL
};

int child_main(void* args)
{
    printf("in child process\n");
    sethostname("NewNamespace",12);
    execv(child_args[0],child_args);
    return 1;
}

int main()
{
    printf("start process!\n");
    int child_pid = clone(child_main,child_stack + STACK_SIZE,CLONE_NEWIPC | CLONE_NEWUTS |CLONE_NEWPID|CLONE_NEWNS| SIGCHLD,NULL);
    waitpid(child_pid,NULL,0);
    printf("has quited\n");
    return 0;
}   

