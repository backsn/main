#ifndef __UTIL__
#define __UTIL__

//#include "Standard.h"
//#include <memory.h>
//#include <string.h>

#define INVALID -1
#define MAX_FILE_IO_BUF 1024

#define CREATE(result, type, number)		do {				\
	if(!((result) = new type [(number)]))						\
			{ abort(); } } while(0)

#define DISPOSE(point) 										\
	do {													\
				if((point)) delete[] (point);				\
				point = NULL;								\
			} while(0)

#define FREEMEM(point) 										\
	do {													\
				if((point)) free(point);					\
				point = NULL;								\
			} while(0)


#define PARSER(str)	return str

#endif