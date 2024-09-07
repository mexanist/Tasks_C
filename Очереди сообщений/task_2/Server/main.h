#define NAME_USR 128
#include <mqueue.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

void *usr_thread(void *);
void *que_chat_read(void *);
