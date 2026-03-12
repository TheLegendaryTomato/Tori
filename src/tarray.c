// Basic dynamic sized array library
// See `src/tarray.h` for documentation

#include <stdlib.h>
#include <stdbool.h>

#include "tarray.h"
#include "terror.h"

TArray tarray_new(size_t start_len) {
	TArray out;

	out.len = start_len;

	// The `sizeof` call allocates each "block" of the array with the
	// size of what is essentially a void pointer, making the correct
	// size for each block.
	out.data = calloc(start_len, sizeof(void*));

	if(!out.data) {
		terror_throw(TERRORTYPE_ALLOC_FAIL);
	}

	return out;	
};

void tarray_free(TArray arr) {
	free(arr.data);
}

void tarray_append(TArray *arr, void *val) {
	size_t new_len = arr->len + 1;

	void *success = realloc(arr->data, sizeof(void*) * new_len);

	if(!success) {
		terror_throw(TERRORTYPE_ALLOC_FAIL);
	}

	arr->data = success;
	arr->data[arr->len] = val;
	arr->len = new_len;
}

void tarray_insert(TArray *arr, void *val, size_t index) {
	if(index > arr->len) {
		terror_throw(TERRORTYPE_OUT_OF_BOUNDS);
	}

	size_t new_len = arr->len + 1;

	void *success = realloc(arr->data, sizeof(void*) * new_len);

	if(!success) {
		terror_throw(TERRORTYPE_ALLOC_FAIL);
	}

	arr->data = success;

	for(int i = new_len-2; i >= (int)index; i--) {
		arr->data[i+1] = arr->data[i];
	}

	arr->data[index] = val;
	arr->len = new_len;
}

void tarray_remove(TArray *arr, size_t index) {
	if(index >= arr->len) {
		terror_throw(TERRORTYPE_OUT_OF_BOUNDS);
	}

	size_t new_len = arr->len - 1;

	for(size_t i = index; i < arr->len-1; i++) {
		arr->data[i] = arr->data[i+1];
	}

	void *success = realloc(arr->data, sizeof(void*) * new_len);

	if(!success && new_len > 0) {
		terror_throw(TERRORTYPE_ALLOC_FAIL);
	}

	arr->data = success;
	arr->len = new_len;
}

int tarray_find(TArray arr, void *val) {
	for(int i = 0; i < arr.len; i++) {
		if(arr.data[i] == val) {
			return i;
		}
	}

	return -1;
}

void *tarray_get(TArray arr, size_t index) {
	if(index >= arr.len) {
		terror_throw(TERRORTYPE_OUT_OF_BOUNDS);
	}

	return arr.data[index];
}