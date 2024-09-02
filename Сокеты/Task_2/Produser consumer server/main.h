#define BUF_SIZE 256
#define STR_WITH_ADDR 512
#define SERV_PORT 35000
#define TRUE 1
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
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

struct sockaddr_in addr_clnt; /* Структура хранящая адрес клиента */
struct sockaddr_in ser_addr;/* Структура хранящая адрес сервера */
struct in_addr serv_in_addr;/* IPv4 адрес*/
int s_fd;                   /* Хранит дескриптор сокета */
ssize_t num_buf_send;       /* Количество отправленных байт */
ssize_t num_buf_recev;      /* Количество принятых байт */
socklen_t size;             /* Размер структуры socaddr_ui */
char buf[BUF_SIZE];         /* Буфер для хранения сообщения */
char buf_ntop_ip[BUF_SIZE]; /* IP адрес в презентационном виде*/

