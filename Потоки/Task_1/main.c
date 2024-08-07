/* Компилируется и линкуется без ключа -lpthread, в Makefile
 * ключ указан */
#include "main.h"

int main(){
	int i, i_j;
	int arr_thread[N];
	pthread_t thread[N];
	for(i = 0; i < N; i++){
		arr_thread[i] = i;
		pthread_create(&thread[i], NULL, thread_calc, (void *)&arr_thread[i]);
	}
	for(i_j = 0; i_j < N; i_j++){
		pthread_join(thread[i_j], NULL);
	}
}

