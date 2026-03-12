// Tori lexer
// See `src/tlex.h` for documentation

#include <stdio.h>

#include "tarray.h"
#include "terror.h"
#include "tstring.h"
#include "tpath.h"

TArray tlex_lex(TString p) {
	// convert p to a realpath and actual C string
	TString realpath = tpath_real(p);
	char *path = string_get(realpath);
	string_free(realpath);

	printf("path: %s\n", path);
	FILE *file = fopen(path, "rb");

	if(!file) {
		terror_throw(TERRORTYPE_FILE_OPEN_FAIL);
	}

	// get the file size
	fseek(file, 0, SEEK_END);
	size_t file_len = ftell(file);
	rewind(file);

	char *buff = malloc(file_len + 1);
	
	fread(buff, 1, file_len, file);
	buff[file_len + 1] = '\0';

	printf("file contents:\n%s\n", buff);

	free(path);
	free(buff);

	fclose(file);

	return tarray_new(1);
}