/*
 * Functions for evaluating AST nodes
 * See eval.h for documentation
 * 2025 Aethari
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "error.h"

/// Evaluates a `TNT_FUNC_DECL` node
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
// If the AST is structured properly, a single call to this
// function should interpret the whole AST. Calling it more than
// once will cause the program to be run multiple times.
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
