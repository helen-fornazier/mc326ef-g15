CFLAGS = -Wall -c -g
CC = gcc
TEST = teste
OBJS = LibWord.o LibFile.o teste.o

$(TEST):LibWord.c LibFile.c teste.c
	$(CC) $(CFLAGS) LibWord.c
	$(CC) $(CFLAGS) LibFile.c
	$(CC) $(CFLAGS) teste.c
	$(CC) $(OBJS) -o $(TEST)

clean:
	rm *.o $(TEST)

all:
	make clean
	make $(TEST)
	