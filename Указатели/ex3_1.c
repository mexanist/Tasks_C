//Поменять в целом положительном числе (int) значение третьего байта на введенное число с клавиатуры через указатель

#include <stdio.h>
#include <stdlib.h>

int main(){
    unsigned int input = 0;
    unsigned int replace = 0;
    char *ptr =(char*)&input;
    printf("Input number ");
    if (scanf("%u", &input) != 1){
	printf("Input isn't number");
	exit(EXIT_SUCCESS);
    }
    printf("Input number replace ");
    if (scanf("%u", &replace) != 1 || replace > 255){
	printf("Input isn't number or bigger than 255");
	exit(EXIT_SUCCESS);
    }
    *(ptr + 2) = replace;
    printf("%d ",  input);
}
