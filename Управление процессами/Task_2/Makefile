obj = main.o
task_2: $(obj)
	gcc $(obj) -o task_2
main.o: main.c
	gcc -c main.c
.PHONY: clean
clean:
	rm main.o task_2
