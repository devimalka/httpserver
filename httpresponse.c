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


