/* функция эмулирует работу грузчика, случайным числом выбирается индекс массива
 * магазина, этот же индекс равен индесу массива в котором расположен нужный мьютекс
 * в итоге, грузчик заходя в магазин блокирует этот магазин и добавляет количество
 * товаров указанное в переменной article, после выхода из магазина засыпает на 1 секунду */

#define TRUE 1
#define article 5000
#include "thread.h"

extern int shop[N_SHOP];
extern pthread_mutex_t mtx[N_SHOP];
extern int err_num;
extern char *err;

void *shop_load(void * arg){
	srand(time(NULL));
	struct loader *loader_tmp;
	loader_tmp = (struct loader* )arg;
	while(TRUE){
		loader_tmp -> n_shop = my_random(0, N_SHOP + 1);
		err_num = pthread_mutex_lock(&mtx[loader_tmp -> n_shop]);
		if (err_num != 0){
			printf("Mutex loader lock failed\n");
			err = strerror(err_num);
			printf("%s\n", err);
			exit(EXIT_FAILURE);
		}
		loader_tmp -> c_shop = shop[loader_tmp -> n_shop];
		shop[loader_tmp -> n_shop] = shop[loader_tmp -> n_shop] + article;
		err_num = pthread_mutex_unlock(&mtx[loader_tmp -> n_shop]);
		if (err_num != 0){
			printf("Mutex loader unlock failed\n");
			err = strerror(err_num);
			printf("%s\n", err);
			exit(EXIT_FAILURE);
		}
		sleep(1);
	printf("Я %s %ld\n  \
Я в магазине %d\n  \
В магазине товаров: %d\n  \
Загрузил в магазин: %d\n\
УСНУЛ\n", 
			loader_tmp -> name_load, 
			loader_tmp -> name, 
			loader_tmp -> n_shop, 
			loader_tmp -> c_shop, 
			article);
	}
	return NULL;
}
