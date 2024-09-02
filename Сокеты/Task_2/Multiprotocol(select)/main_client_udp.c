/* Программа клиент отправляет UDP серверу строку, затем принимает ее обратно
 * в верхнем регистре, выводит ее на экран, а так же выводит на экран
 * адрес сервера */
#include "main.h"

int main(){
	const char * msg = "Test of socket_UDP\n";
	sudp_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sudp_fd == -1){
		perror("Client socket create failure");
		exit(EXIT_FAILURE);
	}
/* Формируем структуру sockaddr_in сервера 
 * Функция inet_pton возвращает адрес уже в сетевом порядке */
	inet_pton(AF_INET, "127.0.0.1", &in_addr_srv_udp);
	addr_udp.sin_family = AF_INET;
/* Сетевой порядок для порта */
	addr_udp.sin_port = htons(SERV_PORT_UDP);
	addr_udp.sin_addr.s_addr = in_addr_srv_udp.s_addr;
/* Отправка сообщения серверу. 4 и 5 аргументы описывают сокет которому будет отправленна 
 * датограмма (в нашем случае сокет сервера) */
	num_sd = sendto (sudp_fd, msg, strlen(msg), 0, (struct sockaddr *)&addr_udp, sizeof(struct sockaddr_in));
	if (num_sd == -1 || num_sd != strlen(msg)){
		perror("Client send message failure");
	}
/* Прием сообщения от сервера. 5 и 6 аргументы возвращают адрес удаленного сокета
 * с помощью которого была отправленна датограмма (в нашем случае от сервера) */
	num_rd = recvfrom(sudp_fd, buf, BUF_SIZE, 0, (struct sockaddr *)&addr_udp, &size);
	if (num_rd == -1){
		perror("Receive client udp message failure");
	} 
	printf("Message of server %s", buf);
/* Т.к. структура адреса сервера больше не нужна, то переводим IP адрес и номер порта
 * из сетевого порядка в порядок представления данных в архитектуре х86, 
 * затем представляем их в презентационном виде с помощью inet_ntop для IP адреса
 * и ntohs для порта и выводим на экран */
	addr_udp.sin_port = ntohs(addr_udp.sin_port);
	inet_ntop(AF_INET, &addr_udp.sin_addr, buf_ntop_ip, BUF_SIZE);
	printf("IP address of server: %s\nPort of server: %d\n", buf_ntop_ip, addr_udp.sin_port);
	close(sudp_fd);
}
