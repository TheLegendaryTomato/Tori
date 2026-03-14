// Tori program entry point

#include <stddef.h>

#include "tstring.h"
#include "tarray.h"

#include "tlex.h"

int main(int argc, char *argv[]) {
	TString path = string_new("tests/test.tori", 15);
	TArray tokens = tlex_lex(path);

	for(size_t i = 0; i < tarray_len(tokens); i++) {
		TToken *token = tarray_get(tokens, i);

		string_println(token->value);
		string_free(token->value);
		free(token);
	}

	string_free(path);
	tarray_free(tokens);

	return 0;
}