#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFSIZE 2048

typedef struct file_data {
  uint8_t *data;
  size_t length;
} file_data;

struct file_data *read_file(const char *path) {

  FILE *handler = NULL;
  struct file_data *fdata = NULL;
  size_t read_length = 0;
  uint8_t buffer[BUFFSIZE] = {0x00};

  fdata = malloc(sizeof(struct file_data));
  if (fdata == NULL)
    return NULL;

  bzero(fdata, sizeof(struct file_data));

  fdata->data = malloc(1);
  if (fdata->data == NULL) {
    free(fdata);
    return NULL;
  }

  handler = fopen(path, "rb");
  if (handler == NULL) {
    free(fdata->data);
    free(fdata);
    return NULL;
  }

  while (!feof(handler)) {
    read_length = fread(buffer, 1, BUFFSIZE, handler);
    fdata->data = realloc(fdata->data, fdata->length + read_length);
    if (fdata->data == NULL) {
      fclose(handler);
      free(fdata);
      return NULL;
    }
    memcpy(fdata->data + fdata->length, buffer, read_length);
    fdata->length += read_length;
  }

  fclose(handler);

  return fdata;
}

// open the requested file and return the file pointer
FILE *requestfile(char *filename) {
  FILE *fp;
  fp = fopen(filename, "r");
  if (fp != NULL) {
    return fp;
  } else {
    perror("Error opening file\n");
  }
}

// count the byte size of file
int count_file_bytes(FILE *fp) {
  int c, count = 0;
  if (fp != NULL) {
    while ((c = fgetc(fp)) != EOF)
      count++;
  }
  fclose(fp);
  return count;
}

// read the file content to buffer and return
char *content(char *filename) {
  FILE *fp = requestfile(filename);
  if (fp == NULL) {
    char *content = "404 Not Found";

  } else {
    int bytecount = count_file_bytes(fp);
    char *content = (char *)malloc(bytecount + 1);

    FILE *file = requestfile(filename);
    size_t i;

    for (i = 0; i < (bytecount + 1); ++i) {
      int c = fgetc(file);
      if (c == EOF) {
        break;
      }

      content[i] = c;
    }

    content[i] = '\0';
    fclose(file);
    return content;
  }
}

// get file extension before last '.'
char *get_file_ext(char *filename, int c) {
  char *type = strrchr(filename, c);
  return type;
}

// read the file in binary format
// char *read_binary_file(char *filename)
//{
//	FILE *fp = fopen(filename,"rb");
//	if(fp == NULL)
//		fprintf(stderr,"\t Error Opening file: %s\n",filename);
//	long image_size;
//	int c;
//	int count = 0;
//	fseek(fp,0,SEEK_END);
//	image_size = ftell(fp);
//	rewind(fp);
//	char *buffer = (char *)malloc(image_size);
//
//	fread(buffer,1,image_size,fp);
//
//	fclose(fp);
//	return buffer;
//}
