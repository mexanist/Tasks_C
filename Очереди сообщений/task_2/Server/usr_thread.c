/* Поток создается для каждого вновь присоединившегося пользователся, как только он присоединился
 * поток отправляет ему все сообщения, которые хранятся в массиве и по мере добавления сообщений в массив
 * отсылает эти новые сообщения */
#define QUE_NAME_USR 512
#define TRUE 1
#include <stdio.h>
#include <unistd.h>
#include <mqueue.h>
#include <pthread.h>
#include <string.h>
#include <fcntl.h>

extern int s_arr_msg;
extern char *arr_msg[10000];

/* Функция вызываемая при отмене потока */
void clos_que(void * arg){
	mqd_t tmp = *(mqd_t *)arg;
	if (mq_close(tmp) == -1){
		perror("Server: close /que_chat failure");
	}
	printf("queue /que_chat close\n");
}

void *usr_thread(void *args){
	const char *que_chat = (char *) args;
	ssize_t num_send;
	mqd_t usr_send;
	int i_arr_msg = 0;
	usr_send = mq_open(que_chat, O_WRONLY);
	if (usr_send == -1){
		perror("que_chat open failure");
	}
/* Записываем функцию в стек, она выполнится когда поток будет завершен при отмене */
	pthread_cleanup_push(clos_que, (void *)&usr_send);
/* Отправляем сообщения из массива пользователю */
	while(TRUE){
		if (i_arr_msg != s_arr_msg){
			num_send = mq_send(usr_send, arr_msg[i_arr_msg], strlen(arr_msg[i_arr_msg]), 0);
			if (num_send == -1){
				perror("Server: send from arr_msg failure");
			}
			i_arr_msg++;
		}
	}
	pthread_cleanup_pop(1);
}
