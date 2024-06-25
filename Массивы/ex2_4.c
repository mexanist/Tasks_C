//заполнить матрицу числами от 1 до N^2 "улиткой"

#include <stdio.h>
#define N 5

int main(){
    int array[N][N];
    int row = 0;
    int column = 0;
    int cell = 0;
    int begin = 0;					//для достижения уже выведенных данных по убыванию
    while (cell != N * N){				// N = 5 * 5
							//движение по строкам и столбцам по возраствнию
         for (column; column < N - begin; column++){    //{{1,2,3,4,5}{0,0,0,0,0}{0,0,0,0,0}{0,0,0,0,0}{0,0,0,0,0}}
	    cell++;
       	    array[row][column] = cell; 
         }
         column--;					//из за того что в цикле for(), column при проверке на условие выходит за границы N - begin
         row++;  					//переход на следующую строку
	 for (row; row < N - begin; row++){		//{{1,2,3,4,5}{0,0,0,0,6}{0,0,0,0,7}{0,0,0,0,8}{0,0,0,0,9}}
	    cell++;
	    array[row][column] = cell;
	 }
	 row--;						//из за того что в цикле for(), row при проверке на условие выходит за границы N - begin
	 column--;					//переход на предыдущий стодбец
	 begin++;					
	 		    				//движение по строкам и столбцам по убыванию
	 for (column; column >= begin; column--){	//{{1,2,3,4,5}{0,0,0,0,6}{0,0,0,0,7}{0,0,0,0,8}{0,12,11,10,9}}
	    cell++;
	    array[row][column] = cell;
	 }
	 for (row; row >= begin; row--){	       //{{1,2,3,4,5}{16,0,0,0,6}{15,0,0,0,7}{14,0,0,0,8}{13,12,11,10,9}}
	    cell++;
	    array[row][column] = cell;
	 }
	 row++;					       //из за того что в цикле for() column и row при проверке на условие
	 column++;				       //выходять за границы begin
    }
    for (row = 0; row < N; row++){
	for (column = 0; column < N; column++){
	    printf ("%2d ", array[row][column]);
	}
    printf("\n");
    }
}
