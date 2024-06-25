#include <stdio.h>
#define N 10

int main(){
    int array[N][N];
    int row = 0;
    int column = 0;
    int cell = 0;
    for (row; row < N; row++){
        for (column = 0; column < N; column++){
	    cell++;
	    array[row][column] = cell;
        }
    }
    for (row = 0; row < N; row++){
        for (column = 0; column < N; column++){
	    printf("%3d ", array[row][column]);
        }
    printf("\n");
    }

}
