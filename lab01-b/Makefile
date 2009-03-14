CC = gcc
CFLAGS = -Wall -c -g
OBJS = lab01b.o liblab01b.o
PROG = lab01b 
$(PROG): lab01b.c liblab01b.c $(OBSJ)
	$(CC) $(CFLAGS) lab01b.c
	$(CC) $(CFLAGS) liblab01b.c
	$(CC) $(OBJS) -o $(PROG)
clean:
	rm -f *.o $(PROG)
all:
	make clean
	make $(PROG)
