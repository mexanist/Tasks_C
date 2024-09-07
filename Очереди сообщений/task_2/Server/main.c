/* Программа сервер, создает очереди:
 * /listen_clnt -для приема служебных сообщений от клиента
 * /chat_room - для приема сообщений всех пользователей 
 * Логика работа сервера:
 * Сервер принимает сообщение от клиента, которое является pid его процесса и одновременно именем.
 * Преобразует имя клиента в имена очередей в которые будут отправляться служебные сообщения и сообщения
 * от клиентов, далее открываются эти череди на запись. Создает массив клиентов, в котором храниться информация
 * о пользователе. Создает общую очередь в которую записываются все сообщения от пользователей, 
 * сервер читает эти сообщения и записывает их в массив. Отдельный поток считывает эти сообщения из массива и отправляет 
 * пользователю по его индивидуальному каналу, который создается 
 * при регистрации нового пользователя. При получение pid который находиться в массиве пользователей, 
 * пользователь с таким pid удаляется */
#include "main.h"

struct user {
	char usr_name[NAME_USR];/* Имя пользователя сообщенное клиентом */
	pthread_t usr_th;       /* Поток работающий с пользователем */
	mqd_t answr;            /* Очередь служебных сообщений для отправки */
};

char *arr_msg[10000]; /* Массив для хранения всех сообщений пользователя */
int s_arr_msg;

int main(){
	int i, flag;
	ssize_t num_read;
	ssize_t num_send;
	int size = 0;
	char buf[1024];
	char str_usrs[1024];  /* Строка в которой храняться все имена клиентов */
	char name_chat[128];  /* Имя очереди через которую клиент получает сообщения друних клиентов */
	char name_answr[128]; /* Служебная очередь сообщений для ответа клиенту */
	struct user *user = NULL;
	pthread_t que_chat_rd;
	mqd_t que_listn;      /* очередь для чтения служебных сообщений от клиента */
	struct mq_attr attr;
	attr.mq_maxmsg = 10;  /* Количество сообщений в очереди */
	attr.mq_msgsize = 256;/* Максимальный размер сообщения */
/* Создание слушающей очереди /listen_client. Сервер постоянно слушает эту очередь
 * на наличие новых клиентов или удаление старых */
	que_listn = mq_open("/listen_clnt", O_CREAT | O_RDONLY, S_IRUSR | S_IWUSR | S_IWGRP, &attr);
	if (que_listn == -1){
		perror("listn_clnt create failure");
		exit(EXIT_FAILURE);
	}
	printf("Очередь для приема служебных сообщений создана\n");
/* Создаем отдельный поток, в котором будет создана основная очередь /chat_room
 * в которую будут отправлять все свои сообщения клиенты */
	if (pthread_create(&que_chat_rd, NULL, que_chat_read, NULL) > 0){
		perror("que_chat_rd failure");
		exit(EXIT_FAILURE);
	}
/* Начинаем слушать новых клиентов */
	do {
		num_read = mq_receive(que_listn, buf, 1024, NULL);
		if (num_read != strlen(buf) + 1 || num_read == -1){
			perror("Server: /listen_client receive failure");
		}
		flag = 1;
/* Если pid клиента уже есть в массиве структур user, значит запрос пользователя пришел
 * на отключение */
		for (i = 0; i < size; i++){
/* Если клиент удаляется */
			if (!strcmp(user[i].usr_name, buf)){
				pthread_cancel(user[i].usr_th);
				printf("Отключение пользователя %s", user[i].usr_name);
				user[i] = user[size - 1];
				size--;
				user = realloc(user, size * sizeof(struct user));
				if (user == NULL && size != 0){
					perror("Out of memory for delete client");
				}
				flag = 0;
			} 
		}
/* Если новый клиент регестрируется */
		if (flag){
			size++;
			user = realloc(user, size * sizeof(struct user));
			if (user == NULL){
				perror("Out of memory for create client");
			}
/* Заполняем структуру user */
			strcpy(user[size - 1].usr_name, buf);	
			printf("Подключение пользователя %s", user[size-1].usr_name);
/* Формируем имена очередей /answer и /chat имена имеют формат /answer_pid /chat_pid */
			snprintf(name_answr, strlen("/answer") + strlen(buf), "%s%s", "/answer", buf);
			snprintf(name_chat, strlen("/chat") + strlen(buf), "%s%s", "/chat", buf);
			user[size - 1].answr = mq_open(name_answr, O_WRONLY);
			if (user[size - 1].answr == -1){
				perror("Server open /answr");
			}
/* Создаем поток, который будет отправлять сообщения пользователю NAME,
 * запоминаем идентификатор потока в структуре user */
			if (pthread_create(&(user[size - 1].usr_th), NULL, usr_thread, (void *) name_chat) > 0){
				printf("fail thread");
			}
		}
/* Создаем список всех активных пользователей и отправляем им всем актуальный список
 * активных пользователей, тем самым оповещая их о том что кто то отключился или кто то
 * присоединился. Список представляет собой строку всех пользователей, строка отправляется 
 * через очередь сообщений /answer */
		if (user != NULL){
			str_usrs[0] = '\0';
			for (i = 0; i < size; i++){
				strncat(str_usrs, user[i].usr_name, strlen(user[i].usr_name));
			}
			for (i = 0; i < size; i++){
				num_send = mq_send(user[i].answr, str_usrs, strlen(str_usrs) + 1, 0);
				if (num_send == -1){
					perror("Server: send /answer");
				}
			}
		}
	} while (user);
/* Т.к. поток сам создает очередь, при отмене этого потока, дожидаемся
 * когда он закроет дескриптор и удалит созданную им очередь */
	pthread_cancel(que_chat_rd);
	pthread_join(que_chat_rd, NULL);
/* Если вдруг не смогли освободить память от всех структур в слушающем цикле */
	if (user != NULL){
		free(user);
	}
/* Высвобождение памяти отведенной для хранения сообщений пользователя */
	for (i = 0; i < s_arr_msg; i++){
		free(arr_msg[i]);
	}
/* Закрытие дескриптора и удаление самой слушающей очереди /listen_client */
	if (mq_close(que_listn) != -1){
		if (mq_unlink("/listen_clnt") == -1){
			perror("Server /listen_client delete failure");
		}
		printf("Server: /listen_client close and delete\n");
	} else {
		perror("Server close /listen_client");
	}
}
