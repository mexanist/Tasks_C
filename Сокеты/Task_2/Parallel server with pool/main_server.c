/* Сервер создает NUM_TH потоков, в поток передается элемент массива типа request
 * таким образом каждый поток работает с отдельным элемента массива. При поступлении запроса
 * от клиента ищется свободный элемент массива по флагу status, если он свободен, то в этот элемент массива
 * записывается сокет созданный accept(), если свободного потока не нашлось, но запрос ожидает первый
 * освободившийся поток */
#define NUM_CLNT 3
#define NUM_TH 2
#define BUSY 1
#define FREE 0
#include "main.h"

struct request{
	pthread_t th_srvr;          /* идентификатор потока */
	struct sockaddr_in addr_clt;/* храниться адрес клиента при вызове accept() */
	socklen_t size;             /* размер структуры типа sockaddr_in */
	int status;                 /* флаг "занят" или "свободен" */
	int accept_fd;              /* сокет созданный accept() */
};
struct request req[NUM_TH];

int main(){
	int s_fd, a_fd;
	int i, i_req;
/* Создаем пулл, т.е. массив потоков, заодно заполняем поля структуры request */
	for (i = 0; i < NUM_TH; i++){
		pthread_create(&(req[i].th_srvr), NULL, subservr, (void*)&req[i]);
		req[i].accept_fd = 0;
		req[i].status = FREE;
		req[i].size = sizeof(struct sockaddr_in);
	}

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
/* Подключаемся NUM_CLNT раз. При свободном потоке передаем сокет созданный accept
 * и поток уже общается с клиентом */
	for (i = 0; i < NUM_CLNT; i++){
		a_fd = accept(s_fd, (struct sockaddr *)&(req[i].addr_clt), &(req[i].size));
		i_req = 0;
/* Если все потоки заняты, то ожидаем свободный */
		while (req[i_req].status != FREE){
			i_req++;
			if (i_req == NUM_TH){
				i_req = 0;
			}
			continue;
		}
/* Поток свободен, передаем в структуру сокет и поднимаем флаг "занят" */
		req[i_req].accept_fd = a_fd;
		req[i_req].status = BUSY;
	}
/* Дожидаемся завершения потоков */
	for (i = 0; i < NUM_TH; i++){
/* Ожидаем те потоки которые доделывают свою работу и еще заняты */
		while (req[i].status != FREE){
			continue;
		}
/* Как освободились, отменяем их */
		pthread_cancel(req[i].th_srvr);
	}
	exit(EXIT_SUCCESS);
}
