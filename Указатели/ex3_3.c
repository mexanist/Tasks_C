//написать программу в которой нужно определить массив типа int размерностью 10. Использовать указатель для вывода
//элементов массива на консоль

#include <stdio.h>
#define N 10

int main(){
    int array[N];  		//имя массива явяляется указателем на элемент с нулевым индексом
    int i = 0;
    for (i; i < N; i++){
        *(array + i) = i + 1;   //аналогично записи *ptr = i + 1; ptr = ptr + 1; при объявлении указателя int *ptr = array;
    }
    for (i = 0; i < N; i++){
	printf("%d ", *(array + i));
    }
}

