// Tori parser
// see `src/tparse.h` for documentation

#include "tarray.h"

#include "tlex.h"

TArray tparse_parse(TArray tokens) {
	// the array that will become the AST
	TArray out = tarray_new(1);

	// DEBUG: print the tokens
	for(size_t i = 0; i < tarray_len(tokens); i++) {
		TToken *token = tarray_get(tokens, i);

		string_println(token->value);
		string_free(token->value);
		free(token);
	}

	return out;
}