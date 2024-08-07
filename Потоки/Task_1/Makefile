obj = main.o thread_calc.o
task_1: $(obj)
	gcc $(obj) -o task_1 -lpthread
main.o: main.c
	gcc -c main.c -lpthread
thread_calc.o: thread_calc.c
	gcc -c thread_calc.c -lpthread
.PHONY: clean
clean:
	rm -rf main.o thread_calc.o task_1
	
