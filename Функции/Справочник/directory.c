#include <stdio.h>
#include <string.h>
#include "directory.h"

void add(DIR * tmp, int * ptr_count){
    printf("Введите имя абонента: ");
    scanf("%s", (tmp[(*ptr_count)]).name);
    printf("Введите фамилию абонента: ");
    scanf("%s", (tmp + *ptr_count) -> second_name);
    printf("Введите номер телефона абонента: ");
    scanf("%s", (tmp + *ptr_count) -> tel);
    (*ptr_count)++;
}

void del(DIR * tmp, char * name, int count){
    for (int i = 0; i < count; i++){
	if (!(strcmp(name, tmp[i].name))){
            for (int j = 0; j < strlen(tmp[i].name)  ; j++){
                tmp[i].name[j] = '0';
            }
            for (int l = 0; l < strlen(tmp[i].second_name); l++){
                tmp[i].second_name[l] = '0';
            }
            for (int k = 0; k < strlen(tmp[i].tel); k++){
                tmp[i].tel[k] = '0';
            } 
        } 
    }
}

void search(DIR * tmp, char * name, int count){
    for (int i = 0; i < count; i++){
        if (!(strcmp(name, tmp[i].name))){
            printf("Имя: %s\n", tmp[i].name);
            printf("Фамилия: %s\n", tmp[i].second_name);
            printf("Номер телефона: %s\n", tmp[i].tel); 
        } 
    }
}

void print(DIR * tmp, int count){
    for (int i = 0; i < count; i++){
        printf("Имя: %s\n", tmp[i].name);
        printf("Фамилия: %s\n", tmp[i].second_name);
        printf("Номер телефона: %s\n", tmp[i].tel);
    }
}
