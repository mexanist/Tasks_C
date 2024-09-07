/* Поток создает основную очередь /chat_room в которую будут отправлять все свои
 * сообщения подключенные клиенты. Так же поток сохраняет все сообщения в массив.
 * После отмены потока происходит закрытие дескриптора и удаление очереди сообщений */
#define TRUE 1
#define MAX_LEN_MSG 1024
#include <stdio.h>
#include <mqueue.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
extern char *arr_msg[10000];
extern char s_arr_msg;

/* Функция вызываемая при отмене потока */
void del_que_room(void * arg){
	mqd_t tmp = *(mqd_t *)arg;
	if (mq_close(tmp) != -1){
		printf("Server: /chat_room close\n");
		if (mq_unlink("/chat_room") != -1){
			perror("/chat_room delete failure");
		}
	} else {
		perror("Server: close chat_room failure");
	}
}

void que_chat_read(void *args){
	mqd_t que_room;
	char buf[MAX_LEN_MSG];
	struct mq_attr attr;
	attr.mq_maxmsg = 10; /* Количество сообщений в очереди */
	attr.mq_msgsize = 256;/* Максимальный размер сообщения */
	que_room = mq_open("/que_room", O_CREAT | O_RDONLY, S_IRUSR | S_IWUSR | S_IWGRP, &attr);
	if (que_room == -1){
		perror("que_room create failure");
	}
	printf("Очередь для чат комнаты создана\n");
	s_arr_msg = 0;
	ssize_t num_read;
/* Записываем функцию в стек, она выполнится когда поток будет завершен при отмене */
	pthread_cleanup_push(del_que_room, (void *)&que_room);
/* Читаем все сообщения пользователей и сохраняем их в массив */
	while(TRUE){
		num_read = mq_receive(que_room, buf, MAX_LEN_MSG, NULL);
		if (num_read == -1){
			perror("receive chat_room failure");
		}
		buf[num_read] = '\n';
		buf[num_read + 1] = '\0';
		arr_msg[s_arr_msg] = malloc(strlen(buf) + 1 );
		if (arr_msg[s_arr_msg] == NULL){
			perror("out of memory for arr_msg");
			exit(EXIT_FAILURE);
		}
		strncpy(arr_msg[s_arr_msg], buf, strlen(buf));
		s_arr_msg++;
	}
	pthread_cleanup_pop(1);
}
