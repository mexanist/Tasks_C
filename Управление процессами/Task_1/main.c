/* Программа порождает процесс. Родительский процесс и дочерний выводят на экран свой pid, ppid. 
 * Затем родительский ждет завершения дочернего и выводит его статус завершения. */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
	pid_t child_pid;
	int status;
	child_pid = fork();
	switch (child_pid) {
		case -1:
			perror("fork");
            exit(EXIT_FAILURE);
        case 0:
			printf("Parent pid %d\n", getppid());
            printf("Child pid %d\n", getpid());
            exit(EXIT_SUCCESS);
        default:
			wait(&status);
			printf("Status %d\n", WIFEXITED(status));/* WIFEXITED, когда процесс завершился обычным образом */
            exit(EXIT_SUCCESS);
        }
}
