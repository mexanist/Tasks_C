/* Приграмма клиент, отправляет серверу свой pid, который является одновременно именем пользователя.
 * Создает две очереди в формате:
 * /answer<pid> - очередь для приема ответа от сервера
 * /chat<pid>  - очередь для приема сообщений всех пользователей
 * В потоке th_out выводятся сообщения всех пользователей в окне frame_out
 * В потоке th_srvs выводятся информация в окне frame_srvs о новых пользователях или удаленных 
 * В отправка сообщений в общий канал происходит в окне frame_in в цикле */
#include "main.h"

mqd_t que_answr;
mqd_t que_chat;

int main(){
	WINDOW *frame_in, *frame_out, *frame_srvs;
	int ch_key;
	mqd_t que_room;
	pthread_t th_out, th_srvs;
	char buf[MAX_MSG_SEND];
	char str[128];
	char name_answr[128];
	char name_chat[128];
	struct mq_attr attr;
	attr.mq_maxmsg = 10; /* Количество сообщений в очереди */
	attr.mq_msgsize = 256;/* Максимальный размер сообщения */
	snprintf(name_answr, 128, "%s%d", "/answer", getpid());
	snprintf(name_chat, 128, "%s%d", "/chat", getpid());
/* Создаем кнал откуда читать служебные сообщения от сервера */
	que_answr = mq_open(name_answr, O_CREAT | O_RDONLY, S_IRUSR | S_IWUSR | S_IWGRP, &attr);
	if (que_answr == -1){
		perror("que_answr create failure");
		exit(EXIT_FAILURE);
	}
/* Создаем канал откуда читаем сообщения других пользователей */
	que_chat = mq_open(name_chat, O_CREAT | O_RDONLY, S_IRUSR | S_IWUSR | S_IWGRP, &attr);
	if (que_answr == -1){
		perror("que_chat create failure");
		exit(EXIT_FAILURE);
	}
/* Открываем канал, созданный сервером, на запись куда будем записывать свои сообщения */
	que_room = mq_open("/que_room", O_WRONLY);
	if (que_room == -1){
		perror("Client que_room open failure");
	}
/* Инициализация окон чата */
	window_ini(&frame_in, &frame_out, &frame_srvs);
	signal(SIGWINCH, sig_winch);
/* Поток в котором отправляются и принимаются служебные сообщения */
	pthread_create(&th_srvs, NULL, thread_srvs, frame_srvs);	
/* Поток в котором выводятся сообщения от других пользователей */
	pthread_create(&th_out, NULL, thread_out, frame_out);
/* Отправка сообщений в общий чат */
	while (TRUE){
		wgetnstr(frame_in, str, MAX_MSG_SEND);
		if (!strcmp(str, "STOP")){
			break;
		}
		snprintf(buf, 256, "%d %s", getpid(), str);
		mq_send(que_room, buf, strlen(buf), 0);
		werase(frame_in);
	}
	delwin(frame_in);
	delwin(frame_out);
	delwin(frame_srvs);
	endwin();
	pthread_cancel(th_out);
	pthread_cancel(th_srvs);
	pthread_join(th_srvs, NULL);
	mq_close(que_chat);
	mq_close(que_answr);
	mq_unlink(name_answr);
	mq_unlink(name_chat);
}
