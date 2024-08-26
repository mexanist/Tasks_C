/* Программа клиент отправляет серверу строку, затем принимает ее обратно
 * в верхнем регистре, выводит ее на экран, а так же выводит на экран
 * адрес сервера */
#include "main.h"

int main(){
	const char *SV_SOCKNAME = "/tmp/socktest_udp_server";
	const char *CL_SOCKNAME = "/tmp/socktest_udp_client";
	const char * msg = "Test of socket\n";
	s_fd = socket(AF_LOCAL, SOCK_DGRAM, 0);
	if (s_fd == -1){
		perror("Client socket create failure");
		exit(EXIT_FAILURE);
	}
/* Формируем структуру sockaddr_un клиента */
	cl_addr.sun_family = AF_LOCAL;
	strncpy(cl_addr.sun_path, CL_SOCKNAME, strlen(CL_SOCKNAME));
/* Привязываем сокет клиента к определенному адресу (файлу) */
	if (bind(s_fd, (struct sockaddr * ) &cl_addr, sizeof(struct sockaddr_un)) == -1){
		perror("Client bind failure");
		exit(EXIT_FAILURE);
	}
/* Формируем структуру sockaddr_un сервера */
	ser_addr.sun_family = AF_LOCAL;
	strncpy(ser_addr.sun_path, SV_SOCKNAME, strlen(SV_SOCKNAME));
/* Отправка сообщения серверу. 4 и 5 аргументы описывают сокет которому будет отправленна 
 * датограмма (в нашем случае сокет сервера) */
	num_buf_send = sendto (s_fd, msg, strlen(msg), 0, (struct sockaddr *)&ser_addr, sizeof(struct sockaddr_un));
	if (num_buf_send == -1 || num_buf_send != strlen(msg)){
		perror("Client send message failure");
		close(s_fd);
		unlink(CL_SOCKNAME);
	}
/* Прием сообщения от сервера. 5 и 6 аргументы возвращают адрес удаленного сокета
 * с помощью которого была отправленна датограмма (в нашем случае от сервера) */
	num_buf_recev = recvfrom(s_fd, buf, BUF_SIZE, 0, (struct sockaddr *)&ser_addr, &size);
	if (num_buf_recev == -1){
		perror("Receive client message failure");
		close(s_fd);
		unlink(CL_SOCKNAME);
	} 
	printf("Message of server %sAddress of server %s\n", buf, ser_addr.sun_path);
	close(s_fd);
	unlink(CL_SOCKNAME);
}
