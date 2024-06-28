//Абонентский справочник
//Требования: ввод пункта меню с клавиатуры, добавление производиться заполнением структуры
//            максимальное число абонентов 100, при удалении абонента структура заполняется нулями
//            поиск осуществляется по имени, выводятся все абоненты с данным именем
//            программа продолжает выполняться, пока пользователь не введет 5 в пункте меню

#include <stdio.h>
#include <string.h>
#define N 10
#define M 100

struct abonent{
    char name[N + 1];
    char second_name[N + 1];
    char tel[N + 1];
};

int main(){
    char tmp[N];
    int count = 0;
    int menu = 0;
    struct abonent catalog[M];
    while (menu != 5){
        puts("1.Добавить абонента");
        puts("2.Удалить абонента");
        puts("3.Поиск абонента по имени");
        puts("4.Вывод всех записей");
        puts("5.Выход");
	scanf("%d", &menu);
	switch(menu){
	   case 1 : if (count < M){
		      printf("Введите имя абонента: ");
		      scanf("%s", catalog[count].name);
		      printf("Введите фамилию абонента: ");
		      scanf("%s", catalog[count].second_name);
		      printf("Введите номер телефона абонента: ");
		      scanf("%s", catalog[count].tel);
		      count++;
		      } else {
		          puts("Количество записей в справочнике больше 100");
		      }
	    break;
	    case 2 : printf("Введите имя для удаления абонента: ");
		      scanf("%s", tmp);
		      for (int i = 0; i < count; i++){
		          if (!(strcmp(tmp, catalog[i].name))){
			      for (int j = 0; j < strlen(catalog[i].name)  ; j++){
			          catalog[i].name[j] = '0';
			      }
			      for (int l = 0; l < strlen(catalog[i].second_name); l++){
			          catalog[i].second_name[l] = '0';
			      }
			      for (int k = 0; k < strlen(catalog[i].tel); k++){
			          catalog[i].tel[k] = '0';
			      } 
			  } 
		      }
	    break;
	    case 3 : printf("Введите имя абонента для поиска: ");
		     scanf("%s", tmp);
		     for (int i = 0; i < count; i++){
		          if (!(strcmp(tmp, catalog[i].name))){
			      printf("Имя: %s\n", catalog[i].name);
			      printf("Фамилия: %s\n", catalog[i].second_name);
			      printf("Номер телефона: %s\n", catalog[i].tel); 
			  } 
		      }
	    break;
	    case  4 : for (int i = 0; i < count; i++){
			   printf("Имя: %s\n", catalog[i].name);
			   printf("Фамилия: %s\n", catalog[i].second_name);
			   printf("Номер телефона: %s\n", catalog[i].tel);
		       }
	    break;
	}
    }
}
