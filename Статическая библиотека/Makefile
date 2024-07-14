obj = mul.o div.o add.o sub.o
calc: main.c arich($(obj)) clean 
	gcc main.c -o calc -L. -larich
arich($(obj)): $(obj)
	ar cr libarich.a $(obj)
sub.o: sub.c
	gcc -c sub.c 
add.o: add.c
	gcc -c add.c
div.o: div.c
	gcc -c div.c
mul.o: mul.c
	gcc -c mul.c
.PHONY: clean
clean: 
	rm $(obj)
