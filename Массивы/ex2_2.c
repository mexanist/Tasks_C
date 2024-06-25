//вывести заданный массив размером N в обратном порядке

#include <stdio.h>
#define N 10

int main(){
    int array[N];
    int i = 0;
    int ptr_begin = 0;
    int ptr_end = N - 1;
    int tmp = 0;
    for (i; i < N; i++){
	array[i] = i + 1;
    }
    for (i = 0; i < N; i++){
	printf("%d ", array[i]);
    }
    printf("\n");
    while (ptr_begin < ptr_end){
	tmp = array[ptr_begin];
	array[ptr_begin] = array[ptr_end];
	array[ptr_end] = tmp;
	ptr_begin++;
	ptr_end--;
    }
    for (i = 0; i < N; i++){
	printf("%d ", array[i]);
    }
}
