/**
 * shell1.c --      second times
 * @author    sexp
 *            2016-09-21
 */
#include "shell.h"
#include "job.h"
#include "pack.h"
#include "parseval.h"
#include "sig_handler.h"

char prompt[] = "> ";
int verbose = 0;

int main(int argc, char **argv)
{
    char cmdline[MAXLINE];

    if (argc > 2)
        usage();
    if (argc == 2) {
        if (!strcmp(argv[1], "-v"))
            verbose = 1;
        else
            usage();
    }
    Signal(SIGINT, sigint_handler);
    Signal(SIGCHLD, sigchld_handler);
    Signal(SIGTSTP, sigtstp_handler);
    
    initjobs(jobs);

    while(1)
    {
        printf("%s", prompt);
        Fgets(cmdline, MAXLINE, stdin);
        //printf("%s\n", cmdline); //
        if (feof(stdin)) {
            exit(0);
        }
        eval(cmdline);
        
    }

    exit(0);
}
