CFLAGS = -Wall -c -g
CC = gcc
OBJS = LibWord.o LibFile.o LibMsg.o
LIBS = LibWord.c LibFile.c LibMsg.c

ptest: $(LIBS) $(OBJS) ptest.o ptest.c
	$(CC) $(CFLAGS) $(LIBS)
	$(CC) $(CFLAGS) ptest.c
	$(CC) $(OBJS) ptest.o -o ptest

htest: $(LIBS) $(OBJS) htest.o htest.c
	$(CC) $(CFLAGS) $(LIBS)
	$(CC) $(CFLAGS) htest.c
	$(CC) $(OBJS) htest.o -o htest

lab03: $(LIBS) $(OBJS) lab03.o lab03.c
	$(CC) $(CFLAGS) $(LIBS)
	$(CC) $(CFLAGS) lab03.c
	$(CC) -o lab03 lab03.o $(OBJS)


clean:
	rm *.o
	rm ptest
	rm htest
	rm lab03

all:
	make clean
	make ptest
	make htest
	make lab03

valgrind:
	valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-reachable=yes ./lab03

valgrindh:
	valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-reachable=yes ./htest

