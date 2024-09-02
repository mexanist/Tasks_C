/* Программа сервер, создает потоковый и датаграмный сокеты привязывает их к определенному адресу
 * затем с помощью мультепликсированного ввода (select) отвечает клиенту с соответствующему соединению
 * и выводит клиентское сообщение и информацию о клиенте на экран */
#include "main.h"
int main(){
	int accept_fd;
	int max_fd; /* Максимальный дескриптор файла */
	fd_set read_clt;/* Набор для чтения */
/* Создаем потоковый сокет */
	stcp_fd = socket(AF_INET, SOCK_STREAM, 0);
/* Создаем датаграммный сокет */
	sudp_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (stcp_fd == -1 || sudp_fd == -1){
		perror("create socket failure");
		exit(EXIT_FAILURE);
	}
/* for tcp port 35000 
 * for udp port 40000 */	
/* Формируем структуру sockaddr in tcp сервера
 * Функция inet_pton возвращает адрес уже в сетевом порядке */
	inet_pton(AF_INET, "127.0.0.1", &in_addr_srv_tcp);
	addr_tcp.sin_family = AF_INET;
/* Сетевой порядок для порта */
	addr_tcp.sin_port = htons(SERV_PORT_TCP);
	addr_tcp.sin_addr.s_addr = in_addr_srv_tcp.s_addr;
/* Привязываем потоковый сокет к адресу с портом 35000 */
	if (bind(stcp_fd, (struct sockaddr *) &addr_tcp, sizeof(struct sockaddr_in)) == -1){
		perror("Server tcp bind socket failure");
		exit(EXIT_FAILURE);
	}
/* Формируем структуру socaddr in udp сервера */
	inet_pton(AF_INET, "127.0.0.1", &in_addr_srv_udp);
	addr_udp.sin_family = AF_INET;
	addr_udp.sin_port = htons(SERV_PORT_UDP);
	addr_udp.sin_addr.s_addr = in_addr_srv_udp.s_addr;
/* Привязываем датаграмный сокет к адресу с портом 40000 */
	if (bind(sudp_fd, (struct sockaddr *) &addr_udp, sizeof(struct sockaddr_in)) == -1){
		perror("Server udp bind socket failure");
		exit(EXIT_FAILURE);
	}
/* Потоковый сокет слушает в пассивном состоянии */
	if (listen(stcp_fd, SOMAXCONN) == -1){
		perror("listen server failure");
		exit(EXIT_FAILURE);
	}
/* Устанавливаем максимальное значение дескриптора */
	max_fd = stcp_fd > sudp_fd ? stcp_fd : sudp_fd;
/* Макросы - помощники */
	FD_ZERO(&read_clt);        /* Очищаем набор */
	FD_SET(stcp_fd, &read_clt);/* Устанавливаем дескриптор потокового сокета в набор */
	FD_SET(sudp_fd, &read_clt);/* Устанавливаем дескриптор датаграмного сокета в набор */
/* Установка select, установка набора для чтения, без таймера */
	if (select (max_fd + 1, &read_clt, NULL, NULL, NULL) == -1){
		perror("Select failure");
		exit(EXIT_FAILURE);
	}
/* Если готов потоковый сокет */
	if (FD_ISSET(stcp_fd, &read_clt)){
		size = sizeof(struct sockaddr_in);
		accept_fd = accept(stcp_fd, (struct sockaddr *) &addr_clt, &size);
		if (accept_fd == -1){
			perror("accept server failure");
			exit(EXIT_FAILURE);
		}
		read(accept_fd, buf, BUF_SIZE);
		printf("Message of client: %s", buf);
/* Обрабатываем строку */
		for (int i = 0; i < strlen(buf); i++){
			buf[i] = toupper(buf[i]);
		}
/* Отправляем обратно клиенту */
		num_sd = write(accept_fd, buf, strlen(buf));
		if (num_sd != strlen(buf)){
			perror("Server tcp message failure");
		}
/* Информация о клиенте */
		addr_clt.sin_port = ntohs(addr_clt.sin_port);
		inet_ntop(AF_INET, &addr_clt.sin_addr, buf_ntop_ip, BUF_SIZE);
		printf("IP address of client: %s\nPort of client: %d\n", buf_ntop_ip, addr_clt.sin_port);
		close (stcp_fd);
	}
/* Если готов датаграмный сокет */
	if (FD_ISSET(sudp_fd, &read_clt)){
		size = sizeof(struct sockaddr_in);
		num_rd = recvfrom(sudp_fd, buf, BUF_SIZE, 0, (struct sockaddr *)&addr_clt, &size);
		if (num_rd == -1){
			perror("Receive server message failure");
		}
		printf("Message of client: %s", buf);
/* Обработка строки присланной клиентом */
		for (int i = 0; i < strlen(buf); i++){
			buf[i] = toupper(buf[i]);
		}
/* Отправка сообщения клиенту. 4 и 5 аргументы описывают сокет которому будет отправленна 
 * датограмма (в нашем случае сокет клиента) */
		num_sd = sendto (sudp_fd, buf, strlen(buf), 0, (struct sockaddr *)&addr_clt, size);
		if (num_sd == -1 || num_sd != strlen(buf)){
			perror("Server send message failure");
		}
/* Информация о клиенте */
		addr_clt.sin_port = ntohs(addr_clt.sin_port);
		inet_ntop(AF_INET, &addr_clt.sin_addr, buf_ntop_ip, BUF_SIZE);
		printf("IP address of client: %s\nPort of client: %d\n", buf_ntop_ip, addr_clt.sin_port);
		close(sudp_fd);
	}	
}
