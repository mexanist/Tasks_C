/* Программа эмуляции работы магазина.
 * магазин реализован в виде массива shop[], который заполняется случайным числами
 * обозначающие количество товаров. Создаются три потока покупателей и один поток грузчика.
 * При посещении магазина он блокируется с поммощью мьетекса, мьютексы расположены 
 * в массиве mtx[], этот массив равен размерности массива магазина, таким образом,
 * номер мьютекса равен порядковому номеру магазина */

#include "main.h"

int shop[N_SHOP];
pthread_mutex_t mtx[N_SHOP];
int err_num;
char *err;

int main(){
/* srand() нужен для my_random(), для смены начального значения rand(),
 * иначе массив магазина не будет заполняться разными случайными значениями, а
 * будет одно случайное значение на весь массив */
	srand(time(NULL)); 
	struct buyer * buyer;
	struct loader * loader;
	int i, j;
/* выделение памяти под структуры и их инициализация */
	buyer = malloc(N_BUYER * sizeof(struct buyer));
	loader = malloc(sizeof(struct loader));
	if (buyer == NULL || loader == NULL){
		err = strerror(errno);
		printf("%s", err);
		exit(EXIT_FAILURE);
	}
	for(i = 0; i < N_BUYER; i++){
		(buyer + i) -> need = my_random(0, 100000);
	}
	for (i = 0; i < N_BUYER; i++){
		(buyer + i) -> a_need = (buyer + i) -> need;
	}
	strncpy(buyer -> name_buy, "BUYER_1", 7);
	strncpy((buyer + 1) -> name_buy, "BUYER_2", 7);
	strncpy((buyer + 2) -> name_buy, "BUYER_3", 7);
	strncpy(loader -> name_load, "LOADER", 6);
/* инициализация магазина */
	for (i = 0; i < N_SHOP + 1; i++){
		shop[i] = my_random(0, 10000);
	}
/* инициализация массива мьютексов */
	for (i = 0; i < N_SHOP + 1; i++){
		pthread_mutex_init(&mtx[i], NULL);
	}
/* создание потоков покупателя */
	for(i = 0; i < N_BUYER; i++){
		err_num = pthread_create(&((buyer + i) -> name), NULL, shop_buy, buyer + i);
		if(err_num != 0){
			printf("Thread buyer %d failed\n", i);
			err = strerror(errno);
			printf("%s\n", err);
			exit(EXIT_FAILURE);
		}
	}
/* создание потока грузчика */
	err_num = pthread_create(&(loader -> name), NULL, shop_load, loader);
	if(err_num != 0){
		printf("Thread loader failed\n");
		err = strerror(errno);
		printf("%s\n", err);
		exit(EXIT_FAILURE);
	}
/* ожидание всех потоков покупателей */
	for(j = 0; j < N_BUYER; j++){
		pthread_join((buyer + j) -> name, NULL);
	}
/* т.к. поток грузчик выполняется в бесконечном цикле, то
 * после ожидания всех потоков покупателей, отменяем поток грузчика
 * и соеденяимся с ним */
	pthread_cancel(loader -> name);
	pthread_join(loader -> name, NULL);
/* удаление мьютексов после завершения всех потоков */
	for (i = 0; i < N_SHOP + 1; i++){
        pthread_mutex_destroy(&mtx[i]);
   }
	free(buyer);
	free(loader);
	printf("DONE\n");
}
