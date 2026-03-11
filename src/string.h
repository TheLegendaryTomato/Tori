// Basic dynamic string library
// 2026 CJHB

#ifndef STRING_H
#define STRING_H

// The actual string object
typedef struct {
	char *buff;
	size_t len;
} String;

// Create a new `String` object and return it
String string_new(char str[], size_t len);

// Completely destroys the string, freeing any memory it had allocated
String string_free(String str);

// Returns the length of the string
size_t string_len(String str);

// Combines two strings, placing `src` at the end of `dest`
void string_cat(String dest, String src);

// Copies the contents of `src` to `dest`
void string_copy(String dest, String src);

// Places a substring of `src` into `dest`. `start` is inclusive, `end` is not.
void string_sub(String dest, String src, int start, int end);

#endif
