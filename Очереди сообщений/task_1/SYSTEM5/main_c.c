/* Программ "клиент", принимает сообщение от сервера, а затем отправляет сообщение серверу */
#include "queue.h"

int main(){
	key_t id_que;       /* Ключ объекта IPC System 5, в нашем случае очереди */
	int msgid;          /* идентификатор очереди */
	char *txt = "OK\n"; /* Сообщение для сервера */
	struct mbuf msg;    /* Структура содержащая приоритет и текстовое сообщение */
	int prio;
/* Создаем ключ на очередь */
	id_que = ftok("server", 'e');
	if (id_que == -1){
		perror("id_que");
	}
/* Открываем очередь созданную сервером */
	msgid = msgget(id_que, S_IRUSR | S_IWUSR | S_IRGRP);
/* Проверка открытия очереди */
	if (msgid == -1){
/* Если клиент запущен раньше сервера, то нет очереди, значит
 * заканчиваем работу и выходим из программы */
		if (errno == 2){
			printf("%s", "Server doesn't create queue\n");
			exit(EXIT_SUCCESS);
		}
		perror("Client open queue failed");
	}
/* Прием сообщения от сервера */
	prio = 100;
	if (msgrcv(msgid, &msg, size_msg, prio, 0) == -1){
		perror("Client receive message");
	}
/* Вывод сообщения от сервера на экран */
	printf("%s", msg.mtext);
/* Формирование сообщение для сервера и отправка сообщения */
	msg.mtype = 400;
    strncpy(msg.mtext, txt, strlen(txt));
	if (msgsnd(msgid, &msg, strlen(txt), 0) == -1){
		perror("Client send message failure"); 
	}   
}

