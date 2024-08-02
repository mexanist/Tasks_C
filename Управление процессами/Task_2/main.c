/* Программа порождает процесс1 и процесс2, ждет завершения дочерних процессов. 
 * Процесс1 в свою очередь порождает процесс3 и процесс4 и ждет их завершения. 
 * Процесс2 порождает процесс5 и ждет его завершения. Все процессы выводят на экран свой pid, ppid. */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
    pid_t child_pid_1, child_pid_2, child_pid_3, child_pid_4, child_pid_5;
    int status;
/* process 1 */
    child_pid_1 = fork();
    if (child_pid_1 == 0){
		printf("Parent pid_1 %d\n", getppid());
        printf("Child pid_1 %d\n", getpid());
/* process 3 */
		child_pid_3 = fork();
        if (child_pid_3 == 0){
            printf("Parent pid_3 %d\n", getppid());
            printf("Child pid_3 %d\n", getpid());
			exit(5);
        } else {
            waitpid(child_pid_3, &status, 0);
            printf("Status %d\n", WEXITSTATUS(status));
        }
/* process 4 */
		child_pid_4 = fork();
        if (child_pid_4 == 0){
            printf("Parent pid_4 %d\n", getppid());
            printf("Child pid_4 %d\n", getpid());
            exit(5);
        } else {
            waitpid(child_pid_4, &status, 0);
            printf("Status %d\n", WEXITSTATUS(status));
        }

        exit(5);
    } else {
        waitpid(child_pid_1, &status, 0);
        printf("Status %d\n", WEXITSTATUS(status));
    }
/* process 2 */
	child_pid_2 = fork();
	if (child_pid_2 == 0){
		printf("Parent pid_2 %d\n", getppid());
        printf("Child pid_2 %d\n", getpid());
/* process 5 */
		child_pid_5 = fork();
        if (child_pid_5 == 0){
            printf("Parent pid_5 %d\n", getppid());
            printf("Child pid_5 %d\n", getpid());
            exit(5);
        } else {
            waitpid(child_pid_5, &status, 0);
            printf("Status %d\n", WEXITSTATUS(status));
        }

        exit(5);
    } else {
        waitpid(child_pid_2, &status, 0);
        printf("Status %d\n", WEXITSTATUS(status));
    }
}

