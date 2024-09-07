obj = main.o usr_thread.o que_chat_read.o

main: $(obj)
	gcc $(obj) -o server -lpthread 
main.o: main.c
	gcc -c -g main.c -lpthread
usr_thread.o: usr_thread.c
	gcc -c -g usr_thread.c -lpthread
que_chat_read.o: que_chat_read.c
	gcc -c -g que_chat_read.c -lpthread
.PHONY: clean
clean: 
	rm $(obj) server 
