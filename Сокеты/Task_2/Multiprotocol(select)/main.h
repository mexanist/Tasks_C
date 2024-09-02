#define BUF_SIZE 256
#define SERV_PORT_TCP 35000
#define SERV_PORT_UDP 40000
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
#include <sys/time.h>
#include <sys/types.h>
#include <pthread.h>

int stcp_fd;
int sudp_fd;
struct sockaddr_in addr_tcp;
struct sockaddr_in addr_udp;
struct in_addr in_addr_srv_udp;
struct in_addr in_addr_srv_tcp;
struct sockaddr_in addr_clt;
char buf[BUF_SIZE];
char buf_ntop_ip[BUF_SIZE];
socklen_t size;
ssize_t num_rd;
ssize_t num_sd;

void *tcp_srvr(void *);
void *udp_srvr(void *);
