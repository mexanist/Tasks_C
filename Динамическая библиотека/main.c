#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include "interface.h"
int main(){
	void *handl;
	int (*ptr_add)(int *, int *);
	char *error;
	int menu = 0;
	int nb1 = 0;
	int nb2 = 0;
	handl = dlopen("./libarich.so", RTLD_LAZY);
	if (!handl){
		printf("%s", dlerror());
		exit(1);
	}
	while (menu != 5){
		puts("1.Сложение");
		puts("2.Вычитание");
		puts("3.Умножение");
		puts("4.Деление");
		puts("5.Выход");
		scanf("%d", &menu);
		switch(menu){
			case 1 : printf("Введите первое число: ");
					 scanf("%d", &nb1);
					 printf("Введите второе число: ");
					 scanf("%d", &nb2);
					 ptr_add = dlsym(handl, "add");
					 if ((error = dlerror()) != NULL){
					 	printf("%s\n", error);
						exit(1);
					 }
					 printf("Результат: %d\n", ptr_add(&nb1, &nb2));
			break;
			case 2 : printf("Введите первое число: ");
					 scanf("%d", &nb1);
					 printf("Введите второе число: ");
					 scanf("%d", &nb2);
					 ptr_add = dlsym(handl, "sub");
					 if ((error = dlerror()) != NULL){
					 	printf("%s\n", error);
						exit(1);
					 }
					 printf("Результат: %d\n", ptr_add(&nb1, &nb2));
			break;
			case 3 : printf("Введите первое число: ");
					 scanf("%d", &nb1);
					 printf("Введите второе число: ");
					 scanf("%d", &nb2);
					 ptr_add = dlsym(handl, "mul");
					 if ((error = dlerror()) != NULL){
					 	printf("%s\n", error);
						exit(1);
					 }
					 printf("Результат: %d\n", ptr_add(&nb1, &nb2));
			break;
			case 4 : printf("Введите первое число: ");
					 scanf("%d", &nb1);
					 printf("Введите второе число: ");
					 scanf("%d", &nb2);
					 ptr_add = dlsym(handl, "divv");
					 if ((error = dlerror()) != NULL){
					 	printf("%s\n", error);
						exit(1);
					 }

					 printf("Результат: %d\n", ptr_add(&nb1, &nb2));
			break;
			case 5 : if (dlclose(handl) < 0){
						 printf("%s", dlerror());
						 exit(1);
					 } else {
						 exit(0);
					 }
			break;
		}	
	}
}
