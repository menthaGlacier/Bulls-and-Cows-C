#ifndef ERRHANDLER_H
#define ERRHANDLER_H

#include "pch.h"
#include "constants.h"

typedef enum ErrorCode
{
	ERR_NONE = 0,
	ERR_FILE = 1,
	ERR_ALLOC = 2,
	ERR_DATA = 3,
	ERR_FILTER = 4
} ErrorCode;

void errorHandler(ErrorCode errCode, ...);

#endif /* ERRHANDLER_H */ 
