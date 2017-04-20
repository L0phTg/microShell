/**
 * shell1.c --      second times
 * @author    sexp
 *            2016-09-21
 */
#include "job.h"
#include "pack.h"
#include "shell.h"
#include "sig_handler.h"
#include "parseval.h"

extern char **environ;
extern int verbose;

void usage()
{
    fprintf(stderr, "cmd need + [-v]\n");
    exit(0);
}

int parseline(const char *cmdline, char **argv)
{
    char array[MAXLINE];  /* holds local copy of command line */
    char *buf = array;
    int bg = 0;
    int argc = 0;
    char *mim;

    strcpy(buf, cmdline);
    buf[strlen(buf)-1] = ' ';
    while(*buf && *buf == ' ')
        buf++;

    while((mim = strchr(buf, ' '))){
        argv[argc++] = buf;
        *mim = '\0';                // noice
        buf = mim + 1;
        while(*buf && *buf == ' ')
            buf++;
    }
    argv[argc] = NULL;
    
    if (argc == 0)
        return 1;

    if ((bg = (*argv[argc-1] == '&')) != 0)
        argv[--argc] = NULL;

    return bg;
}
void waitfg(pid_t pid)
{
    int status;
    if (waitpid(pid, &status, WUNTRACED) < 0)
        printf("waitfg: waitpid error");

    if (WIFSTOPPED(status)){
        sprintf(sbuf, "Job %d stopped by signal", pid);
        psignal(WSTOPSIG(status), sbuf);
/*
        printf("%d stop by signal\n", pid);
*/
        updatejob(jobs, pid, ST);
    }
    else {
    if (WIFSIGNALED(status)){
        //deletejob(jobs, pid);
        sprintf(sbuf, "Job %d is terminated by signal", pid);
        psignal(WTERMSIG(status), sbuf);
    }
        deletejob(jobs, pid);
    }
}

int buildin_command(char **argv)
{
    pid_t pid;
    char *cmd = argv[0];
    //char cmd[MAXLINE]; 

    //strcpy(cmd, argv[0]);

    if (!strcmp(cmd, "jobs")) {
        listjobs(jobs);
        return 1;
    }

    if (!strcmp(cmd, "bg") || !strcmp(cmd, "fg")) 
    {
        if (argv[1] == NULL) {
            printf("%s command needs PID argument\n", cmd);
            return 1;
        }
        else 
        { 
            pid = atoi(argv[1]);
            if (getjob(jobs, pid) != NULL) {
                if (!strcmp(cmd, "bg")) {
                    Kill(pid, SIGCONT);
                    updatejob(jobs, pid, BG);
                }
                if (!strcmp(cmd, "fg")) {
                    Kill(pid, SIGCONT);
                    updatejob(jobs, pid, FG);
                    waitfg(pid);
                }
            }
            else
                printf("Job %d not found\n", pid);
            return 1;
        }
    }
    if (!strcmp(argv[0], "&"))
        return 1;

    return 0;
}

void eval(char *cmdline)
{
    pid_t pid;

    int bg;
    char *argv[MAXARGS];

    bg = parseline(cmdline, argv);

    if (argv[0] == NULL)
        return ;
    if (!strcmp(argv[0], "quit"))
        exit(0);

    if (!buildin_command(argv))
    {
        if ((pid = Fork()) == 0) {        
            if (bg) {
                Signal(SIGINT, SIG_IGN);
                Signal(SIGTSTP, SIG_IGN);
            }

            if (execve(argv[0], argv, environ)< 0) {
                
                printf("%s: Command not found. \n", argv[0]);   
                fflush(stdout);
                exit(0);
            }
        }
    

    addjob(jobs, pid, (bg == 1 ? BG : FG), cmdline);

    if (!bg)
        waitfg(pid);
    else
        printf("%d %s", pid, cmdline);
    }
    return ;
}

