#include "main.h"

int main(){
	char buf[BUF_SIZE];
	s_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (s_fd == -1){
		perror("Client socket create failure");
		exit(EXIT_FAILURE);
	}
/* Формируем структуру sockaddr_in сервера 
 * Функция inet_pton возвращает адрес уже в сетевом порядке */
	inet_pton(AF_INET, "255.255.255.255", &serv_in_addr);
	ser_addr.sin_family = AF_INET;
/* Сетевой порядок для порта */
	ser_addr.sin_port = htons(SERV_PORT);
	ser_addr.sin_addr.s_addr = serv_in_addr.s_addr;
/* Подключаемся к широковещательному адресу */
	if (bind(s_fd, (struct sockaddr *)&ser_addr, sizeof(struct sockaddr_in)) == -1){
		perror("Client bind failure");
		close(s_fd);
		exit(EXIT_FAILURE);
	}
/* Прием сообщения от сервера */
	num_buf_recev = recvfrom(s_fd, buf, BUF_SIZE, 0, NULL, NULL);
	if (num_buf_recev == -1){
		perror("Receive client message failure");
		close(s_fd);
	} 
	printf("Message of server: %s", buf);
	close(s_fd);
}
