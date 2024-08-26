all: server client 
server: main_server.o 
	gcc main_server.o -o server
client: main_client.o
	gcc main_client.o -o client
main_server.o: main_server.c
	gcc -c main_server.c -g
main_client.o: main_client.c
	gcc -c main_client.c -g
.PHONY: clean
clean:
	rm  *.o server client 
