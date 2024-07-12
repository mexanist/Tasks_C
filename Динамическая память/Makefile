obj = ex6_1.o directory.o

directory: $(obj)
	gcc $(obj) -o directory
directory.o: directory.c
	gcc -c directory.c 
ex6_1.o: ex6_1.c
	gcc -c ex6_1.c
.PHONY: clean
clean: 
	rm $(obj) directory
