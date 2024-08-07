obj = main.o count.o
task_2: $(obj)
	gcc $(obj) -o task_2 -lpthread
main.o: main.c
	gcc -c main.c -lpthread
count.o: count.c
	gcc -c count.c -lphtread
.PHONY: clean
clean:
	rm -rf main.o count.o task_2
