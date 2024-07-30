/* программа создает файл с именем output.txt,
 * записывает в него строку “String from file”, 
 * затем считывает ее из файла с конца и выводит на экран */

#include "main.h"

int main(){
	fp = fopen("output.txt", "w+");
	if(fp == NULL){
		err = strerror(errno);
		printf("%s", err);
		exit(EXIT_SUCCESS);
	}
	fputs("String from file", fp);
	id = fileno(fp);
/* сбрасывает пользовательский буфер в буфер ядра ОС, 
 * затем записывает на диск и вызывается функция по выводу строки */
	fflush(fp);
	if(fsync(id) == -1){
		err = strerror(errno);
		printf("%s", err);
		exit(EXIT_SUCCESS);
	}
	revers_out(fp);
	fclose(fp);
	exit(EXIT_SUCCESS);
}
