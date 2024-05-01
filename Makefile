CC = gcc
CFLAGS = -o
main: main.c
	$(CC) main.c $(CFLAGS) output
clean:
	rm -f a.out output 
