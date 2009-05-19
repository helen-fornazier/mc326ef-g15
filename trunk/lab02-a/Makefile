CFLAGS = -Wall -c -g
CC = gcc
PROG = lab02a
OBJS = LibWord.o LibFile.o lab02a.o LibMsg.o
LIBS = LibWord.c LibFile.c LibMsg.c

$(PROG): $(LIBS) lab02a.c
	$(CC) $(CFLAGS) $(LIBS)
	$(CC) $(CFLAGS) lab02a.c
	$(CC) $(OBJS) -o $(PROG)

clean:
	rm *.o
	rm $(PROG)

all:
	make clean
	make $(PROG)

valgrind:
	valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-reachable=yes ./lab02a listafinal.txt o1.out o2.out portugues.config
