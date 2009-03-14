lab01: lab01.c liblab01.c liblab01.o lab01.o
	gcc -Wall -c -g lab01.c
	gcc -Wall -c -g liblab01.c
	gcc liblab01.o lab01.o -o lab01
clean:
	rm -f lab01.o
	rm -f liblab01.o
	rm -f lab01
all:
	make clean
	make lab01
