/* Поток принимает в качестве аргумента дескриптор соткета, 
 * далее принимает входящее соединение от клиента, переводит сообщение в верхний регистр
 * и отправляет сообщение обратно клиенту */
#define BUF_SIZE 256
#include <stdlib.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
void *subservr(void *arg){
	char buf[BUF_SIZE];
	int c_fd = *(int *) arg;
	ssize_t num_rd;
	printf("Thread %ld\n", pthread_self());
/* Читаем то что прислал клиент */
	num_rd = read(c_fd, buf, BUF_SIZE);
//	buf[num_rd] = '\0';
	printf("Message of client: %s", buf);
/* Обрабатываем строку */
	for (int i = 0; i < strlen(buf); i++){
		buf[i] = toupper(buf[i]);
	}
/* Отправляем обратно клиенту */
	write(c_fd, buf, strlen(buf));
	printf("\n");
	close(c_fd);
}
