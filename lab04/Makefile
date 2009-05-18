CFLAGS = -Wall -c -g
CC = gcc
OBJS = LibWord.o LibFile.o LibMsg.o LibOption.o
LIBS = LibWord.c LibFile.c LibMsg.c LibOption.c


lab04: $(LIBS) $(OBJS) hteste.o hteste.c
	$(CC) $(CFLAGS) $(LIBS)
	$(CC) $(CFLAGS) hteste.c
	$(CC) -o hteste hteste.o $(OBJS)


clean:
	rm *.o
	rm lab04

all:
	make clean
	make lab04

valgrind:
	valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-reachable=yes ./lab04


