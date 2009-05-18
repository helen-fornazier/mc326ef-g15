CFLAGS = -Wall -c -g
CC = gcc
OBJS = LibWord.o LibFile.o LibMsg.o LibOption.o
LIBS = LibWord.c LibFile.c LibMsg.c LibOption.c


lab04: $(LIBS) $(OBJS) lab04.o lab04.c
	$(CC) $(CFLAGS) $(LIBS)
	$(CC) $(CFLAGS) lab04.c
	$(CC) -o lab04 lab04.o $(OBJS)


clean:
	rm *.o
	rm lab04

all:
	make clean
	make lab04

valgrind:
	valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-reachable=yes ./lab04


