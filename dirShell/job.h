/**
 * job.h --      second times
 * @author    sexp
 *            2016-09-21
 */
#ifndef Job_H
#define Job_H
#include "shell.h"

#define UNDEF   0
#define FG      1
#define BG      2
#define ST      3

#define MAXJOBS 32

struct job_t{
    pid_t pid;
    int state;
    char cmdline[MAXLINE];
};

struct job_t jobs[MAXJOBS];

/*
 * job work  starting:  
 */
void initjobs(struct job_t *jobs);
void clearjob(struct job_t *jobs);

int updatejob(struct job_t *jobs, pid_t pid, int state);

int addjob(struct job_t *jobs, pid_t pid, int state, char *cmdline);
int deletejob(struct job_t *jobs, pid_t pid);

struct job_t *getjob(struct job_t *jobs, pid_t pid);

void listjobs(struct job_t *jobs);
#endif
