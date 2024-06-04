#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFSIZE 2048

char *get_file_path(const char *request) {
    char *path = NULL;
    char *start = strstr(request, "GET ");
    if (start != NULL) {
	start += 4; // Move past "GET "
	char *end = strstr(start, " ");
	if (end != NULL) {
	    int path_length = end - start;
	    path = (char *)malloc(path_length + 1);
	    strncpy(path, start, path_length);
	    path[path_length] = '\0';
	}
    }
    return path;
};

char *removenslash(char *request) {
//    char *path = null; 
//    char *start = strstr(request,"/");
//    char *end = strstr(request," ");
//    if(end != null) {
//        int path_length = end - start;
//        strncpy(path,start,path_length);
//        path[path_length] = '\0';
//    }
//    return path;

      char *path = request + 1;
      return path;
}
        

char *requestpath(int sockfd) {
    char *buffer = (char *)malloc(BUFFSIZE);

    int bytes = read(sockfd, buffer, BUFFSIZE);
    return buffer;
};

