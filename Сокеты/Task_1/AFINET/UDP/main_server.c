/* Программа сервер, принимает сообщение в виде строки от клиента,
 * выводит ее на экран, так же выводит на экран адрес клиента,
 * далее переводит строку в верхний регистр и отправляет ее обратно клиенту */
#include "main.h"

int main(){
	s_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (s_fd == -1){
		perror("server socket create failure");
		exit(EXIT_FAILURE);
	} 
/* Формируем структуру sockaddr in сервера, сначала переводим адрес как строку в двоичное представление,
 * затем переводим к сетевому порядку следования байтов по сети */
	inet_pton(AF_INET, "127.0.0.1", &serv_in_addr);
	serv_in_addr.s_addr = htonl(serv_in_addr.s_addr);
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(SERV_PORT);
	ser_addr.sin_addr.s_addr = htonl(serv_in_addr.s_addr);//inet_addr("127.0.0.1");
/* Привязываем сокет сервера к определенному адресу */
	if (bind(s_fd, (struct sockaddr *)&ser_addr, sizeof(struct sockaddr_in)) == -1){
		perror("Server bind failure");
		exit(EXIT_FAILURE);
	}
/* Принимаем сообщение от клиента */
	size = sizeof(struct sockaddr_in);
/* Прием сообщения от клиента. 5 и 6 аргументы возвращают адрес удаленного сокета
 * с помощью которого была отправленна датограмма (в нашем случае от клиента) */
	num_buf_recev = recvfrom(s_fd, buf, BUF_SIZE, 0, (struct sockaddr *)&cl_addr, &size);
	if (num_buf_recev == -1){
		perror("Receive server message failure");
		close(s_fd);
	}
	printf("Message of client: %s", buf);
/* Обработка строки присланной клиентом */
	for (int i = 0; i < strlen(buf); i++){
		buf[i] = toupper(buf[i]);
	}
/* Отправка сообщения клиенту. 4 и 5 аргументы описывают сокет которому будет отправленна 
 * датограмма (в нашем случае сокет клиента) */
	num_buf_send = sendto (s_fd, buf, strlen(buf), 0, (struct sockaddr *)&cl_addr, size);
	if (num_buf_send == -1 || num_buf_send != strlen(buf)){
		perror("Server send message failure");
		close(s_fd);
	}
/* Т.к. структура адреса клиента больше не нужна, то переводим IP адрес и номер порта
 * из сетевого порядка в порядок представления данных в архитектуре х86, 
 * затем представляем их в презентационном виде и выводим на экран */
	cl_addr.sin_port = ntohs(SERV_PORT);
	cl_addr.sin_addr.s_addr = ntohl(cl_addr.sin_addr.s_addr);
	inet_ntop(AF_INET, (struct sockaddr *)&cl_addr, buf_ntop_ip, BUF_SIZE);
	printf("IP address of client: %s\nPort of client: %d\n", buf_ntop_ip, cl_addr.sin_port);
	close(s_fd);
}
