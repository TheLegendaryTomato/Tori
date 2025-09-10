/*
 * Definitions for node types to help with parsing the AST
 * 2025 Aethari
 *
 * This does NOT parse the AST itself, it just helps interp.h
 * parse it.
 */

#ifndef AST_H
#define AST_H

/// Every type of AST node that can exist in Tori.
///
/// We need:
/// - Program (for the root node)
///
/// - Function declaration
/// - Variable declaration
/// - For loop
/// - While loop
/// - Include statement
///
/// If statements will be the root if statement, have children
/// of "comparison" and "block" type, and optional children
/// containing "elif" or "else" type nodes, each with their own
/// "comparison" and / or "block" type node.
/// - If statement
/// 
/// - Elif statement
/// - Else statement
///
/// - Parameter statements
/// - Call statements
/// - Return statements
///
/// - Variable assignment (NOT declaration)
///
/// - Block (interior of function, if statement, etc.)
///
/// - Comparison expression
/// - Binary 
///
/// - Literals
typedef enum {
	TNT_PROGRAM,

	TNT_FUNC_DECL,
	TNT_VAR_DECL,
	TNT_FOR,
	TNT_WHILE,
	TNT_INCLUDE,

	TNT_IF,
	TNT_ELIF,
	TNT_ELSE,

	TNT_PARAM,
	TNT_CALL,
	TNT_RETURN,

	TNT_VAR_ASSN,

	TNT_BLOCK,

	TNT_COMPARE,
	TNT_BINARY_EXPR,

	TNT_INT_LITERAL,
	TNT_FLOAT_LITERAL,
	TNT_BOOL_LITERAL,
	TNT_CHAR_LITERAL
} ToriNodeType;

/// Struct representing a single AST node.
typedef struct ToriNode ToriNode;

struct ToriNode {
	ToriNodeType type;
	struct ToriNode **children;
	int child_count;
};

#endif
