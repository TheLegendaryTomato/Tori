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

					// the identifier used for the name of the variable
					TToken *identifier = tarray_get(tokens, i+1);
					char *identifier_string = string_get(identifier->value);

					// check to make sure the identifier exists and is valid
					if(identifier->type == TTOKENTYPE_INVALID) {
						printf("Error: Invalid identifier \"%s\" in variable definition on line %d, column %d\n", identifier_string, identifier->line, identifier->col);
						exit(1);
					} else if(identifier->type != TTOKENTYPE_IDENTIFIER) {
						printf("Error: Missing identifier in variable definition on line %d, column %d\n", identifier->line, identifier->col);
						exit(1);
					}

					// check to make sure there is only one identifier
					if(operator->type == TTOKENTYPE_IDENTIFIER) {
						printf("Error: Extra identifier \"%s\" in variable definition on line %d, column %d\n", operator_string, operator->line, operator->col);
						exit(1);
					}
					
					TAstVarDefNode *node = malloc(sizeof(TAstVarDefNode));

					if(!node) {
						terror_throw(TERRORTYPE_ALLOC_FAIL);
					}
					
					if(strcmp(operator_string, ":") == 0) {
						// declaration
						node->node_type = TASTNODETYPE_VAR_DECL;
						node->initialized = false;
						
						node->identifier = string_dup(identifier->value);

						// the last token on the line, which should be a semicolon.
						// this is used to check for extra types.
						TToken *last = tarray_get(tokens, i+4);
						char *last_string = string_get(last->value);
						if(last->type != TTOKENTYPE_DELIMITER) {
							printf("Error: Extra type \"%s\" in variable declaration on line %d, column %d\n", last_string, last->line, last->col);
							exit(1);
						}
						
						// find the variable's type
						TToken *type = tarray_get(tokens, i+3);
						char *type_string = string_get(type->value);
						
						if(strcmp(type_string, "int") == 0) {
							node->var_type = TVARTYPE_INT;
						} else if(strcmp(type_string, "float") == 0) {
							node->var_type = TVARTYPE_FLOAT;
						} else if(strcmp(type_string, "bool") == 0) {
							node->var_type = TVARTYPE_BOOL;
						} else if(strcmp(type_string, "string") == 0) {
							node->var_type = TVARTYPE_STRING;
						} else if(
							type->type == TTOKENTYPE_IDENTIFIER ||
							type->type == TTOKENTYPE_KEYWORD
						) {
							printf("Error: Invalid type \"%s\" in variable declaration on line %d, column %d\n", type_string, type->line, type->col);
							exit(1);
						} else {
							printf("Error: Missing type in variable declaration on line %d, column %d\n", type->line, type->col);
							exit(1);
						}
						
						// the variable has no value
						node->null = true;
						
						// cleanup
						free(type_string);
						free(last_string);
					} else if(strcmp(operator_string, ",") == 0) {
						// initilization
						node->node_type = TASTNODETYPE_VAR_INIT;
						node->initialized = true;
						
						node->identifier = string_dup(identifier->value);

						// the last token on the line, which should be a semicolon.
						// this is used to check for extra types.
						TToken *last = tarray_get(tokens, i+4);
						char *last_string = string_get(last->value);
						if(last->type != TTOKENTYPE_DELIMITER) {
							printf("Error: Extra value \"%s\" in variable declaration on line %d, column %d\n", last_string, last->line, last->col);
							exit(1);
						}

						// find the variable's type
						TToken *value = tarray_get(tokens, i+3);
						char *value_string = string_get(value->value);

						if(string_is_int(value->value)) {
							node->var_type = TVARTYPE_INT;
							node->value.i = atoi(value_string);
						} else if(string_is_float(value->value)) {
							node->var_type = TVARTYPE_FLOAT;
							node->value.f = atof(value_string);
						} else if(strcmp(value_string, "true") == 0) {
							node->var_type = TVARTYPE_BOOL;
							node->value.b = true;
						} else if(strcmp(value_string, "false") == 0) {
							node->var_type = TVARTYPE_BOOL;
							node->value.b = false;
						} else if(value_string[0] == '"') {
							node->var_type = TVARTYPE_STRING;
							node->value.s = string_dup(value->value);
						// TODO: We should have a case for "invalid literals", but these theoretically do not exist. Until we implement variable lookups, they technically do, but are just identifiers. Therefore, the error will simply be wrong until we implement variable lookups.
						} else {
							printf("Error: Missing value in variable initialization on line %d, column %d\n", value->line, value->col);
							exit(1);
						}

						// the variable has a value, so it cannot be null
						node->null = false;

						// cleanup
						free(value_string);
						free(last_string);
					} else {
						printf("Error: Invalid operator in variable definition on line %d, column %d\n", operator->line, operator->col);
						exit(1);
					}

					node->line = token->line;
					node->col = token->col;

					// add the node to the array
					tarray_append(&out, node);

					free(operator_string);
					free(identifier_string);
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