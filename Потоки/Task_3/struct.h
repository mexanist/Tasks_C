struct buyer{
	char name_buy[7]; /* имя покупателя (символьная строка) */
	pthread_t name;   /* имя покупателя (идентификатор потока) */
	int need;         /* потребность покупателя */
	int n_shop;       /* номер магазина (индекс массива) */
	int c_shop;       /* содержимое магазина (сколько было) */
	int a_need;       /* актуальная потребность покупателя на данный момент */
};
struct loader{
	char name_load[6];
	pthread_t name; /* идентификатор потока */
	int c_shop;     /* содержимое магазина в момент посещения */
	int n_shop;     /* номер магазина (индекс массива) */
};
