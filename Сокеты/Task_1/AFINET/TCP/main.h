#define BUF_SIZE 256
#define SERV_PORT 35000
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int s_fd;
struct sockaddr_in addr;
struct sockaddr_in addr_cl;
struct in_addr serv_in_addr;
char buf[BUF_SIZE];
char buf_ntop_ip[BUF_SIZE];
socklen_t size;
