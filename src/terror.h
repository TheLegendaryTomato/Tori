// Handles various errors throughout program execution

#ifndef TERROR_H
#define TERROR_H

// What kind of error is being thrown.
typedef enum {
	// Throw when a call to `fopen` fails.
	TERRORTYPE_FILE_OPEN_FAIL,

	// Throw when a call to `malloc` fails.
	TERRORTYPE_ALLOC_FAIL,

	// Throw when an index of some kind is out of bounds.
	TERRORTYPE_OUT_OF_BOUNDS
} TErrorType;

// Throw an error. Depending on the value of `type`, the program might be
// terminated.
void terror_throw(TErrorType type);

#endif