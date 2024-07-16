obj = mul.o div.o add.o sub.o
calc: main.c arich($(obj)) clean 
	gcc main.c -o calc 
arich($(obj)): $(obj)
	gcc -shared -o libarich.so $(obj)
sub.o: sub.c
	gcc -c -fPIC sub.c 
add.o: add.c
	gcc -c -fPIC add.c
div.o: div.c
	gcc -c -fPIC div.c
mul.o: mul.c
	gcc -c -fPIC mul.c
.PHONY: clean
clean: 
	rm $(obj) 
