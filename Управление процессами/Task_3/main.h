#define TRUE 1
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

pid_t child;
int status, ret_exe;
char comm[10];
char arg[10];
char ch;
char *err;  
