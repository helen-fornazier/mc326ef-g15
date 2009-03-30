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
	rm *.o $(PROG)

all:
	make clean
	make $(PROG)