#include <stdio.h>
#include <string.h>
#include "directory.h"
#include <malloc.h>
#include <errno.h>
#include <stdlib.h>
#include <assert.h>


static int size = 0;
static int i = 0;
static DIR * head = NULL;
/*при head = NULL функция realloc аналогична функции malloc(size(DIR))*/
void add(){
    size++;
    head = realloc(head, size * sizeof(DIR));
    if (head == NULL){
	    perror("Out of memory\n");
	    exit(EXIT_FAILURE);
    }
    printf("Введите имя абонента: ");
    scanf("%s", head[size - 1].name);
    printf("Введите фамилию абонента: ");
    scanf("%s", head[size - 1].last_name);
    printf("Введите номер телефона абонента: ");
    scanf("%s", head[size - 1].phone);
    printf("\n");
}
/* функция удаляет все объекты типа структура с одинаковыми именами
 * все объекты которые требуется удалить перемещаются в конец массива
 * если заданное имя совпадает с заданным именем поля структуры, то эта структура
 * перезаписывается структурой которая расположена в конце массива, при этом,
 * цикл while исключает возможность перезаписать удаляемые объекты из конца массива в то место,
 * куда указывает head в первом условии проверяeтся достижение указателя head 
 */
void del(const char * name){
    if (head == NULL){
	    printf("Справочник пуст\n");
	    return;
    }
    while (!(strcmp(name, head[size - 1].name)) && (head != (head + size))){
        size--;
    }
    if (head != (head + size)){
    	for (i = 0; i < size; i++){
	        if (!(strcmp(name, head[i].name))){
	    	    head[i] = head[size - 1];
		        size--;
	        }
        }
    }
/* при size = 0 функция realloc возвращает указатель на NULL */
	head = realloc(head, size * sizeof(DIR));
	assert((size == 0 && head == NULL) || (size != 0 && head != NULL));
}

void search(const char * name){
    if (head == NULL){
	    printf("Справочиник пуст\n");
	    return;
    }
    for (i = 0; i < size; i++){
	    if (!(strcmp(name, head[i].name))){
	         printf("Имя: %s\n", head[i].name);
	         printf("Фамилия: %s\n", head[i].last_name);
	         printf("Номер телефона: %s\n", head[i].phone);
	    } else {
	         printf("Имени нет в справочнике\n");
	    }
    }
}

void print(){
	if (head == NULL){
		printf("Справочник пуст\n");
		return;
	}
    for (i = 0; i < size; i++){
        printf("Имя: %s\n", head[i].name);
        printf("Фамилия: %s\n", head[i].last_name);
        printf("Номер телефона: %s\n", head[i].phone);
	    printf("\n");
    }
}


void exit_programm(){
    if (head != NULL){
	    free(head);
    }
}
