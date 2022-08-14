#include "../include/errorHandler.h"

void errorHandler(ErrorCode errCode, ...)
{
	puts("");

	va_list argptr;
	va_start(argptr, errCode);

	switch (errCode)
	{
	// Error code ERR_NONE indicates no error
	case ERR_NONE:
		break;

	// Error code ERR_FILE indicates an error with opening a file
	// An additional argument specifies the file name
	case ERR_FILE:
		fprintf(stderr, "An error occured while trying to open a %s file\n",
			va_arg(argptr, char*));
		break;

	// Error code ERR_ALLOC indicates an error with memory allocation
	case ERR_ALLOC:
		fprintf(stderr, "An error occured while trying to allocate memory\n");
		break;

	// Error code ERR_DATA indicates an error with the amount of loaded valid words
	// Two additional arguments specify the minimum and maximum amount of words 
	case ERR_DATA:
		fprintf(stderr, "An invalid amount of valid words were loaded. "
			"Their amount must be in [%d, %d] range\n",
			va_arg(argptr, int), va_arg(argptr, int));
		break;

	// Error code ERR_FILTER indicates an error with the word passed to the filter
	case ERR_FILTER:
		fprintf(stderr, "A word passed to the filter was an empty pointer\n");
		break;

	// In the case of an unknown error code
	default:
		fprintf(stderr, "Unknown error code #%d\n", errCode);
		break;
	}

	va_end(argptr);
	exit(errCode);
}