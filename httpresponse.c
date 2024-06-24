#include <time.h>
#include <stdlib.h>

#include <string.h>
#include <stdio.h>

#define MAXSIZE 30

// get the date for http response
char* get_date_for_server()
{
	time_t result = time(NULL);
	char *date = (char *)malloc(MAXSIZE*sizeof(char));
	if(result != (time_t)(-1)){

		size_t t = strftime(date,MAXSIZE,"%a, %d %b %Y %T GMT",localtime(&result));
	}
	return date;

}

// return the MIME types for file type
char *return_content_type(char *filetype){
		if(strcmp(filetype,".jpeg") == 0 || strcmp(filetype,".jpg") == 0){
				return "image/jpeg";
		}

		else if(strcmp(filetype,".css") == 0){
				return "text/css";
		}

		else if(strcmp(filetype,".js") == 0){
				return "text/javascript";
		}

		else if(strcmp(filetype,".png") == 0){
				return "image/png";
		}

		else if(strcmp(filetype,".html") == 0){
				return "text/html";
		}
		else {
				return "text/html";
		}

}
