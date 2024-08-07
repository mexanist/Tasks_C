obj = main.o random.o shop_buy.o shop_load.o
task_3: $(obj)
	gcc $(obj) -o task_3 -lpthread
main.o: main.c
	gcc -c main.c -lpthread
random.o: random.c
	gcc -c random.c
shop_buy.o: shop_buy.c
	gcc -c shop_buy.c -lpthread
shop_load.o: shop_load.c
	gcc -c shop_load.c -lpthread
.PHINY: clean
clean:
	rm -rf main.o random.o shop_buy.o shop_load.o task_3
