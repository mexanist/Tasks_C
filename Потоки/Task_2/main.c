/* Программа инкрементирует TOTAL раз с помощью пяти потоков и пяти мьютексов.
 * Компилируется и линкуется без ключа -lpthread, в Makefile ключ указан */
#include "main.h"

long a_1 = 0;
long a_2 = 0;
long a_3 = 0;
long a_4 = 0;
long a_5 = 0;

int main(){
	int i;
	int i_j;
	pthread_t thread[N];
	for(i = 0; i < N; i++){
		pthread_create(&thread[i], NULL, count, (void *) NULL);
	}
	for(i_j = 0; i_j < N; i_j++){
		pthread_join(thread[i_j], NULL);
	}
	printf("TOTAL = %ld\n", a_1 + a_2 + a_3 + a_4 + a_5);
	printf("a_1 = %ld a_2 = %ld a_3 = %ld a_4 = %ld a_5 = %ld\n", a_1, a_2, a_3, a_4, a_5);
}

