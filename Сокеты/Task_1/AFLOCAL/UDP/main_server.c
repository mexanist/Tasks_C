/* Программа сервер, принимает сообщение в виде строки от клиента,
 * выводит ее на экран, так же выводит на экран адрес клиента,
 * далее переводит строку в верхний регистр и отправляет ее обратно клиенту */
#include "main.h"

int main(){
	const char *SV_SOCKNAME = "/tmp/socktest_udp_server";
	s_fd = socket(AF_LOCAL, SOCK_DGRAM, 0);
	if (s_fd == -1){
		perror("server socket create failure");
		exit(EXIT_FAILURE);
	} 
/* Формируем структуру sockaddr_un сервера */
	ser_addr.sun_family = AF_LOCAL;
	strncpy(ser_addr.sun_path, SV_SOCKNAME, strlen(SV_SOCKNAME));
/* Привязываем сокет сервера к определенному адресу (файлу) */
	if (bind(s_fd, (struct sockaddr *)&ser_addr, sizeof(struct sockaddr_un)) == -1){
		perror("Server bind failure");
		exit(EXIT_FAILURE);
	}
/* Принимаем сообщение от клиента */
	size = sizeof(struct sockaddr_un);
 /* Прием сообщения от клиента. 5 и 6 аргументы возвращают адрес удаленного сокета
  * с помощью которого была отправленна датограмма (в нашем случае от клиента) */
	num_buf_recev = recvfrom(s_fd, buf, BUF_SIZE, 0, (struct sockaddr *)&cl_addr, &size);
	if (num_buf_recev == -1){
		perror("Receive server message failure");
		close(s_fd);
		unlink(SV_SOCKNAME);
	}
	printf("Message of client %sAddress of client %s\n", buf, cl_addr.sun_path);
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
		unlink(SV_SOCKNAME);
	}   
	close(s_fd);
	unlink(SV_SOCKNAME);
}
