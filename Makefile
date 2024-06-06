CC = gcc
CFLAGS = -g 
SRCS = main.c filehandle.c httpresponse.c routes.c
main: main.c
	$(CC) $(SRCS)  $(CFLAGS) -o output
clean:
	rm -f a.out output
