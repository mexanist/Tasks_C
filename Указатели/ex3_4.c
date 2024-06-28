//программа ищет в веденной строке с клавиатуры подстроку введенную с клавиатуры
//и возвращает указатель на начало подстроки, если подстрока не найдена, то 
//указатель записывается NULL, в качестве строк использовать статические массивы
#include <string.h>
#include <stdio.h>
#define N 100

int main(){
    char str[N];
    char substr[N];
    char *ptr_sub = NULL;
    int i = 0;
    int j = 0;
    int i_comp = 0;
    fgets(str, N, stdin);             //C99
    fgets(substr, N, stdin);
    int length_str = strlen(str) - 1;
    int length_substr = strlen(substr) - 1;
    printf("Начальный адрес строки: %p\n", str);
    if (length_str > length_substr){
	for (i; i < length_str; i++){
	    i_comp = i;
	    ptr_sub = str + i;
	    for (j = 0; j < length_substr; j++){
		if (*(str + i_comp) != *(substr + j)){
		    break;
		} else {
		    i_comp++;
		}
		if (j == (length_substr - 1)){
		    printf("Адрес первого элемента вхождения подстроки в строку %p", ptr_sub);
		    return 0;;
		}
	    }
	}
    }
    ptr_sub = NULL;
    printf("%p", ptr_sub);
}
