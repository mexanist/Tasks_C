/* Программа клиент отправляет серверу строку, затем принимает ее обратно
 * в верхнем регистре, выводит ее на экран, а так же выводит на экран
 * адрес сервера */
#include "main.h"

int main(){
	const char * msg = "Test of socket\n";
	s_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (s_fd == -1){
		perror("Client socket create failure");
		exit(EXIT_FAILURE);
	}
/* Формируем структуру sockaddr_in сервера */
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(SERV_PORT);
	ser_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
/* Отправка сообщения серверу. 4 и 5 аргументы описывают сокет которому будет отправленна 
 * датограмма (в нашем случае сокет сервера) */
	num_buf_send = sendto (s_fd, msg, strlen(msg), 0, (struct sockaddr *)&ser_addr, sizeof(struct sockaddr_in));
	if (num_buf_send == -1 || num_buf_send != strlen(msg)){
		perror("Client send message failure");
		close(s_fd);
	}
/* Прием сообщения от сервера. 5 и 6 аргументы возвращают адрес удаленного сокета
 * с помощью которого была отправленна датограмма (в нашем случае от сервера) */
	num_buf_recev = recvfrom(s_fd, buf, BUF_SIZE, 0, (struct sockaddr *)&ser_addr, &size);
	if (num_buf_recev == -1){
		perror("Receive client message failure");
		close(s_fd);
	} 
	printf("Message of server %s", buf);
/* Т.к. структура адреса сервера больше не нужна, то переводим IP адрес и номер порта
 * из сетевого порядка в порядок представления данных в архитектуре х86, 
 * затем представляем их в презентационном виде и выводим на экран */
	ser_addr.sin_port = ntohs(SERV_PORT);
	ser_addr.sin_addr.s_addr = ntohl(ser_addr.sin_addr.s_addr);
	inet_ntop(AF_INET, (struct sockaddr *)&ser_addr, buf_ntop_ip, BUF_SIZE);
	printf("IP address of server: %s\nPort of server: %d\n", buf_ntop_ip, ser_addr.sin_port);
	close(s_fd);
}
