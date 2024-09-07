/* Функция потока прнимает обновленный список участников и выводит на экран
 * при отмене потока закрывает дескриптор очереди который слушает сервер 
 * и отправляет pid процесса, при первой посылке pid клиент регестрируется
 * на сервере, при второй отправке pid дает понять серверу что он покидает
 * чат комнату */
#define TRUE 1
#define MAX_MSG_SEND 1024 

#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>
#include <mqueue.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>
 
extern mqd_t que_answr;
/* Функция вывода участников чата на экран */
int work_out_srvs(WINDOW *win, void *arg){
	char *str = (char *) arg;
	char *tmp;
	werase(win);
	wprintw(win, "%s", str);
	wrefresh(win);
}
/* Функция выполняющаяся при отмене потока, отсылает 
 * pid клиента и закрывает дескриптор очереди, которую слушает сервер */
void send_bye(void *arg){
	mqd_t tmp = *(mqd_t *)arg;
	char buf[1024];
	snprintf(buf, 1024, "%d%c", getpid(), '\n');
	mq_send(tmp, buf, strlen(buf) + 1, 0);
	mq_close(tmp);	
	printf("queue /listen_clnt close\n");
} 

void *thread_srvs(void* arg) {
	WINDOW *frame_out = (WINDOW *) arg;
	char buf[1024];
	char buf_win[1024];
	mqd_t srvs_wr, srvs_rd;
	ssize_t num_read;
/* Открываем слушающую очередь сервера, отправляем свой pid, 
 * который является одновременно именем, серверу */
	snprintf(buf, MAX_MSG_SEND, "%d%c", getpid(), '\n');
	srvs_wr = mq_open("/listen_clnt", O_WRONLY);
	if (srvs_wr == -1){
		perror("Client open /listn_clnt failure");
	}
	mq_send(srvs_wr, buf, strlen(buf) + 1, 0);
/* Сохраняем функцию, которая будет выполнена при отмене потока, в стек */
	pthread_cleanup_push(send_bye, (void *)&srvs_wr);
	while (TRUE) {
		num_read = mq_receive(que_answr, buf, 1024, NULL);
		use_window(frame_out, work_out_srvs, buf);
	}
	pthread_cleanup_pop(1);
}
