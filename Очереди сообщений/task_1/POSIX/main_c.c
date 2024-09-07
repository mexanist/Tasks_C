#include <sys/stat.h>
#include <mqueue.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h> 

char buf[256];

int main(){
	mqd_t rd_que, wr_que;
	char *msg = "OK\n";
/* Открываем очередь, созданную сервером на чтение */
	rd_que = mq_open("/test", O_RDONLY);
	if (rd_que == -1){
/* Если сервер не создал очередь на запись, то выходим из программы,
 * проверка открытия очереди на запись серверу не имеет смысла, по причине не созданных очередей */
		if (errno == 2){
			printf("Server doesn't create queue\n");
			exit(EXIT_SUCCESS);
		}
		perror("Client open queue for read error");
		exit(EXIT_FAILURE);
	}
/* т.к. сообщения без приотитетов, то последний аргумент NULL */
	if (mq_receive(rd_que, buf, 1024, NULL) == -1){
		perror("Client receive message failure");
	}
/* Закрываем очередь сообщений */
	if (mq_close(rd_que) == -1){
		perror("Client close read queue failure");      
	}
/* Выводим переданное сообщение на экран */
	if (write(STDOUT_FILENO, buf, 3) == -1){
		perror("Output client failure");
	}

/* Открываем очередь для записи для передачи сообщения серверу */
	wr_que = mq_open("/test_1", O_WRONLY);
	if (wr_que == -1){
		perror("Client open queue for write failure");
	}
/* Передаем сообщение серверу */
	if (mq_send(wr_que, msg, strlen(msg), 0) == -1){
		perror("Client send message failure");
	}   
/* Закрываем очередь для передачи сообщений серверу */
	if (mq_close(wr_que) == -1){
		perror("Client close write queue failure");
	}
}

