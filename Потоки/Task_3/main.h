#define N_BUYER 3
#define N_SHOP 4
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include "struct.h"
#include <errno.h>

//int i, j;

int my_random(int, int);
void *shop_buy(void *);
void *shop_load(void *);
