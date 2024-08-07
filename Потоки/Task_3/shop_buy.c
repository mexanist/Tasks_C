/* функция эмулирует работу покупателя, случайным числом выбирается индекс массива
 * магазина, этот же индекс равен индесу массива в котором расположен нужный мьютекс
 * в итоге, покупатель заходя в магазин блокирует этот магазин, после выхода из магазина
 * засыпает на 2 секунды */

#include "thread.h"

extern int shop[N_SHOP];
extern pthread_mutex_t mtx[N_SHOP];
extern int err_num;
extern char *err;

void *shop_buy(void *arg){
	struct buyer *buyer_tmp;
	srand(time(NULL));
	buyer_tmp = (struct buyer* )arg;
	while(buyer_tmp -> a_need != 0){
		buyer_tmp -> n_shop = my_random(0, N_SHOP + 1);
		err_num = pthread_mutex_lock(&mtx[buyer_tmp -> n_shop]);
		if (err_num != 0){
			printf("Mutex buyer lock failed %d\n", err_num);
			err = strerror(err_num);
			printf("%s\n", err);
			exit(EXIT_FAILURE);
		}
		buyer_tmp -> c_shop = shop[buyer_tmp -> n_shop];
/* Условие на то что, что бы покупатель не унес отрицательное количество товара */
		if (buyer_tmp -> a_need >= shop[buyer_tmp -> n_shop]){
			buyer_tmp -> a_need = buyer_tmp -> a_need - shop[buyer_tmp -> n_shop];
			shop[buyer_tmp -> n_shop] = 0;
		} else {
			shop[buyer_tmp -> n_shop] = shop[buyer_tmp -> n_shop] - buyer_tmp -> a_need;
			buyer_tmp -> a_need = 0;
		}
		err_num = pthread_mutex_unlock(&mtx[buyer_tmp -> n_shop]);
		if (err_num != 0){
			printf("Mutex buyer unlock failed\n");
			err = strerror(err_num);
			printf("%s\n", err);
			exit(EXIT_FAILURE);
		}
		sleep(2);
/* Выводит информацию о покупателе после посещения магазина,
 * информация о текущей потребности уже с учетом того что было в текущем магазине */
		printf("Я %s %ld\n  \
Моя потребность: %d\n  \
Я был в магазине: %d\n  \
В магазине было: %d\n  \
Моя текущая потребность: %d\n\
УСНУЛ\n", 
				buyer_tmp -> name_buy, 
				buyer_tmp -> name, 
				buyer_tmp -> need, 
				buyer_tmp -> n_shop, 
				buyer_tmp -> c_shop, 
				buyer_tmp -> a_need);
	}
    return NULL;
}
