// Basic dynamic string library
// For documentation, see `src/tstring.h`

#include <string.h>
#include <stdlib.h>

#include "tstring.h"
#include "terror.h"

TString string_new(char *str, size_t len) {
	TString out;

	out.len = len;

	out.buff = malloc(len+1);

	// check if allocation failed
	if(!out.buff) {
		terror_throw(TERRORTYPE_ALLOC_FAIL);
	}

	// check if `str` actually has `len` bytes (segfaults if not)
	if(strlen(str) < len) {
		printf("Error: Unable to create string: invalid length\n");
		exit(1);
	}

	memcpy(out.buff, str, len);
	out.buff[len] = '\0';

	return out;
}

void string_free(TString str) {
	free(str.buff);
}

TString string_dup(TString str) {
	return string_new(str.buff, str.len);
}

size_t string_len(TString str) {
	return str.len;
}

TString string_cat(TString first, TString second) {
	size_t len = first.len + second.len;

	char *buff = malloc(len + 1);

	if(!buff) {
		terror_throw(TERRORTYPE_ALLOC_FAIL);
	}

	strcat(buff, first.buff);
	strcat(buff, second.buff);

	TString out = string_new(buff, len);

	free(buff);
	return out;
}

TString string_append(TString str, char append) {
	size_t len = str.len + 1;

	char *buff = malloc(len + 1);

	if(!buff) {
		terror_throw(TERRORTYPE_ALLOC_FAIL);
	}

	memcpy(buff, str.buff, str.len);
	buff[len-1] = append;
	buff[len] = '\0';

	TString out = string_new(buff, len);

	free(buff);
	return out;
}

TString string_sub(TString src, int start, int end) {
	// the ending length of the string (not null-terminated)
	int len = end - start;

	char *buff = malloc(len);

	if(!buff) {
		terror_throw(TERRORTYPE_ALLOC_FAIL);
	}

	strncpy(buff, src.buff + start, len);

	TString out = string_new(buff, len);

	free(buff);
	return out;
}

char *string_get(TString str) {
	char *out = malloc(str.len + 1);

	if(!out) {
		terror_throw(TERRORTYPE_ALLOC_FAIL);
	}

	strcpy(out, str.buff);

	return out;
}

void string_print(TString str) {
	printf("%s", str.buff);
}

void string_println(TString str) {
	printf("%s\n", str.buff);
}