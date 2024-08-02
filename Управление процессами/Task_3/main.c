/* Аналог командного интерпритатора bash. */
/* Программа использует функцию execlp, которая в качестве первого аргумента
 * принимает имя введенной команды и ищет ее расположение в системных путях
 * установленных с помощью переменной окружения PATH. Второй аргумент имя программы, 
 * третий - опции программы */
 
#include "main.h"

int main(){
	while (TRUE){
		printf("bh# ");
		if ((ch = getchar()) == 'q'){
            exit(EXIT_SUCCESS);
        }
		ungetc(ch, stdin);
		scanf("%s%s", comm, arg);
		child = fork();
		switch(child){
			case -1:
				err = strerror(errno);
                printf("%s", err);
                exit(EXIT_FAILURE);
			case 0:
				ret_exe = execlp(comm, comm, arg, NULL);
            	if (ret_exe == -1){
                	err = strerror(errno);
                	printf("%s", err);
                	exit(EXIT_FAILURE);
            	}
            	exit(1);
			default:
				waitpid(child, &status, 0);
	            printf("Status %d\n", WIFEXITED(status));
		}
		while(getchar() != '\n'){
			continue;
		}
	}
}
