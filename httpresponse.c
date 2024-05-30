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

// generate http response 
char *generate_http_response()
{
	char *Header =
	"HTTP/1.1 200 OK\r\n"
	"Access-Control-Allow-Origin: *\r\n"
	"Connection: Keep-Alive\r\n"
	"Date: %s\r\n"
	"Content-Type: %s\r\n"
//	"Content-Length: %d\r\n"
	"\n"
	"%s";

	return Header;
}

// return the file mime type 
char *get_type(char *filepath)
{

    char *type = NULL;
    if(strcmp(filepath, ".jpg") == 0){
        type = "image/jpg";
    }
    else {
        type = "text/html";
    }
    return type;
}
