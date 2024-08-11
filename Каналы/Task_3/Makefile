OBJ = main.o process.o pipe.o
task_3: $(OBJ)
	gcc $(OBJ) -o task_3
main.o: main.c
	gcc -c main.c
process.o: process.c
	gcc -c process.c
pipe.o: pipe.c
	gcc -c pipe.c
.PHONY: clean
clean:
	rm -rf $(OBJ) task_3

