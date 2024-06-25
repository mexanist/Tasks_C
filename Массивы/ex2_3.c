//заполнить верхний треугольник матрицы 0, а нижний 1

#include <stdio.h>
#define N 20

    int array[N][N];
int main(){
    int row = 0;
    int column = 0;
    for (row; row < N; row++){
	column = N - 1 - row;
	for(column; column < N; column++){
	    array[row][column] = 1;
	}
    }
    for (row = 0; row < N; row++){
	for (column = 0; column < N; column++){
	    printf("%d ", array[row][column]);
	}
	printf("\n");
    }
}

