// Basic dynamic string library

#include <stdio.h>

#ifndef TSTRING_H
#define TSTRING_H

// The actual string object.
typedef struct {
	// The string's data.
	char *buff;

	// The length of the string (does not include null terminated character).
	size_t len;
} TString;

// Creates a new TString object and return it.
TString string_new(char *str, size_t len);

// Completely destroys the string, freeing any memory it had allocated.
void string_free(TString str);

// Returns the length of the string.
size_t string_len(TString str);

// Creates a new TString object with `src` placed at the end of `dest`
TString string_cat(TString first, TString second);

// Returns a duplicate TString object of `str`
TString string_dup(TString src);

// Returns a substring of `src`. `start` is inclusive, `end` is not.
TString string_sub(TString src, int start, int end);

// Prints a TString object.
void string_print(TString str);

// Prints a TString object, followed by a newline character.
void string_println(TString str);

#endif
