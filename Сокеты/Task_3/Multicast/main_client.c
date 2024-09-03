#include "main.h"

int main(){
	char buf[BUF_SIZE];
	struct ip_mreqn mreqn;
	s_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (s_fd == -1){
		perror("Client socket create failure");
		exit(EXIT_FAILURE);
	}
/* Формируем структуру sockaddr_in сервера 
 * Функция inet_pton возвращает адрес уже в сетевом порядке */
	inet_pton(AF_INET, "0.0.0.0", &serv_in_addr);
	ser_addr.sin_family = AF_INET;
/* Сетевой порядок для порта */
	ser_addr.sin_port = htons(SERV_PORT);
	ser_addr.sin_addr.s_addr = serv_in_addr.s_addr;
/* Заполнение структуры ip_mreqn, для настройки сокета */
/* Локальный адрес */
	inet_pton(AF_INET, "0.0.0.0", &(mreqn.imr_address));
/* Адресс для групповой рассылки */
	inet_pton(AF_INET, "224.0.0.1", &(mreqn.imr_multiaddr));
	mreqn.imr_ifindex = 0;
/* Подключаемся к порту сервера */
	if (bind(s_fd, (struct sockaddr *)&ser_addr, sizeof(struct sockaddr_in)) == -1){
		perror("Client bind failure");
		close(s_fd);
		exit(EXIT_FAILURE);
	}
/* Настраиваем сокет на сетевом уровне для групповой рассылки */
	if (setsockopt(s_fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreqn, sizeof(mreqn)) == -1){
		perror("Setting socket client failure");
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
