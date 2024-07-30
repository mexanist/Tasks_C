/* функция принимает указатель на файл, считытвает позицию в файле
 * и выводит строку находящиюся в файле в обратном порядке */

#include <stdio.h>

extern FILE *fp;

void revers_out(FILE * fp){
	int i;                      /* хранит позицию в файле */
	char ch;
	i = ftell(fp);              /* позиция в конце строки */
    while(i--){
        fseek(fp, i, SEEK_SET); /* устанавливает позицию в файле */
        ch = fgetc(fp);
        putchar(ch);
    }
	printf("\n");
}
