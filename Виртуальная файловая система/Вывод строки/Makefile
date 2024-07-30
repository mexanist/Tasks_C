obj = main.o revers_out.o
main: $(obj)
main.o: main.c
	gcc -c main.c
revers_out.o: revers_out.c
	gcc -c revers_out.c
.PHONY: clean
clean:
	rm $(obj) main output.txt
