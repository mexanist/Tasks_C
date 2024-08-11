#define TRUE 1
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int pipe_fd[2];
char *comm;
char *arg;
char *comm_p;
char *arg_p;

void my_bash_pipe();
void my_bash();
