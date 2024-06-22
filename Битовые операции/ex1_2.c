//Вывести двоичное предстваление целого отрицательного числа, используя битовые операции


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
    
int main(){   
    int length = CHAR_BIT * sizeof(int);		//максимальная разрядность для типа int
    int input = 0;
    unsigned int mask = -1; 				//битовая маска
    for (int i = 0; i < length - 1; i++){
	mask = mask << 1;				//установка старшего бита маски в 1
    }
    printf("Input negative number: ");
    if (scanf("%d", &input) != 1 || input > 0){
	printf("Input isn't number or number is positive. Closed\n");
	exit(EXIT_SUCCESS);
    }
    printf("Number of binary: "); 
    for (int i = 0; i < length; i++){
	if (i % 4 == 0){
           putchar(' ');
	}
	printf("%c", (input & mask) ? '1' : '0');	
	input = input << 1;
    }
    printf("\n");
}
