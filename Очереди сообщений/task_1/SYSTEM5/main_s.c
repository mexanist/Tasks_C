/* Программа "сервер", создает очередь с приоритетами, затем отправляет сообщение
 * клиенту, дожидается ответа от клиента, выводит его на экран и удаляет очередь */

/* Для отправки сообщения клиенту и приема сообщения от клиента используется одна очередь
 * фильтрация сообщений происходит по полю mtype структуры buf */
#include "queue.h"

int main(){
	key_t id_que;       /* Ключ объекта IPC System 5, в нашем случае очереди */
	int msgid;          /* идентификатор очереди */
	int prio;
	char *txt = "Hi\n"; /* Сообщение для клиента */
	struct mbuf msg;    /* Структура содержащая приоритет и текстовое сообщение */
	msg.mtype = 100;    /* Приоритет для сообщения клиенту */
	strncpy(msg.mtext, txt, strlen(txt));
	printf("%s", "Wait answer from client....\n");
/* Создаем ключ на очередь */
	id_que = ftok("server", 'e');
	if (id_que == -1){
		perror("id_que");
	}
/* Создание очереди  */
	msgid = msgget(id_que, IPC_CREAT | S_IRUSR | S_IWUSR | S_IRGRP);
	if (msgid == -1){
		perror("Server create queue failed");
	}
/* Отправляем сообщение клиенту */
	if (msgsnd(msgid, &msg, strlen(txt), 0) == -1){
		perror("Server send message failure");
	}
/* Принимаем сообщение от клиента */
	prio = 400;
	if (msgrcv(msgid, &msg, size_msg, prio, 0) == -1){
		perror("Server receive message");
	}
/* Выводим на экран сообщение от клиента */
	printf("%s", msg.mtext);
/* Удаляем очередь сообщений */
	if (msgctl(msgid, IPC_RMID, NULL) == -1){
		perror("Server remove queue failure");
	}
}
