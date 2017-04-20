/**
 * shell1.c --      second times
 * @author    sexp
 *            2016-09-21
 */
#ifndef _Parseval_H
#define _Parseval_H

#include "shell.h"
#include "pack.h"
#include "job.h"


#define MAXLINE 8192

char sbuf[MAXLINE];


void usage();
void waitfg(pid_t pid);
int  parseline(const char *cmdline, char **argv);
int  buildin_command(char **argv);
void eval(char *cmdline);

#endif
