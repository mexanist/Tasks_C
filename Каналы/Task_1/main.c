#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <limits.h>

int main(){
	int pipe_fd[2];
	int err_num;
	pid_t child;
	char buf[PIPE_BUF];
	char *msg = "Hi!";
/* создаем канал и проверяем коректно ли он создан */
	if(pipe(pipe_fd) == -1){
		printf("%s", strerror(errno));
		exit(EXIT_FAILURE);
	}
	child = fork();
	if (child == -1){
		printf("%s", strerror(errno)) ;
		exit(EXIT_FAILURE);
/* дочерний процес */
	} else if (child == 0){
/* закрываем дескриптор за запись */
		if(close(pipe_fd[1]) == -1){
			perror("Child descriptor 1");
			exit(EXIT_FAILURE);
		}
/* чтение из канала */
		err_num = read(pipe_fd[0], &buf, strlen(msg));
		if(err_num == -1){
			perror("Failure read from pipe");
			exit(EXIT_FAILURE);
		}
/* записываем данные в стандартный вывод (экран) */
		err_num = write(STDOUT_FILENO, &buf, strlen(msg));
		if(err_num == -1){
			perror("Failure write stdout");
			exit(EXIT_FAILURE);
		}
/* закрываем дескриптор на чтение, после его использования */
		if(close(pipe_fd[0]) == -1){
			perror("Child descriptor 0");
			exit(EXIT_FAILURE);
		}
/* родительский процесс */
	} else {
/* закрываем дескриптор на чтение */
		if(close(pipe_fd[0]) == -1){
			perror("Parent descriptor 0");
			exit(EXIT_FAILURE);
		}
/* пишем сообщение в канал */
		err_num = write(pipe_fd[1], msg, strlen(msg));
		if(err_num == -1){
			perror("Failure write to pipe");
			exit(EXIT_FAILURE);
		}
/* закпываем дескриптор на запись, после его использования */
		if(close(pipe_fd[1]) == -1){
			perror("Parent descriptor 1");
			exit(EXIT_FAILURE);
		}  
/* ждем дочерний процесс и завершаем работу */
		wait(NULL);
		exit(EXIT_SUCCESS);
	}
}
