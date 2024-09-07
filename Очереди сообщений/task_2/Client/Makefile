obj = main.o window_ini.o resize.o thread_out.o thread_srvs.o 

main: $(obj)
	gcc $(obj) -o client -lncurses -lpthread
main.o: main.c
	gcc -c -g main.c -lpthread 
window_ini.o: window_ini.c 
	gcc -c -g window_ini.c -lncurses
thread_out.o: thread_out.c
	gcc -c -g thread_out.c -lncurses
thread_srvs.o: thread_srvs.c
	gcc -c -g thread_srvs.c -lncurses
resize.o: resize.c
	gcc -c -g resize.c
.PHONY: clean
clean: 
	rm $(obj) client 
