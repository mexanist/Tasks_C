#define BUF_SIZE 256
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>


int main(){
	char buf[BUF_SIZE];
	ssize_t num_read;
	int offst, s_fd;
	s_fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
	if (s_fd == -1){
		perror("Client socket create failure");
		exit(EXIT_FAILURE);
	}
	while (1){
		offst = 27;
		num_read = recvfrom(s_fd, buf, BUF_SIZE, 0, NULL, NULL);
		if (num_read == -1){
			perror("Receive client message failure");
			close(s_fd);
		} 
		buf[num_read] = '\0';
		while (buf[offst++]){
			printf("%c", buf[offst]);
		}
	}
	close(s_fd);
}
