#ifndef FILEHANDLE
#define FILEHANDLE
#include<stdint.h>
#include<stdio.h>

typedef struct file_data {
	uint8_t *data;
	size_t length;
}file_data;

FILE* requestfile(char *filename);
char *content(char *filename);
int count_file_bytes(FILE *fp);
char *get_file_ext(char *filename, int c);
char *read_binary_file(char *filename);
struct file_data *read_file(const char *path);


#endif
