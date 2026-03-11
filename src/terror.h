// Handles various errors throughout program execution

#ifndef TERROR_H
#define TERROR_H

// What kind of error is being thrown.
typedef enum {
	TERRORTYPE_ALLOC_FAIL
} TErrorType;

void terror_throw(TErrorType type);

#endif