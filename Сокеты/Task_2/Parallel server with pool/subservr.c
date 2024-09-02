/* Поток принимает в качестве аргумента дескриптор соткета, 
 * далее принимает входящее соединение от клиента, переводит сообщение в верхний регистр
 * и отправляет сообщение обратно клиенту */
#define BUF_SIZE 256
#define TRUE 1
#define BUSY 1
#define FREE 0
#define NUM_TH 2
#include <stdlib.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

struct request{
	pthread_t th_srvr;
	struct sockaddr_in addr_clt;
	socklen_t size;
	int status;
	int accept_fd;
};


void *subservr(void *arg){
	char buf[BUF_SIZE];
	char buf_ntop_ip[BUF_SIZE];
	ssize_t num_rd;
	struct request *req;
	req = (struct request *) arg;
	while (TRUE) {
/* Ожидаем запроса клиента */
		while (req -> accept_fd == 0){
			continue;
		}
		printf("Thread %ld\n", pthread_self());
/* Читаем то что прислал клиент */
		num_rd = read(req -> accept_fd, buf, BUF_SIZE);
/* Вызов read не добавляет завершающий нулевой байт в конце строки. Керриск стр 115
 * без этого считываются лишние символы, но такое поведение замечено от случая к случаю,
 * в иных случаях лишнии символы не считываются */
		buf[num_rd] = '\0';
		printf("Message of client: %s", buf);
/* Обрабатываем строку */
		for (int i = 0; i < strlen(buf); i++){
			buf[i] = toupper(buf[i]);
		}
/* Отправляем обратно клиенту */
		write(req -> accept_fd, buf, strlen(buf));
/* Т.к. структура адреса клиента больше не нужна, то переводим IP адрес и номер порта
 * из сетевого порядка в порядок представления данных в архитектуре х86, 
 * затем представляем их в презентационном виде с помощью inet_ntop для IP адреса
 * и ntohs для порта и выводим на экран */
	req -> addr_clt.sin_port = ntohs(req -> addr_clt.sin_port);
	inet_ntop(AF_INET, &(req -> addr_clt.sin_addr), buf_ntop_ip, BUF_SIZE);
	printf("IP address of client: %s\nPort of client: %d\n", buf_ntop_ip, req -> addr_clt.sin_port);
	printf("\n");
		close(req -> accept_fd);
		req -> accept_fd = 0;
		req -> status = FREE;
	}
}
