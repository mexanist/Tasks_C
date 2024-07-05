//Абонентский справочник
//Требования: ввод пункта меню с клавиатуры, добавление производиться заполнением структуры
//            максимальное число абонентов 100, при удалении абонента структура заполняется нулями
//            поиск осуществляется по имени, выводятся все абоненты с данным именем
//            программа продолжает выполняться, пока пользователь не введет 5 в пункте меню

#include <stdio.h>
#include <string.h>
#include "directory.h"

int main(){
    char name_srch[N];
    int count = 0;
    int menu = 0;
    DIR catalog[M];
    while (menu != 5){
        puts("1.Добавить абонента");
        puts("2.Удалить абонента");
        puts("3.Поиск абонента по имени");
        puts("4.Вывод всех записей");
        puts("5.Выход");
	scanf("%d", &menu);
	switch(menu){
	    case 1 : if (count < M){
		         add(catalog, &count);
		     } else {
		         puts("Количество записей в справочнике больше 100");
		     }
	    break;
	    case 2 : printf("Введите имя для удаления абонента: ");
		     scanf("%s", name_srch);
		     del(catalog, name_srch, count);
	    break;
	    case 3 : printf("Введите имя абонента для поиска: ");
		     scanf("%s", name_srch);
		     search(catalog, name_srch, count);
	    break;
	    case  4 : print(catalog, count); 
	    break;
	}
    }
}
