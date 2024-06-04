#ifndef ROUTES_H
#define ROUTES_H

char *get_file_path(const char *request);
char *requestpath(int sockfd);
char *removenslash(const char *path);

#endif
