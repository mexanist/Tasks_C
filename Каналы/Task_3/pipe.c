#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
 
extern char *comm;    /* имя записывающей программы в канал */
extern char *arg;     /* аргумент записывающий программы */
extern char *comm_p;  /* имя программы читающей из канала */
extern char *arg_p;   /* аргумент читающей программы */
extern int pipe_fd[2];/* файловые дескрипторы канала */
 
/* Функция создает два канала, пораждая два процесса, 
 * один дочерний процесс выполняет введенную пользователем команду
 * и задает дескриптор файла вывода для этой программы, другой дочерний
 * процесс делает то же, за исключением того, что задает дескриптор файла 
 * откуда она будет считывать данные */
void my_bash_pipe(){
	pid_t child;
	pid_t pipe_child;
/* создаем канал  */
	if (pipe(pipe_fd) == -1){
		perror("Child_pipe failure");
		exit(EXIT_FAILURE);
	}
/* дочерний процесс который пишет в канал */
	child = fork();
	if (child == -1){
		perror("Create proccess failure");
		exit(EXIT_FAILURE);
	}
	if (child == 0){
/* закрывем дескриптор на чтение из канала */
	if (close(pipe_fd[0]) == -1){
		perror("Child_pipe_write close failure");
		exit(EXIT_FAILURE);
	}
/* !!! дублируем стандартный вывод на записывающем конце канала */
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1){
		perror("Child_pipe_write dup failure");
		exit(EXIT_FAILURE);
	}
/* !!! и тут же закрываем стандартный вывод */
	if (close(pipe_fd[1]) == -1){
		perror("Child_pipe_write_dub close");
	}
/* выполняем программу введенноую пользователем
 * результат команды попадает не на экран, а в канал */
		if (execlp(comm, comm, arg, NULL) == -1){
			perror("Child exec_bash_pipe failure");
			exit(EXIT_FAILURE);
		}
	} 
/* дочерний процесс который читает из канала */
	pipe_child = fork();
	if (pipe_child == -1){
		perror("Create proccess failure");
		exit(EXIT_FAILURE);
	}
	if (pipe_child == 0){
/* закрываем дескриптор на запись в канал */
		if (close(pipe_fd[1]) == -1){
			perror("Child pipe_read close");
			exit(EXIT_FAILURE);
		}
/* !!! дублируем стандартный ввод на читающем конце канала */
        if (dup2(pipe_fd[0], STDIN_FILENO) == -1){
            perror("Child_pipe_read dup");
            exit(EXIT_FAILURE);
        }
/* !!! и тут же закрываем стандартный ввод */
        if (close(pipe_fd[0]) == -1){
			perror("Chilr_pipe_read_close");
		}
/* выполняем программу введенную пользователем,
 * входные данные из канала будут поступать из канала */
        if (execlp(comm_p, comm_p, arg_p, NULL) == -1){
			perror("Child exec_bash_pipe failure");
			exit(EXIT_FAILURE);
		}
	}
/* закрываем остальные дескрипторы перед завершением процессов
 * и выхода из функции */
       if (close(pipe_fd[0]) || close(pipe_fd[1])){
			perror("Other descriptions");
			exit(EXIT_FAILURE);
		}
/* ждем дочерние процессы */
       wait(NULL);
       wait(NULL);
/* уходим из функции */
}
