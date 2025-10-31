/*
 * Interpreter error types and utility functions
 * 2025 Aethari
 */

#ifndef ERROR_H
#define ERROR_H

/// An enum containing each of the errors the interpreter can
/// throw.
typedef enum {
	/// Program was executed with no errors
	ERR_SUCCESS,

	/// Generic failure code
	ERR_FAILURE,

	/// Thrown when a type mismatch between the evaluation function
	/// and its `ToriNode` parameter is found.
	ERR_INVALID_NODE_TYPE,

	/// Thrown when a node other than the root node has type
	/// `TNT_PROGRAM`
	ERR_DUPLICATE_PROGRAM,

	/// Thrown when a node contains a value it shouldn't
	ERR_INVALID_VALUE,

	/// Thrown when a node is missing a value it should have
	ERR_MISSING_VALUE
} ErrorType;

/// Creates an error message from an `ErrorType` value and
/// returns it.
///
/// Parameters:
/// - err: An ErrorType value to convert to an error message
///
/// Returns:
/// A pointer to a dynamically allocated string containing the
/// error message. This must be freed by the caller.
char *eval_err_to_string(ErrorType err);

#endif
