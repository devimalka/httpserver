#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT "8080"
#define BUFFSIZE 2048
#define RESSIZE 4096

#include "filehandle.h"
#include "httpresponse.h"
#include "routes.h"

int main(int argc, char *argv[]) {

  int status;
  struct addrinfo hints, *res;
  int sockfd;
  int bindstatus;

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  status = getaddrinfo(NULL, PORT, &hints, &res);
  if (status == -1) {
    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
  }

  sockfd = socket(res->ai_family, res->ai_socktype, 0);
  if (sockfd == -1) {
    fprintf(stderr, "socket error %s\n", strerror(sockfd));
  }

  int opt = 1;
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));

  bindstatus = bind(sockfd, res->ai_addr, res->ai_addrlen);
  if (bindstatus == -1) {
    fprintf(stderr, "bind error %s\n", strerror(bindstatus));
  }

  freeaddrinfo(res);

  int l;
  l = listen(sockfd, 10);
  if (l != 0) {
    fprintf(stderr, "LISTEN ERROR %s\n", strerror(l));
  }

  while (1) {
    struct sockaddr_in client_addr;
    int newfd;
    socklen_t theiraddr = sizeof client_addr;
    newfd = accept(sockfd, (struct sockaddr *)&client_addr, &theiraddr);

    if (newfd == -1) {
      fprintf(stderr, "accept error %s\n", strerror(errno));
    } else {
      char str[INET_ADDRSTRLEN];
      inet_ntop(client_addr.sin_family, (struct inaddr *)&client_addr.sin_addr,
                str, INET_ADDRSTRLEN);
      printf("Connection from %s\n", str);
    }

    char *request = requestpath(newfd);
    char *filepath = get_file_path(request);
    free(request);

    char *ext = get_file_ext(filepath, '.');
    printf("file ext is %s\n", ext);

    char *path = removenslash(filepath);
    printf("path is %s\n", path);

    char *response = NULL;

    if (strcmp(ext, ".html") == 0) {
      if (strcmp(path, "") == 0 || strcmp(filepath, "index.html") == 0) {

        response = content("index.html");
        char *http_response = (char *)malloc(RESSIZE);
        char *date = get_date_for_server();
        int content_length = strlen(response);
        int len, bytes_sent;
        int n =
            snprintf(http_response, RESSIZE,
                     "HTTP/1.1 200 OK\r\nAcess-Control-Allow-Origin: *"
                     "*\r\nConnection: Keep-Alive\r\nDate: %s\r\nContent-Type: "
                     "%s\r\nContent-Length: %d\r\n\n%s",
                     date, "text/html", content_length, response);
        len = strlen(http_response);
        bytes_sent = send(newfd, http_response, len, 0);
        shutdown(newfd, SHUT_WR);
        free(date);
        free(http_response);

      } else {
        response = content(path);
        char *statuscode = "200 OK";
        if (strcmp(response, "404 Not Found") == 0)
          statuscode = "404 Not Found";
        char *http_response = (char *)malloc(RESSIZE);
        char *date = get_date_for_server();
        int content_length = strlen(response);
        int len, bytes_sent;
        int n =
            snprintf(http_response, RESSIZE,
                     "HTTP/1.1 %s\r\nAcess-Control-Allow-Origin: *"
                     "*\r\nConnection: Keep-Alive\r\nDate: %s\r\nContent-Type: "
                     "%s\r\nContent-Length: %d\r\n\n%s",
                     statuscode, date, "text/html", content_length, response);
        len = strlen(http_response);
        bytes_sent = send(newfd, http_response, len, 0);
        shutdown(newfd, SHUT_WR);

        free(date);
        free(http_response);
      }

    } else if (strcmp(ext, ".css") == 0) {
      response = content(path);
      char *statuscode = "200 OK";
      if (strcmp(response, "404 Not Found") == 0)
        statuscode = "404 Not Found";
      char *http_response = (char *)malloc(RESSIZE);
      char *date = get_date_for_server();
      int content_length = strlen(response);
      int len, bytes_sent;
      int n =
          snprintf(http_response, RESSIZE,
                   "HTTP/1.1 %s\r\nAcess-Control-Allow-Origin: *"
                   "*\r\nConnection: Keep-Alive\r\nDate: %s\r\nContent-Type: "
                   "%s\r\nContent-Length: %d\r\n\n%s",
                   statuscode, date, "text/css", content_length, response);
      len = strlen(http_response);
      bytes_sent = send(newfd, http_response, len, 0);
      shutdown(newfd, SHUT_WR);

      free(date);
      free(http_response);
    }

    else if (strcmp(ext, ".jpg") == 0 || strcmp(ext, ".jpeg") == 0 ||
             strcmp(ext, ".png") == 0) {
      char http_header[256];
      char *date = get_date_for_server();
      char *type = return_content_type(ext);
      struct file_data *fdata = NULL;
      fdata = read_file(path);
      if (fdata == NULL) {
        fprintf(stderr, "Error opening binary file");
        char *temp404 = "404 Not Found";
        int templen = strlen(temp404);
        char tempresponse[256];
        int temp_n =
            snprintf(tempresponse, 256,
                     "HTTP/1.1 404 Not Found\r\nAcess-Control-Allow-Origin: *"
                     "*\r\nConnection: Keep-Alive\r\nDate: %s\r\nContent-Type: "
                     "%s\r\nContent-Length: %d\r\n\n%s",
                     date, "text/html", templen, temp404);
        int temp_bytes_sent =
            send(newfd, tempresponse, strlen(tempresponse), 0);
        temp404 = NULL;
      }

      else {
        uint8_t buff[fdata->length];
        snprintf(http_header, 256,
                 "HTTP/1.1 200 OK\r\nContent-Type: "
                 "%s\r\nContent-Length: %llu\r\n\r\n",type,
                 fdata->length);
        send(newfd, http_header, strlen(http_header), 0);
        send(newfd, fdata->data, fdata->length, 0);
        shutdown(newfd, SHUT_WR);

        fdata = NULL;
      }

    } else {

      shutdown(newfd, SHUT_WR);
    }
  }

  close(sockfd);
  return 0;
}
