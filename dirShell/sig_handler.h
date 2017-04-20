#ifndef _SigHandler_H
#define _SigHandler_H


#include "shell.h"
#include "pack.h"
#include "job.h"

void sigint_handler(int sig);

void sigtstp_handler(int sig);


void sigchld_handler(int sig);

#endif
