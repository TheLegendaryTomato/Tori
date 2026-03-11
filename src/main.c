// Tori program entry point

#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "tstring.h"

int main(int argc, char *argv[]) {
	String tmp = string_new("Hello from tstring.h", 20);
	String dup = string_dup(tmp);
	String sub = string_sub(tmp, 1, 3);

	size_t len = string_len(tmp);
	size_t dup_len = string_len(dup);
	size_t sub_len = string_len(sub);

	string_println(tmp);
	printf("len: %zu\n\n", len);

	string_println(dup);
	printf("len: %zu\n\n", dup_len);

	string_println(sub);
	printf("len: %zu\n\n", sub_len);

	String cat1 = string_new("First ", 6);
	String cat2 = string_new("Second", 6);
	String cat = string_cat(cat1, cat2);

	string_println(cat);
	printf("len: %zu\n", string_len(cat));

	string_free(tmp);
	string_free(dup);
	string_free(sub);

	string_free(cat1);
	string_free(cat2);
	string_free(cat);

	return 0;
}
