#ifndef FILEHANDLE
#define FILEHANDLE


FILE* requestfile(char *filename);
char *content(char *filename);
int count_file_bytes(FILE *fp);
char *get_file_ext(char *filename, int c);
char *read_binary_file(char *filename);
#endif
