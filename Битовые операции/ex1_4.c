//Поменять в целом положительном числе значение третьего байта на введенное число с клавиатуры (int)


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
    
int main(){   
    int length = CHAR_BIT * sizeof(int);		//максимальная разрядность для типа int
    unsigned int input = 0;
    unsigned int input_replace = 0;
    unsigned int mask = 0xFF0000; 			//битовая маска 1111 1111 0000 0000 0000 0000 
    unsigned int byte_replace = 2 * CHAR_BIT;           //количество бит до третьего байта
    printf("Input positive number: ");
    if (scanf("%u", &input) != 1 || input < 0){
	printf("Input isn't number or number is negative. Closed\n");
	exit(EXIT_SUCCESS);
    }
    printf("Input number for replace: ");
    if (scanf("%u", &input_replace) != 1 || input_replace > UCHAR_MAX){
       	printf("Input isn't number or number is bigger than 255. Closed\n");
	exit(EXIT_SUCCESS); 
    } 
    printf("%d\n",  (~mask & input)|(input_replace << byte_replace));
}
