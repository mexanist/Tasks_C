#include "main.h"

int main(){
	int flag = 1;
	const char *msg = "Hi\n";
	s_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (s_fd == -1){
		perror("server socket create failure");
		exit(EXIT_FAILURE);
	} 
/* Формируем структуру sockaddr in сервера
 *  Функция inet_pton возвращает адрес уже в сетевом порядке 
 * в качестве IP адреса указываем адрес для групповой рассылки*/
	inet_pton(AF_INET, "224.0.0.1", &serv_in_addr);
	ser_addr.sin_family = AF_INET;
/* Сетевой порядок для порта */
	ser_addr.sin_port = htons(SERV_PORT);
	ser_addr.sin_addr.s_addr = serv_in_addr.s_addr;
/* Отправка сообщения клиенту. 4 и 5 аргументы описывают сокет которому будет отправленна 
 * датограмма (в нашем случае сокет клиента) */
	size = sizeof(struct sockaddr_in);
	num_buf_send = sendto (s_fd, msg, strlen(msg), 0, (struct sockaddr *)&ser_addr, size);
	if (num_buf_send == -1 || num_buf_send != strlen(msg)){
		perror("Server send message failure");
		close(s_fd);
	}
	close(s_fd);
}
