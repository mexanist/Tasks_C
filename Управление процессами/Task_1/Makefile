obj = main.o
task_1: $(obj)
	gcc $(obj) -o task_1
main.o: main.c 
	gcc -c main.c
.PHONY: clean
clean:
	rm  $(obj) task_1
