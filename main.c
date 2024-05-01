#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>

#define PORT "8080"


int count_file_bytes(char *filename)
{
	FILE *fp;
	int c,count = 0;
	fp = fopen(filename,"r");
	if(fp != NULL){
		while((c = fgetc(fp)) != EOF)
			count++;
	}
	fclose(fp);
	return count;
}





int main(int argc, char argv[])
{

	int status;
	struct addrinfo hints, *res;
	int sockfd;
	int bindstatus;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	

	status = getaddrinfo("127.0.0.1", PORT, &hints, &res);
	if (status == -1)
	{
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
	}

	sockfd = socket(res->ai_family, res->ai_socktype, 0);
	if (sockfd == -1)
	{
		fprintf(stderr, "socket error %s\n", strerror(sockfd));
	}

	bindstatus = bind(sockfd, res->ai_addr, res->ai_addrlen);
	if (bindstatus == -1)
	{
		fprintf(stderr, "bind error %s\n", strerror(bindstatus));
	}

	freeaddrinfo(res);
	// listen
	int l;
	l = listen(sockfd, 10);
	if (l != 0)
	{
		fprintf(stderr, "LISTEN ERROR %s\n", strerror(l));
	}

	while (1)
	{
		// accept
		struct sockaddr addrlength;
		int newfd;
		socklen_t theiraddr;
		newfd = accept(sockfd, &addrlength, &theiraddr);

		if (newfd == -1)
		{
			fprintf(stderr, "%saccept error %s\n", strerror(errno));
		}

		// send

		char *buffer = "hello world";	
		int len, bytes_sent;
			
		len = strlen(buffer);
		bytes_sent = send(newfd, buffer, len, 0);
		close(newfd);
	}
	close(sockfd);
	return 0;
}
