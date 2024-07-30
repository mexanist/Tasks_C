obj = main.o window_ini.o path_build.o free_mem.o window_out.o resize.o

main: $(obj)
	gcc $(obj) -o main -lncurses 
main.o: main.c
	gcc -c -g main.c 
window_ini.o: window_ini.c
	gcc -c -g window_ini.c
path_build.o: path_build.c
	gcc -c -g path_build.c
free_mem.o: free_mem.c
	gcc -c -g free_mem.c
window_out.o: window_out.c
	gcc -c -g window_out.c
resize.o: resize.c
	gcc -c -g resize.c
.PHONY: clean
clean: 
	rm $(obj) main
