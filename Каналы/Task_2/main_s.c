#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>

int main(){
	char *msg = "Hi!";
	int server;
	if (mkfifo("test", S_IRUSR | S_IWUSR | S_IWGRP) == -1){
		perror("Server pipe create failure");
		exit(EXIT_FAILURE);
	};
/* получаем дескриптор файла-канала */
	server = open("test", O_WRONLY);
	if (server == -1){
		perror("Server open pipe failure");
		exit(EXIT_FAILURE);
	}
/* записываем сообщение в канал */
	if (write(server, msg, strlen(msg)) == -1){
		perror("Server write failure");
		exit(EXIT_FAILURE);
	}

	if (close(server) == -1){
		perror("Server close pipe failure");
		exit(EXIT_FAILURE);
	}
}

