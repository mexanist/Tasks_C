#include "main.h"

int main(){
	const char *msg = "Test's sockets\n";
/* Создаем сокет */
	s_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (s_fd == -1){
		perror("create socket failure");
		exit(EXIT_FAILURE);
	}
/* Формируем структуру sockaddr in сервера, сначала переводим адрес как строку в двоичное представление,
 * затем переводим к сетевому порядку следования байтов по сети */
	inet_pton(AF_INET, "127.0.0.1", &serv_in_addr);
	serv_in_addr.s_addr = htonl(serv_in_addr.s_addr);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(SERV_PORT);
	addr.sin_addr.s_addr = htonl(serv_in_addr.s_addr);
/* Выполняем соединение. Соединяет сокет на который указывает s_fd со слушающим сокетом, чей адрес указан
 * в addr */
	if (connect(s_fd, (struct sockaddr *) &addr, sizeof(struct sockaddr_in)) == -1){
		perror("connect client failure");
		exit(EXIT_FAILURE);
	}
/* Отправляем сообщение серверу */
	write (s_fd, msg, strlen(msg));
/* Принимаем сообщение от сервера */
	read(s_fd, buf, BUF_SIZE);
	printf("Message of server: %s", buf);
/* Т.к. структура адреса сервера больше не нужна, то переводим IP адрес и номер порта
 * из сетевого порядка в порядок представления данных в архитектуре х86,    
 * затем представляем их в презентационном виде и выводим на экран */
	addr.sin_port = ntohs(SERV_PORT);
	addr.sin_addr.s_addr = ntohl(addr.sin_addr.s_addr);
	inet_ntop(AF_INET, (struct sockaddr *)&addr, buf_ntop_ip, BUF_SIZE);
	printf("IP address of server: %s\nPort of server: %d\n", buf_ntop_ip, addr.sin_port);
	close(s_fd);
}
