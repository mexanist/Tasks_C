//Абонентский справочник

#include <stdio.h>
#include <string.h>
#include "directory.h"

int main(){
    char name_srch[N];
    int menu = 0;
    while (menu != 5){
        puts("1.Добавить абонента");
        puts("2.Удалить абонента");
        puts("3.Поиск абонента по имени");
        puts("4.Вывод всех записей");
        puts("5.Выход");
	scanf("%d", &menu);
	switch(menu){
	    case 1 : add();
	    break;
	    case 2 : printf("Введите имя для удаления абонента: ");
		     scanf("%s", name_srch);
	             del(name_srch);
	    break;
	    case 3 : printf("Введите имя абонента для поиска: ");
		     scanf("%s", name_srch);
		     search(name_srch);
	    break;
	    case 4 : print();
	    break;
	    case 5 : exit_programm();
	}
    }
}
