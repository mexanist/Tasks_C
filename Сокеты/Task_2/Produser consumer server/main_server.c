/* Программа сервер, создает дочерний процесс, а дочерний процесс в свою очередь создает свой
 * дочерний процесс. Родительский процесс создает очередь FIFO, куда будет записывать все входящие
 * сообщения от клиента, перед этим преобразовав строку в форма IP_port_message of client.
 * Родственные процессы читают из очереди FIFO эту строку, разбивают на лексемы, заполняют 
 * структуру sockaddr_in и отправляют по извлеченному адресу сообщение клиенту.
 *
 * Очередь FIFO выбрана с целью синхранизации всех процессов, когда родительский процесс закрывает
 * свой записывающий дескриптор очереди, то родственные процессы выполняющие чтения из канала
 * получают символ конца файла после того как дочитают оставшиеся сообщения из очереди, 
 * по этому признаку они выходят из бесконечного цикла в котором происходило чтение из канала,
 * закрывают свой читающий дескриптор. Это позволяет родителю дождаться завершения дочернего процесса, 
 * а дочернему процессу дождаться завершения своего дочернего процесса  */
#define NUM_CLNT 3
#include "main.h"

int main(){
	pid_t chld_srvr;
	int i;
	if (mkfifo("fifo_recv", S_IRUSR | S_IWUSR | S_IWGRP) == -1){
		perror("mkfifo create failure");
		exit(EXIT_FAILURE);
	}
	s_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (s_fd == -1){
		perror("server socket create failure");
		exit(EXIT_FAILURE);
	} 
/* Формируем структуру sockaddr in сервера
 *  Функция inet_pton возвращает адрес уже в сетевом порядке */
	inet_pton(AF_INET, "127.0.0.1", &serv_in_addr);
	ser_addr.sin_family = AF_INET;
/* Сетевой порядок для порта */
	ser_addr.sin_port = htons(SERV_PORT);
	ser_addr.sin_addr.s_addr = serv_in_addr.s_addr;
/* Привязываем сокет сервера к определенному адресу */
	if (bind(s_fd, (struct sockaddr *)&ser_addr, sizeof(struct sockaddr_in)) == -1){
		perror("Server bind failure");
		exit(EXIT_FAILURE);
	}
	size = sizeof(struct sockaddr_in);
/* Создание дочернего процесса */
	chld_srvr = fork();
	switch(chld_srvr){
		case -1:
			perror("child_srvr");
			exit(EXIT_FAILURE);
/* Сын */
		case 0:
			int rfrq;
			char buf_qrd[512];
			char *str_send;
			int num_read;
			struct sockaddr_in send_clnt;
			pid_t grndchld_servr;
			rfrq = open("fifo_recv", O_RDONLY);
/* Дочерний процесс пораждает свой дочерний процесс (внук) */
			grndchld_servr = fork();
			switch(grndchld_servr){
				case -1:
					perror("grndchild failure");
					exit(EXIT_FAILURE);
/* Внук */
				case 0:
					while(TRUE){ 
						num_read = read(rfrq, buf_qrd, sizeof buf_qrd);
						if (num_read == '\0'){
							break;
						}
						buf_qrd[num_read] = '\0';
						send_clnt.sin_family = AF_INET;
						send_clnt.sin_addr.s_addr = atoi(strtok(buf_qrd, " "));
						send_clnt.sin_port = atoi(strtok(NULL, " "));
						str_send = strtok(NULL, "\n");
						for (i = 0; i < strlen(str_send); i++){
							str_send[i] = toupper(str_send[i]);
						}
						sendto(s_fd, str_send, strlen(str_send), 0, (struct sockaddr *)&send_clnt, size);
					}
					close(rfrq);
					exit(EXIT_SUCCESS);
/* Родитель */
				default:
					while(TRUE){
						num_read = read(rfrq, buf_qrd, sizeof buf_qrd);
						if (num_read == '\0'){
							break;
						}	
						buf_qrd[num_read] = '\0';
						send_clnt.sin_family = AF_INET;
						send_clnt.sin_addr.s_addr = atoi(strtok(buf_qrd, " "));
						send_clnt.sin_port = atoi(strtok(NULL, " "));
						str_send = strtok(NULL, "\n");
						for (i = 0; i < strlen(str_send); i++){
							str_send[i] = toupper(str_send[i]);
						}
						sendto(s_fd, str_send, strlen(str_send), 0, (struct sockaddr *)&send_clnt, size);
					}
					close(rfrq);
					wait(NULL);
					exit(EXIT_SUCCESS);
				}
/* Родитель деда */
		default:
			int wtoq;
			char str[STR_WITH_ADDR];
			wtoq = open("fifo_recv", O_WRONLY);
			for (i = 0; i < NUM_CLNT; i++){
				num_buf_recev = recvfrom(s_fd, buf, BUF_SIZE, 0, (struct sockaddr *)&addr_clnt, &size);
				if (num_buf_recev == -1){
					perror("Receive server message failure");
					close(s_fd);
				}
				printf("Message of client: %s", buf);
				snprintf(str, STR_WITH_ADDR, "%d %d %s", addr_clnt.sin_addr.s_addr, addr_clnt.sin_port, buf);
				addr_clnt.sin_port = ntohs(addr_clnt.sin_port);
				inet_ntop(AF_INET, &addr_clnt.sin_addr, buf_ntop_ip, BUF_SIZE);
				printf("IP address of client: %s\nPort of client: %d\n", buf_ntop_ip, addr_clnt.sin_port);
				printf("\n");
				if (write(wtoq, str, strlen(str)) == -1){
					perror("write FIFO failure");
				}
			}	
			close(wtoq);
			wait(NULL);
			close(s_fd);
			unlink("fifo_recv");
			exit(EXIT_SUCCESS);
		}
}
