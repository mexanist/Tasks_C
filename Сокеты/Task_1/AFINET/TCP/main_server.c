#include "main.h"

int main(){
	int s_fd, c_fd;
/* Создаем сокет */
	s_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (s_fd == -1){
		perror("create socket failure");
		exit(EXIT_FAILURE);
	}
/* Формируем структуру sockaddr in сервера, сначала переводим адрес как строку в двоичное представление,
 * затем переводим к сетевому порядку следования байтов по сети */
	inet_pton(AF_INET, "127.0.0.1", &serv_in_addr);
	serv_in_addr.s_addr = htonl(serv_in_addr.s_addr);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(SERV_PORT);
	addr.sin_addr.s_addr = htonl(serv_in_addr.s_addr);//inet_addr("127.0.0.1");
/* Привязываем сокет к адресу */
	if (bind(s_fd, (struct sockaddr *) &addr, sizeof(struct sockaddr_in)) == -1){
		perror("bind socket failure");
		exit(EXIT_FAILURE);
	}
/* Делает потоковый сокет, на который указывает s_fd, пассивным. Используется для приема соединений 
 * от других активных сокетов. SOMAXCONN - константа определенная в <sys/socket.h>, содержит количество 
 * отложенных соединений */
	if (listen(s_fd, SOMAXCONN) == -1){
		perror("listen server failure");
		exit(EXIT_FAILURE);
	}
/* Принимаем входящее соединение на слушающем потоковом сокете, на который указывает s_fd
 * !!!accept создает новый сокет, который затем подключается к удаленному сокету, 
 * выполнившему вызов connect() !!! */
	size = sizeof(struct sockaddr_in);
	c_fd = accept(s_fd, (struct sockaddr *) &addr_cl, &size);
	if (c_fd == -1){
		perror("accept server failure");
		exit(EXIT_FAILURE);
	}
/* Читаем то что прислал клиент */
	read(c_fd, buf, BUF_SIZE);
	printf("Message of client: %s", buf);
/* Обрабатываем строку */
	for (int i = 0; i < strlen(buf); i++){
		buf[i] = toupper(buf[i]);
	}
/* Отправляем обратно клиенту */
	write(c_fd, buf, strlen(buf));
/* Т.к. структура адреса клиента больше не нужна, то переводим IP адрес и номер порта
 * из сетевого порядка в порядок представления данных в архитектуре х86, 
 * затем представляем их в презентационном виде и выводим на экран */
	addr_cl.sin_port = ntohs(SERV_PORT);
	addr_cl.sin_addr.s_addr = ntohl(addr_cl.sin_addr.s_addr);
	inet_ntop(AF_INET, (struct sockaddr *)&addr_cl, buf_ntop_ip, BUF_SIZE);
	printf("IP address of client: %s\nPort of client: %d\n", buf_ntop_ip, addr_cl.sin_port);
/* Закрываем сокеты */
	close(c_fd);
	close(s_fd);
}
