/* Сервер создает NUM_CLNT потоков, пережает им в качестве аргумента
 * дескриптор сокета, и слушает запросы на соединения от клиентов */
#define NUM_CLNT 3
#include "main.h"

int main(){
	int s_fd;
	int c_fd[NUM_CLNT];
/* Количество клиентов */
	pthread_t sub[NUM_CLNT]; 
	int i;
/* Создаем сокет */
	s_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (s_fd == -1){
		perror("create socket failure");
		exit(EXIT_FAILURE);
	}
/* Формируем структуру sockaddr in сервера
 * Функция inet_pton возвращает адрес уже в сетевом порядке */
	inet_pton(AF_INET, "127.0.0.1", &serv_in_addr);
	addr.sin_family = AF_INET;
/* Сетевой порядок для порта */
	addr.sin_port = htons(SERV_PORT);
	addr.sin_addr.s_addr = serv_in_addr.s_addr;
/* Привязываем сокет к адресу */
	if (bind(s_fd, (struct sockaddr *) &addr, sizeof(struct sockaddr_in)) == -1){
		perror("Server bind socket failure");
		exit(EXIT_FAILURE);
	}
/* Делает потоковый сокет, на который указывает s_fd, пассивным. Используется для приема соединений 
 * от других активных сокетов. SOMAXCONN - константа определенная в <sys/socket.h>, содержит количество 
 * отложенных соединений */
	if (listen(s_fd, SOMAXCONN) == -1){
		perror("listen server failure");
		exit(EXIT_FAILURE);
	}
/* В цикле на accept() блокируемся, как появился новый клиент, создаем для него поток
 * в поток передается сокет созданный accept() и далее взаимодействие с клиентом
 * происходит в этом потоке. В основном потоке продолжаем слушать новых клиентов.
 * И так NUM_CLNT раз */
	for (i = 0; i < NUM_CLNT; i++){
		c_fd[i] = accept(s_fd, NULL, NULL);
		if (c_fd[i] == -1){
			perror("accept server failure");
			exit(EXIT_FAILURE);
		}   
		if (pthread_create(&sub[i], NULL, subservr, (void*)&c_fd[i]) != 0){
			printf("Create thread failed %d", i);
			break;
		}
	}
/* Дожидаемся завершения потоков */
	for (i = 0; i < NUM_CLNT; i++){
		pthread_join(sub[i], NULL);
	}
}
