CFLAGS = -Wall -c -g
CC = gcc
TEST = teste
OBJS = LibWord.o LibFile.o lab02a.o LibMsg.o

$(TEST):LibWord.c LibFile.c teste.c LibMsg.c
	$(CC) $(CFLAGS) LibWord.c
	$(CC) $(CFLAGS) LibFile.c
	$(CC) $(CFLAGS) teste.c
	$(CC) $(CFLAGS) LibMsg.c
	$(CC) $(OBJS) -ansi -o $(TEST)

lab02a:LibWord.c LibFile.c lab02a.c LibMsg.c
	$(CC) $(CFLAGS) LibWord.c
	$(CC) $(CFLAGS) LibFile.c
	$(CC) $(CFLAGS) lab02a.c
	$(CC) $(CFLAGS) LibMsg.c
	$(CC) $(OBJS) -o lab02a

clean:
	rm *.o $(TEST)

all:
	make clean
	make $(TEST)
	
