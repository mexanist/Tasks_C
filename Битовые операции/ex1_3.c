//Найти количество единиц в двоичном представлении целого положительного числа


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
    
int main(){   
    int length = CHAR_BIT * sizeof(int);		//максимальная разрядность для типа int
    unsigned int input = 0;
    unsigned int mask = 1; 				//битовая маска
    int count_of_ones = 0;				//счетчик количества единиц
    printf("Input positive number: ");
    if (scanf("%u", &input) != 1 || input < 0){
	printf("Input isn't number or number is negative. Closed\n");
	exit(EXIT_SUCCESS);
    }
    printf("Total ones in number: "); 
    for (int i = 0; i < length; i++){
	if (input & mask){
	    count_of_ones++;
        }
        input = input >> 1;
    }
    printf("%d\n", count_of_ones);
}
