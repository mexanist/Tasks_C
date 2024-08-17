/* Прорамма создает дочерний процесс, родительский процесс ожидает сигнала от потомка в бесконечном цикле,
 * потомок в свою очередь отправляет N сигналов SIGUSR1 родителю, каждые 2 секунды родитель выводит сообщение об этом, 
 * по завершении дочернего процесса родитель принимает сигнал SIGCHLD о завершении работы своего потомка
 * и выходит из бесконечного цикла */
#define N 3
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
	pid_t child;
	child = fork();
	if (child == -1){
		perror("fork");
	} else if (child == 0){
/* Дочерний процесс */
		int j;
		j = N;
		while (j--){
			sleep(2);
			kill(getppid(), SIGUSR1);
		}
		exit(EXIT_SUCCESS);
	} else {
/* Родительский процесс */
		int sig;
/* Определяем набор сигналов */
		sigset_t set;
		sigemptyset(&set);
/* Добавляем сигналы SIGUSR1 и SIGCHLD в набор сигналов */
		sigaddset(&set, SIGUSR1);
/* Если не добавить сигнал дочернего процесса о его завершении,
 * то родитель будет бесконечно ждать сигнала от своего потомка, 
 * да же не зная что потомок его завершился */
		sigaddset(&set, SIGCHLD);
/* Добавляем сигналы SIGUSR1 и SIGCHLD в сигнальную маску и блокируем их*/
		if (sigprocmask(SIG_BLOCK, &set, NULL) == -1){
			perror("Block signal error");
		}
		printf("Parent %d start\n", getpid());
		while(1){
/* Третий аргумент WNOHANG означает что вызов ожидания завершения дочернего процесса не должен блокироваться,
 * если дочерний процесс не завершился то waitpid возвращает 0, как только дочерний процесс
 * завершился, то waitpid возвращает pid дочернего процесса. И таким образом выходим из бесканечного цикла */
			if (waitpid(child, NULL, WNOHANG) > 0){
				break;
			}
/* Ожидаем сигнал SIGUSR1 от дочернего процесс  */
			sigwait(&set, &sig);
			printf("Child %d send signal %d\n", child, sig);
		}
		printf("Parent %d end\n", getpid());
		exit(EXIT_SUCCESS);
	}
}

