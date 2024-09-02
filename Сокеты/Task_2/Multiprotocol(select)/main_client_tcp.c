/* Программа клиент отправляет TCP серверу строку, затем принимает ее обратно
 * в верхнем регистре, выводит ее на экран, а так же выводит на экран
 * адрес сервера */

#include "main.h"

int main(){
	const char *msg = "Test's sockets_TCP\n";
/* Создаем сокет */
	stcp_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (stcp_fd == -1){
		perror("create socket failure");
		exit(EXIT_FAILURE);
	}
/* Формируем структуру sockaddr in сервера
 * Функция inet_pton возвращает адрес уже в сетевом порядке */
	inet_pton(AF_INET, "127.0.0.1", &in_addr_srv_tcp);
	addr_tcp.sin_family = AF_INET;
/* Сетевой порядок для порта */	
	addr_tcp.sin_port = htons(SERV_PORT_TCP);
	addr_tcp.sin_addr.s_addr = in_addr_srv_tcp.s_addr;
/* Выполняем соединение */
	if (connect(stcp_fd, (struct sockaddr *) &addr_tcp, sizeof(struct sockaddr_in)) == -1){
		perror("connect client failure");
		exit(EXIT_FAILURE);
	}
/* Отправляем сообщение серверу */
	write (stcp_fd, msg, strlen(msg));
/* Принимаем сообщение от сервера */
	read(stcp_fd, buf, BUF_SIZE);
	printf("Message of server: %s", buf);
/* Т.к. структура адреса сервера больше не нужна, то переводим IP адрес и номер порта
 * из сетевого порядка в порядок представления данных в архитектуре х86,    
 * затем представляем их в презентационном виде с помощью inet_ntop для IP адреса
 * и ntohs для порта и выводим на экран */
	addr_tcp.sin_port = ntohs(addr_tcp.sin_port);
	inet_ntop(AF_INET, &addr_tcp.sin_addr, buf_ntop_ip, BUF_SIZE);
	printf("IP address of server: %s\nPort of server: %d\n", buf_ntop_ip, addr_tcp.sin_port);
	close(stcp_fd);
}
