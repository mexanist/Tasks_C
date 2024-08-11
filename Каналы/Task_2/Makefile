all: server client 
server: main_s.o 
	gcc main_s.o -o server
client: main_c.o
	gcc main_c.o -o client
main_s.o: main_s.c
	gcc -c main_s.c
main_c.o: main_c.c
	gcc -c main_c.c
.PHONY: clean
clean:
	rm  *.o server client 
