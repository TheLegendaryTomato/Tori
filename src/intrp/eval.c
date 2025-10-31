/*
 * Functions for evaluating AST nodes
 * See eval.h for documentation
 * 2025 Aethari
 */

#include <string.h>

#include "ast.h"
#include "error.h"

#define STR_MAX_LEN 4096

/// Evaluates a `TNT_FUNC_DECL` node.
///
/// Parameters:
/// - node: a node of type `TNT_FUNC_DECL` that will be evaluated and ran
///
/// Returns:
/// An `ErrorType` value representing whether or not the node
/// executed successfully. Returns `ERR_SUCCESS` if the
/// evaluation was successful, and a non-zero `ErrorType` value
/// if it failed.
ErrorType eval_func_decl(ToriNode *node) {
	if(node->type != TNT_FUNC_DECL) {
		return ERR_INVALID_NODE_TYPE;
	}

	if(node->value_count < 2) {
		return ERR_MISSING_VALUE;
	} else if(node->value_count > 2) {
		return ERR_INVALID_VALUE;
	}

	char identifier[STR_MAX_LEN];
	char type[STR_MAX_LEN];

	for(int i = 0; i < 1; i++) {
		if(strcmp(node->values[i]->name, "identifier") == 0) {
			strcpy(identifier, node->values[i]->value);
		} else if(strcmp(node->values[i]->name, "type") == 0) {
			strcpy(type, node->values[i]->value);
		} else {
			return ERR_INVALID_VALUE;
		}
	}

	// add the function to the stack

	return ERR_SUCCESS;
}

/// Evaluates a `TNT_VAR_DECL` node.
///
/// Parameters:
/// - node: a node of type `TNT_VAR_DECL` that will be evaluated and ran
///
/// Returns:
/// An `ErrorType` value representing whether or not the node
/// executed successfully. Returns `ERR_SUCCESS` if the
/// evaluation was successful, and a non-zero `ErrorType` value
/// if it failed.
ErrorType eval_var_decl(ToriNode *node) {
	if(node->type != TNT_VAR_DECL) {
		return ERR_INVALID_NODE_TYPE;
	}

	if(node->value_count < 2) {
		return ERR_MISSING_VALUE;
	} else if(node->value_count > 2) {
		return ERR_INVALID_VALUE;
	}

	char identifier[STR_MAX_LEN];
	char type[STR_MAX_LEN];

	for(int i = 0; i < 1; i++) {
		if(strcmp(node->values[i]->name, "identifier") == 0) {
			strcpy(identifier, node->values[i]->value);
		} else if(strcmp(node->values[i]->name, "type") == 0) {
			strcpy(type, node->values[i]->value);
		} else {
			return ERR_INVALID_VALUE;
		}
	}

	// add the variable to the stack

	return ERR_SUCCESS;
}

/// Same as eval_var_decl, but the variable is followed by an
/// assignment. Left this here as a reminder to add var_decl_assn
/// to the lexer/parser.
ErrorType eval_var_decl_assn(ToriNode *node) {
	return ERR_SUCCESS;
}

// Evaluates a `TNT_PROGRAM` (root) node.
//
// True to the nature of a recursive-descent parser, This
// function is recursive. A single call of it will interpret and
// execute the entire AST. It relies on evaluation functions for
// each `ToriNodeType`, and will return the `EvalError` value if
// any child evaluation returns non-zero.
//
// Calling this function more than once will cause the program
// to be run multiple times.
ErrorType eval(ToriNode *node) {
	if(node->type != TNT_PROGRAM) {
		return ERR_INVALID_NODE_TYPE;
	}

	if(node->child_count > 0) {
		for(int i = 0; i < node->child_count; i++) {
			ToriNode *child = node->children[i];

			switch(child->type) {
				case TNT_PROGRAM:
					return ERR_DUPLICATE_PROGRAM;
				case TNT_FUNC_DECL:
					return eval_func_decl(child);
				case TNT_VAR_DECL:
				default:
					return ERR_SUCCESS;
			}
		}
	}

	return 0;
}
