// Basic dynamic string library
// For documentation, see `src/tstring.h`

#include <string.h>
#include <stdlib.h>

#include "tstring.h"
#include "terror.h"

String string_new(char *str, size_t len) {
	String out;

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

void string_free(String str) {
	free(str.buff);
}

String string_dup(String src) {
	return string_new(src.buff, src.len);
}

size_t string_len(String str) {
	return str.len;
}

String string_cat(String first, String second) {
	size_t len = first.len + second.len;

	char *buff = malloc(len + 1);

	strcat(buff, first.buff);
	strcat(buff, second.buff);

	String out = string_new(buff, len);

	free(buff);
	return out;
}

String string_sub(String src, int start, int end) {
	// the ending length of the string (not null-terminated)
	int len = end - start;

	char *buff = malloc(len);

	strncpy(buff, src.buff + start, len);

	String out = string_new(buff, len);

	free(buff);
	return out;
}

void string_print(String str) {
	printf("%s", str.buff);
}

void string_println(String str) {
	printf("%s\n", str.buff);
}