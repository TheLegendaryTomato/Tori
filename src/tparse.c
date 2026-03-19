// Tori parser
// see `src/tparse.h` for documentation

#include "tarray.h"
#include "tast.h"

#include "tlex.h"
#include "tstring.h"

TArray tparse_parse(TArray tokens) {
	// the array that will become the AST
	TArray out = tarray_new(1);

	// process the tokens
	for(size_t i = 0; i < tarray_len(tokens); i++) {
		TToken *token = tarray_get(tokens, i);

		// evaluate the current token based on its type
		switch(token->type) {
			case TTOKENTYPE_KEYWORD:
				break;
			case TTOKENTYPE_WHITESPACE:
				break;
			case TTOKENTYPE_OPERATOR:
				break;
			case TTOKENTYPE_DELIMITER:
				break;
			case TTOKENTYPE_LITERAL:
				break;
			case TTOKENTYPE_IDENTIFIER:
				// the only statement in Tori that starts with an identifier is a function call
				break;
			// This case was already handled in the lexer, so it does not need any additional work here.
			case TTOKENTYPE_INVALID:
				break;
		}
		
		// DEBUG: print the tokens
		string_println(token->value);
		string_free(token->value);

		// IMPROVEMENT: keep this here, or free individual tokens separate from this function?
		free(token);
	}

	return out;
}