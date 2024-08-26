#define BUF_SIZE 256
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int s_fd;
struct sockaddr_un addr;
struct sockaddr_un addr_serv;
char buf[BUF_SIZE];
