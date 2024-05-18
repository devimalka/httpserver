#include <stdio.h>
#include <stdlib.h>

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
