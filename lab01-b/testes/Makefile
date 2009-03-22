CC = gcc
CFLAGS = -Wall -c -g
OBJS = teste1.o liblab01b.o
PROG1 = teste1 
PROG2 = teste2

all:
	make clean
	make $(PROG1)
	make $(PROG2)

$(PROG1): teste1.c ../liblab01b.c $(OBSJ)
	$(CC) $(CFLAGS) teste1.c
	$(CC) $(CFLAGS) ../liblab01b.c
	$(CC) teste1.o liblab01b.o -o $(PROG1)

$(PROG2): teste2.c ../liblab01b.c $(OBSJ)
	$(CC) $(CFLAGS) teste2.c
	$(CC) $(CFLAGS) ../liblab01b.c
	$(CC) teste2.o liblab01b.o -o $(PROG2)
clean:
	rm -f *.o $(PROG1) $(PROG2)