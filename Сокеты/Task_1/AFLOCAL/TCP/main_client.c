#include "main.h"

int main(){
	const char *SOCKNAME = "/tmp/testsock";
	const char *msg = "Test's sockets\n";
/* Создаем сокет */
	s_fd = socket(AF_LOCAL, SOCK_STREAM, 0);
	if (s_fd == -1){
		perror("create socket failure");
		exit(EXIT_FAILURE);
	}
	addr.sun_family = AF_LOCAL;
	strncpy(addr.sun_path, SOCKNAME, strlen(SOCKNAME));

/* Выполняем соединение. Соединяет сокет на который указывает s_fd со слушающим сокетом, чей адрес указан
 * в addr */
	if (connect(s_fd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1){
		perror("connect client failure");
		exit(EXIT_FAILURE);
	}
/* Отправляем сообщение серверу */
	write (s_fd, msg, strlen(msg));
/* Принимаем сообщение от сервера */
	read(s_fd, buf, BUF_SIZE);
	socklen_t size = sizeof(addr_serv);
	getpeername(s_fd, (struct sockaddr *)&addr_serv, &size);
	printf("Message of server: %sAddress of server: %s\n", buf, addr_serv.sun_path);
	close(s_fd);
}
