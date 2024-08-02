obj = main.o
task_3: $(obj)
	gcc $(obj) -o task_3
main.o: main.c
	gcc -c main.c
.PHONY: clean
clean:
	rm main.o task_3
