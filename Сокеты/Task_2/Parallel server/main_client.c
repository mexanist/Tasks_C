#include "main.h"

int main(){
	const char *msg = "Tsest of sockets\n";
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
/* Выполняем соединение. Соединяет сокет на который указывает s_fd со слушающим сокетом, чей адрес указан
 * в addr */
	if (connect(s_fd, (struct sockaddr *) &addr, sizeof(struct sockaddr_in)) == -1){
		perror("connect client failure");
		exit(EXIT_FAILURE);
	}
/* Отправляем сообщение серверу */
	write (s_fd, msg, strlen(msg) + 1);
/* Принимаем сообщение от сервера */
	read(s_fd, buf, BUF_SIZE);
	printf("Message of server: %s", buf);
/* Т.к. структура адреса сервера больше не нужна, то переводим IP адрес и номер порта
 * из сетевого порядка в порядок представления данных в архитектуре х86,    
 * затем представляем их в презентационном виде с помощью inet_ntop для IP адреса
 * и ntohs для порта и выводим на экран */
	addr.sin_port = ntohs(addr.sin_port);
	inet_ntop(AF_INET, &addr.sin_addr, buf_ntop_ip, BUF_SIZE);
	printf("IP address of server: %s\nPort of server: %d\n", buf_ntop_ip, addr.sin_port);
}
