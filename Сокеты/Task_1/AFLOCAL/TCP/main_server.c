#include "main.h"

int main(){
	const char *SOCKNAME = "/tmp/testsock";
	int s_fd, c_fd;
/* Создаем сокет */
	s_fd = socket(AF_LOCAL, SOCK_STREAM, 0);
	if (s_fd == -1){
		perror("create socket failure");
		exit(EXIT_FAILURE);
	}
	addr.sun_family = AF_LOCAL;
	strncpy(addr.sun_path, SOCKNAME, strlen(SOCKNAME));
/* Привязываем сокет к адресу */
	if (bind(s_fd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1){
		perror("bind socket failure");
		exit(EXIT_FAILURE);
	}
/* Делает потоковый сокет, на который указывает s_fd, пассивным. Используется для приема соединений 
 * от других активных сокетов. SOMAXCONN - константа определенная в <sys/socket.h>, содержит количество 
 * отложенных соединений */
	if (listen(s_fd, SOMAXCONN) == -1){
		perror("listen server failure");
		exit(EXIT_FAILURE);
	}
/* Принимаем входящее соединение на слушающем потоковом сокете, на который указывает s_fd
 * !!!accept создает новый сокет, который затем подключается к удаленному сокету, 
 * выполнившему вызов connect() !!! Т.к. клиент не привязал свой сокет к определенному адресу,
 * то 2 и 3 аргументы не нужны (выведет пустую строку в противном случае) */
	c_fd = accept(s_fd, NULL, NULL);
	if (c_fd == -1){
		perror("accept server failure");
		exit(EXIT_FAILURE);
	}
/* Читаем то что прислал клиент */
	read(c_fd, buf, BUF_SIZE);
	printf("Message of client: %s", buf);
/* Обрабатываем строку */
	for (int i = 0; i < strlen(buf); i++){
		buf[i] = toupper(buf[i]);
	}
/* Отправляем обратно клиенту */
	write(c_fd, buf, strlen(buf));
/* Закрываем сокеты, а затем удаляем сокет s_fd  */
	close(c_fd);
	close(s_fd);
	unlink(SOCKNAME);
}
