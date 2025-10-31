/*
 * Functions for evaluating AST nodes
 * 2025 Aethari
 */

#include "ast.h"
#include "error.h"

#ifndef EVAL_H
#define EVAL_H

/// Evaluate a `TNT_PROGRAM` node.
///
/// Parameters:
/// - node: a node of type `TNT_PROGRAM` that will be evaluated and ran
///
/// Returns:
/// An `ErrorType` value representing whether or not the program
/// executed successfully. Returns `ERR_SUCCESS` if it was
/// successful, and a `ErrorType` value if it failed.
ErrorType eval(ToriNode *node);

#endif
