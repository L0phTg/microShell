#ifndef _Pack_H
#define _Pack_H

#include "shell.h"

/*
 * error 
 */
void  unix_error(char *msg);  /* Unix-style error */
void  app_error(char *msg);

pid_t Fork(void);
void  Execve(const char *filename, char *const argv[], char *const envp[]);
void  Kill(pid_t pid, int signum);

handler_t *Signal(int signum, handler_t *handler);
char *Fgets(char *ptr, int n, FILE *stream);

#endif
