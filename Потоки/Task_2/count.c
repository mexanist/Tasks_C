/* Функция реализует принцип "разделяй и властвуй", число, определенное как TOTAL
 * разбивается на части равное количеству потоков и количеству мьютексов,
 * каждый поток в цикле инкрементирует каждую часть по одному разу TOTAL/N/N раз,
 * затем в главной части программы эти части складываются и получается результат инкрементирования
 * равный TOTAL. При использовании пяти потоков и одного мьютекса время выполнения программы примерно 14 с,
 * при использовании пяти потоков и пяти мьютексов время выполнения программы примерно 3 с.
 */

#define TOTAL 50000000
#define N 5 
#include <pthread.h>

extern long a_1;
extern long a_2;
extern long a_3;
extern long a_4;
extern long a_5;
static pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t m2 = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t m3 = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t m4 = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t m5 = PTHREAD_MUTEX_INITIALIZER;
 
void *count(void *arg){
	long i;
/* Как я думаю, пять потоков не "толпятся" в цикле ожидая освобождения одного мьютекса,
 * а выстраиваются в очередь, друг за другом, текущий поток высвободил текущий мьютекс и занял последующий мьютекс, 
 * последующий поток занял высвободившийся мьютекс занимаемый текущим потоком, и т.д. 
 * таким образом все пять потоков распределены с помощью пятью мьютексов */
	for (i = 0; i < TOTAL/N/N; i++){
		pthread_mutex_lock(&m1);
		a_1++;
		pthread_mutex_unlock(&m1);
#if 1
		pthread_mutex_lock(&m2);
		a_2++;
		pthread_mutex_unlock(&m2);
 
		pthread_mutex_lock(&m3);
		a_3++;
		pthread_mutex_unlock(&m3);

		pthread_mutex_lock(&m4);
		a_4++;
		pthread_mutex_unlock(&m4);
 
		pthread_mutex_lock(&m5);
		a_5++;
		pthread_mutex_unlock(&m5);
#endif
	}
	return NULL;
}

