CC = gcc
CFLAGS = -g -o
SRCS = main.c filehandle.c httpresponse.c routes.c
main: main.c
	$(CC) $(SRCS)  $(CFLAGS) output
clean:
	rm -f a.out output
