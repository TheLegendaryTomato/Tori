// Basic dynamic string library

#include <stdio.h>

#ifndef STRING_H
#define STRING_H

// The actual string object.
typedef struct {
	char *buff;
	size_t len;
} String;

// Create a new `String` object and return it.
String string_new(char *str, size_t len);

// Completely destroys the string, freeing any memory it had allocated.
void string_free(String str);

// Returns the length of the string.
size_t string_len(String str);

// Creates a new String object with `src` placed at the end of `dest`
String string_cat(String first, String second);

// Returns a duplicate String object of `str`
String string_dup(String src);

// Returns a substring of `src`. `start` is inclusive, `end` is not.
String string_sub(String src, int start, int end);

// Prints a String object.
void string_print(String str);

// Prints a String object, followed by a newline character.
void string_println(String str);

#endif
