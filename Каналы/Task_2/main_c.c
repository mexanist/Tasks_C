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
	char buf[PIPE_BUF];

	int client;
/* получаем дескриптор файла-канала */
	client = open("test", O_RDONLY);
	if (client == -1){
		perror("Client open pipe failure");
		exit(EXIT_FAILURE);
	}

/* читаем сообщение из канала */
	if (read(client, &buf, 3) == -1){
		perror("Client read pipe failure");
		exit(EXIT_FAILURE);
	}
/* и выводим его на экран */
	if (write(STDOUT_FILENO, &buf, 3) == -1){
		perror("Output failure");
		exit(EXIT_FAILURE);	
	}
	if (close(client) == -1){
		perror("Client close pipe failure");
		exit(EXIT_FAILURE);
	}
/* удаляем файл-канал */
	if (unlink("test") == -1){
		perror("Remove pipe failure");
		exit(EXIT_FAILURE);
	}
}
 

