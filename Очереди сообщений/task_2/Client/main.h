#define NAME_USR 128
#define MAX_MSG_SEND 1024
#define QUE_NAME_USR 512
#define TRUE 1
#include <fcntl.h>
#include <limits.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <errno.h>/* для вывода */
#include <stdio.h> /* ошибок */
#include <stdlib.h>// для NULL or include <stddef.h>
#include <unistd.h> /* для sleep() fork()*/
#include <string.h>
#include <ncurses.h>
#include <signal.h>
#include <mqueue.h>
#include <sys/wait.h>
#include <pthread.h>

void sig_winch(int);
void window_ini(WINDOW **, WINDOW **, WINDOW **);
void *thread_out(void *);
void *thread_srvs(void *);
