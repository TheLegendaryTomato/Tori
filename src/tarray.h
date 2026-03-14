// Basic dynamic sized array library

#include <stdlib.h>
#include <stdbool.h>

#ifndef TARRAY_H
#define TARRAY_H

// use void pointers for the actual array?
typedef struct {
	// The actual data contained in the array.
	void **data;

	// The number of objects currently in the array.
	size_t len;
} TArray;

// Creates a new `TArray` object and returns it.
TArray tarray_new(size_t start_len);

// Completely destroys the array, freeing any memory it had allocated.
void tarray_free(TArray arr);

// Adds a new value `val` to the end of array `arr`.
void tarray_append(TArray *arr, void *val);

// Inserts a value `val` at position `index` in array `arr`.
void tarray_insert(TArray *arr, void *val, size_t index);

// Removes a value at position `index` in array `arr`.
void tarray_remove(TArray *arr, size_t index);

// Finds a value `val` and returns the index of it. Returns -1 if `val`
// is not found.
int tarray_find(TArray arr, void *val);

// Returns the size of the TArray.
size_t tarray_len(TArray arr);

// Returns a value located at position `index` in `arr`.
void *tarray_get(TArray arr, size_t index);

#endif