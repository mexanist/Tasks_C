#include <stdio.h>

void *thread_calc(void *args){
	int *i = (int *) args;
	printf("thread num %d\n", *i);
	return NULL;
}

