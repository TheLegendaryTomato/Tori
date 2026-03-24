// Tori parser
// see `src/tparse.h` for documentation

#include <string.h>

#include "tarray.h"
#include "tast.h"

#include "terror.h"
#include "tlex.h"
#include "tstring.h"

TArray tparse_parse(TArray tokens) {
	// the array that will become the AST
	TArray out = tarray_new(1);

	// process the tokens
	for(size_t i = 0; i < tarray_len(tokens); i++) {
		TToken *token = tarray_get(tokens, i);
		char *token_string = string_get(token->value);
		
		// evaluate the current token based on its type
		switch(token->type) {
			case TTOKENTYPE_KEYWORD:
				// variable definitions
				if(strcmp(token_string, "var") == 0) {
					// which operator (":" for declarations, "," for definitions) was used in the source code
					TToken *operator = tarray_get(tokens, i+2);
					char *operator_string = string_get(operator->value);

					TAstVarDefNode node;

					if(strcmp(operator_string, ":") == 0) {
						// declaration
						node.node_type = TASTNODETYPE_VAR_DECL;
						node.initialized = false;

						// find the variable's type
						TToken *type = tarray_get(tokens, i+3);
						char *type_string = string_get(type->value);

						if(strcmp(type_string, "int") == 0) {
							node.var_type = TVARTYPE_INT;
						} else if(strcmp(type_string, "float") == 0) {
							node.var_type = TVARTYPE_FLOAT;
						} else if(strcmp(type_string, "bool") == 0) {
							node.var_type = TVARTYPE_BOOL;
						} else if(strcmp(type_string, "string") == 0) {
							node.var_type = TVARTYPE_STRING;
						} else {
							printf("Error: Invalid type \"%s\" in variable declaration on line %d, column %d\n", type_string, type->line, type->col);
							exit(1);
						}

						// cleanup
						free(type_string);

						node.value.null = true;
					} else if(strcmp(operator_string, ",") == 0) {
						// initilization
						node.node_type = TASTNODETYPE_VAR_INIT;
						node.initialized = true;

						TToken *value = tarray_get(tokens, i+3);
						char *value_string = string_get(value->value);

						if(string_is_int(value->value)) {
							node.var_type = TVARTYPE_INT;
							node.value.i = atoi(value_string);
						} else if(string_is_float(value->value)) {
							node.var_type = TVARTYPE_FLOAT;
							node.value.f = atof(value_string);
						} else if(strcmp(value_string, "true") == 0) {
							node.var_type = TVARTYPE_BOOL;
							node.value.b = true;
						} else if(strcmp(value_string, "false") == 0) {
							node.var_type = TVARTYPE_BOOL;
							node.value.b = false;
						} else if(value_string[0] == '"') {
							node.var_type = TVARTYPE_STRING;
							node.value.s = string_dup(value->value);
						} else {
							terror_throw(TERRORTYPE_INVALID_LITERAL);
						}

						free(value_string);
					} else {
						printf("Error: Invalid operator in variable definition on line %d, column %d\n", operator->line, operator->col);
						exit(1);
					}

					node.line = token->line;
					node.col = token->col;

					// add the node to the array
					tarray_append(&out, &node);

					free(operator_string);
				}
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
		free(token_string);

		// IMPROVEMENT: keep this here, or free individual tokens separate from this function?
		free(token);
	}

	return out;
}