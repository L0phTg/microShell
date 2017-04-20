#include "shell.h"
#include "job.h"
#include "pack.h"

extern int verbose;

void sigint_handler(int sig)
{
    if (verbose)
        printf("sigint_handler: shell caught SIGINT\n");
}

void sigtstp_handler(int sig)
{
    if (verbose)
        printf("sigtstp_handler: shell caught SIGTSTP\n");
}

void sigchld_handler(int sig)
{
    int status;
    pid_t pid;
    
    if (verbose)
        printf("sigchld_handler: entering \n");

    while((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        deletejob(jobs, pid);
        if (verbose)
            printf("sigchld_handler: job %d deleted\n", pid);
    }
    
    if (!((pid == 0) || (pid == -1 && errno == ECHILD)))
        unix_error("sigchld_handler wait error");

    if (verbose) 
        printf("sigchld_handler: exiting\n");

    return ;
}
