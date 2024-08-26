#define BUF_SIZE 256
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct sockaddr_un cl_addr; /* Структура хранящая адрес клиента */
struct sockaddr_un ser_addr;/* Структура хранящая адрес сервера */
int s_fd;                   /* Хранит дескриптор сокета */
ssize_t num_buf_send;       /* Количество отправленных байт */
ssize_t num_buf_recev;      /* Количество принятых байт */
socklen_t size;              /* Размер структуры socaddr_un */
char buf[BUF_SIZE];         /* Буфер для хранения сообщения */
