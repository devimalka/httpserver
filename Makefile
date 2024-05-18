CC = gcc
CFLAGS = -o
SRCS = main.c filehandle.c httpresponse.c
main: main.c
	$(CC) $(SRCS)  $(CFLAGS) output
clean:
	rm -f a.out output 
