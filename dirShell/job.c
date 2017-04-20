/**
 * job.c --      second times
 * @author    sexp
 *            2016-09-21
 */
#include "job.h"
#include "pack.h"
#include "shell.h"

extern int verbose;

void clearjob(struct job_t *job)
{
    job->pid = 0;
    job->state = UNDEF;
    job->cmdline[0] = '\0';
}

void initjobs(struct job_t *jobs)
{
    int i;

    for (i = 0; i < MAXJOBS; i++) 
        clearjob(&jobs[i]);
}

int updatejob(struct job_t *jobs, pid_t pid, int state)
{
    int i;
    for (i = 0; i < MAXJOBS; i++) {
        if (jobs[i].pid == pid) {
            jobs[i].state = state; 
            return 1;
        }
    }

    if (verbose) {
        printf(" not found this %d \n", pid);
    }

    return 0;
}

int addjob(struct job_t *jobs, pid_t pid, int state, char *cmdline)
{
    int i;

    for (i = 0; i < MAXJOBS; i++) {
        if (jobs[i].pid == 0) {
            jobs[i].pid = pid;
            jobs[i].state = state;
            strcpy(jobs[i].cmdline, cmdline);
            return 1;
        }
    }
    if (verbose) {
        printf("The jobs is full");
    }
    return 0;
}

int deletejob(struct job_t *jobs, pid_t pid)
{
    int i;
    for (i = 0; i < MAXJOBS; i++) {
            if (jobs[i].pid == pid) {
            clearjob(&jobs[i]);
            return 1;
        }
    }
    return 0;
}

struct job_t *getjob(struct job_t *jobs, pid_t pid)
{
    int i;
    for (i = 0; i < MAXJOBS; i++) {
        if (jobs[i].pid == pid)
            return &jobs[i];
    }

    if (verbose) {
        printf("this pid %d is't in jobs\n", pid);
    }
    return NULL;
}

void listjobs(struct job_t *jobs)
{
    int i;
    
    for (i = 0; i < MAXJOBS; i++) 
    {
        if (jobs[i].pid != 0) {
            printf("%5d    ", (int)jobs[i].pid); 
            switch(jobs[i].state) {
                case FG:
                    printf("Running foreground    ");
                    break;
                case BG:
                    printf("Running background    ");
                    break;
                case ST:
                    printf("Stop                  ");
                    break;
                defalut:
                    printf("interrupt error       ");
                    break;
            }
            printf("%s ", jobs[i].cmdline);
        }
    }
}
/*
 * end job
 */
