#include <stdio.h>
#include "interface.h"
int main(){
	int menu = 0;
	int nb1 = 0;
	int nb2 = 0;
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
					 printf("Результат: %d\n", add(&nb1, &nb2));
			break;
			case 2 : printf("Введите первое число: ");
					 scanf("%d", &nb1);
					 printf("Введите второе число: ");
					 scanf("%d", &nb2);
					 printf("Результат: %d\n", sub(&nb1, &nb2));
			break;
			case 3 : printf("Введите первое число: ");
					 scanf("%d", &nb1);
					 printf("Введите второе число: ");
					 scanf("%d", &nb2);
					 printf("Результат: %d\n", mul(&nb1, &nb2));
			break;
			case 4 : printf("Введите первое число: ");
					 scanf("%d", &nb1);
					 printf("Введите второе число: ");
					 scanf("%d", &nb2);
					 printf("Результат: %d\n", div(&nb1, &nb2));
			break;
		}	
	}
}
