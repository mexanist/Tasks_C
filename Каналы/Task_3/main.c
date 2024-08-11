/* Аналог bash из задания по процессам, с использованием канала 
 * для вывода данныйх одной программы в другую программу.
 * Переменная flag выбирает процесс с каналом или без канала,
 * в первом случае создается процесс без канала, во второс процесс с каналом */

#include "main.h" 

int main(){
	char str_comm[256];
	int flag, i;
	while (TRUE){
/* создаем канал  */
		pipe(pipe_fd);
		printf("bh# ");
/* считываем то что ввел пользователь */
		fgets(str_comm, 256, stdin);
		for (i = 0; i < strlen(str_comm); i++){
			if (str_comm[i] == '|'){
				flag = 1;
				break;
			} else {
				flag = 0;
			}
		} 
/* разбиваем пользовательскую строку на лексемы, которые затем 
 * в виде строки передаются в качестве аргументов функции execlp, так же
 * проверяется условие на выход из программы
 * и условие использование процесса с каналом или без него */
		comm = strtok(str_comm, " |\n");
/* условие, если нужно выйти */
		if (!strcmp(comm, "quit")){
			exit(EXIT_SUCCESS);
		}
        arg = strtok(NULL, " |\n");
		comm_p = strtok(NULL, " |\n");
		arg_p = strtok(NULL, " \n");
		switch(flag){
/* с каналом */
			case 1:
				my_bash_pipe();		
			break;
/* без канала */
			case 0:
				my_bash();
			break;
		default:
			break;
		}
	}
}
