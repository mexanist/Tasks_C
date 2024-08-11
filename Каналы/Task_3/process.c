#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
 
extern char *comm;/* имя исполняемой программы */
extern char *arg; /* аргумент исполняемой программы */

void my_bash(){
	pid_t child;
/* создание процесса */
        child = fork();
        if (child == -1){
            perror("Create proccess failure");
            exit(EXIT_FAILURE);
        }
/* дочерний процесс в котором запускается введенная пользователем программа */
        if (child == 0){
/* функция execlp ищет имя программы в системных путях
 * указанные в переменной PATH */
			if (execlp(comm, comm, arg, NULL) == -1){
				perror("Child exec_bash failure");
				exit(EXIT_FAILURE);
			}
		} else {
/* родитель ожидает завершения дочернего процесса */
			wait(NULL);
		}
}
