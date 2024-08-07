/* функция задает случайное число в указанном диапазоне */
#include <stdio.h>
#include <stdlib.h>
int my_random(int range_min, int range_max){
	int rnd;
	return rnd = ((double)rand() / RAND_MAX) * (range_max - range_min) + range_min;
}

