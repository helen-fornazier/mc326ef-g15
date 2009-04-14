CFLAGS = -Wall -c -g
CC = gcc
OBJS = LibWord.o LibFile.o LibMsg.o LibOption.o
LIBS = LibWord.c LibFile.c LibMsg.c LibOption.c


lab03: $(LIBS) $(OBJS) lab03.o lab03.c
	$(CC) $(CFLAGS) $(LIBS)
	$(CC) $(CFLAGS) lab03.c
	$(CC) -o lab03 lab03.o $(OBJS)


clean:
	rm *.o
	rm lab03

all:
	make clean
	make lab03

valgrind:
	valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-reachable=yes ./lab03


