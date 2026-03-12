// Tori lexer
// See `src/tlex.h` for documentation

#include <stdio.h>

#include "tarray.h"
#include "tstring.h"

TArray tlex_lex(TString p) {
	// open the file at path and read it
	// we may need to do stuff with relative paths and working directories
	// to get this to work.

	char *path = string_get(p);

	printf("path: %s\n", path);
	FILE *file = fopen(path, "r");

	free(path);

	return tarray_new(1);
}