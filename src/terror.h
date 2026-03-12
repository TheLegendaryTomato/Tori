// Handles various errors throughout program execution

#ifndef TERROR_H
#define TERROR_H

// What kind of error is being thrown.
typedef enum {
	// Throw when a call to `malloc` fails.
	TERRORTYPE_ALLOC_FAIL
} TErrorType;

// Throw an error. Depending on the value of `type`, the program might be
// terminated.
void terror_throw(TErrorType type);

#endif