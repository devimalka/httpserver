#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// open the requested file and return the file pointer
FILE* requestfile(char *filename){
	FILE *fp;
	fp = fopen(filename,"r");
	if(fp != NULL){
		return fp;
	}
	else{
		perror("Error opening file\n");
	}
}

// count the byte size of file
int count_file_bytes(FILE *fp)
{
	int c,count = 0;
	if(fp != NULL){
		while((c = fgetc(fp)) != EOF)
			count++;
	}
	fclose(fp);
	return count;
}

// read the file content to buffer and return
char* content(char *filename)
{
	FILE *fp = requestfile(filename);
	int bytecount = count_file_bytes(fp);
	char *content = (char *) malloc(bytecount+1);

	FILE *file = requestfile(filename);
	size_t i;

	for(i=0;i<(bytecount+1);++i)
	{
		int c = fgetc(file);
		if( c == EOF)
		{
			break;
		}

		content[i]= c;
	}

	content[i] = '\0';
	fclose(file);
	return content;



}

// get file extension before last '.'
char *get_file_ext(char *filename, int c)
{
	char *type = strrchr(filename,c);
	return type;
}


// read the file in binary format
char *read_binary_file(char *filename)
{
	FILE *fp = fopen(filename,"rb");
	if(fp == NULL)
		fprintf(stderr,"\t Error Opening file: %s\n",filename);
	long image_size;
	int c;
	int count = 0;
	fseek(fp,0,SEEK_END);
	image_size = ftell(fp);
	rewind(fp);
	char *buffer = (char *)malloc(image_size);

	fread(buffer,1,image_size,fp);

	fclose(fp);
	return buffer;
}
