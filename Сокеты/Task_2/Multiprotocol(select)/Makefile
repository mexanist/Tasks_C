all: server client_udp client_tcp 
server: main_server.o   
	gcc main_server.o -o server
client_udp: main_client_udp.o
	gcc main_client_udp.o -o client_udp
client_tcp: main_client_tcp.o
	gcc main_client_tcp.o -o client_tcp
main_client_udp.o: main_client_udp.c
	gcc -c main_client_udp.c
main_server.o: main_server.c
	gcc -c main_server.c 
main_client_tcp.o: main_client_tcp.c
	gcc -c main_client_tcp.c 
.PHONY: clean
clean:
	rm  *.o server client_udp client_tcp 
