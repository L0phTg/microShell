#ifndef Shell_H
#define Shell_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>

#define UNDEF 0
#define FG    1
#define BG    2
#define ST    3

extern char **environ;
typedef void handler_t(int);


#define MAXARGS 128
#define MAXLINE 8192

#endif
