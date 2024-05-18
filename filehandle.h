#ifndef FILEHANDLE
#define FILEHANDLE


FILE* requestfile(char *filename);
char *content(char *filename);
int count_file_bytes(FILE *fp);
#endif
