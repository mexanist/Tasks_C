#include <sys/stat.h>
#include <mqueue.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

int main(){
	char buf[256];
	mqd_t wr_que, rd_que;
	ssize_t read_buf;
	struct mq_attr attr;
	char *msg = "Hi\n";
/* Т.к. функции mq_open при указании флага O_CREAT обязательны два аргумента:
 * права доступа и указатель на структуру где определены атрибуты создаваемой очереди, 
 * то определяем два поля этой структуры, по той причине что функция mq_open использует
 * два поля структуры из четырех */
	attr.mq_maxmsg = 1; /* количество сообщений в очереди */
	attr.mq_msgsize = 256; /* размер сообщения */
/* Создаем очередь для общения с клиентом на запись */
	wr_que = mq_open("/test", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IWGRP, &attr);
	if (wr_que == -1){
		perror("Server create queue for write");
	}
/* Создаем очередь для общения с клиентом на чтение */
	rd_que = mq_open("/test_1", O_CREAT | O_RDONLY, S_IRUSR | S_IWUSR | S_IWGRP, &attr);
	if (rd_que  == -1){
		perror("Server create queue for read");
	}
/* Отправка сообщение клиенту */
	if (mq_send(wr_que, msg, strlen(msg), 0) == -1){
		perror("Server send message failure");
	}
/* Закрываем очередь записи сервера с клиентом */
	if (mq_close(wr_que) == -1){
		perror("Server close queue failure");
	}
/* Читаем сообщение клиента */
	read_buf = mq_receive(rd_que, buf, 1024, NULL) == -1;
	if (read_buf == -1){
		perror("Server receive message failure");
	} 
/* Закрываем очередь записи клиента с сервером */
		if (mq_close(rd_que) == -1){
			perror("Server close read queue failure");
		}
/* Удаляем очередь записи клиента с сервером */
		if (mq_unlink("/test_1") == -1){
			perror("Server delete queue failure");
		}
/* Выводим переданное клиентом сообщение на экран */
	write(STDOUT_FILENO, buf, 3);
/* Удаляем очередь записи сервера с клиентом */
	if (mq_unlink("/test") == -1){
		perror("Unlink test error");
	}
}
