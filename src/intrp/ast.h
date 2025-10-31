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
enum ToriNodeType {
	TNT_PROGRAM,

	TNT_FUNC_DECL,
	TNT_VAR_DECL,
	TNT_VAR_DECL_ASSN,
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
};

/// The potential types of a ToriNodeValue. This is used by
/// the interpreter when verifying if a ToriNode has all of the
/// data it should.
enum ToriValueType {
	/// The value in ToriNodeValue->value is a string. This is
	/// used for things like identifiers, where they aren't
	/// literally a string in the Tori source, but are cannot
	/// be put into any of the other types.
	TVT_STRING,

	/// The value in ToriNodeValue->value is an integer
	TVT_INT,

	/// The value in ToriNodeValue->value is a float
	TVT_FLOAT,

	/// The value in ToriNodeValue->value is a boolean
	TVT_BOOL,

	/// The value in ToriNodeValue->value is a character
	TVT_CHAR,

	/// The value in ToriNodeValue->value is null. Having a value
	/// of this type will always result in an error.
	TVT_NULL
};

/// Struct representing a value of an AST node - the "content"
/// of the node. This struct exists because an AST node may
/// have different numbers of values to be included, and I
/// don't want to make a struct for each type of node.
///
/// For example, both a binary expression (2 + 2) needs three
/// values: left, right, and operation (addition, subtraction,
/// etc.). However, a function declaration (func add : int;)
/// requires two: identifier (add), and type (int).
///
/// On top of that, node values may end up being different
/// C types. For example, an identifier would be a char *
/// in C, but a Tori int would be a C int. ToriNodeValue makes
/// it so that there doesn't need to be different
/// definitions for a value in every C type.
struct ToriNodeValue {
	/// The name of the value, to identify it from other value
	/// nodes (i.e. "left", "identifier", etc.).
	char *name;

	/// The actual value that the node contains.
	char *value;

	/// The type of the ToriNodeValue - what the contents of
	/// ToriNodeValue->value "really are".
	enum ToriValueType type;
};

/// Struct representing a single AST node.
typedef struct ToriNode ToriNode;

// we need a way to represent data - we could just use strings,
// but some node data needs to be a ToriNode (**children), we
// could just have a custom string that "points" eval.c to
// whatever child that value is.
// also some node types have 2 values. or 4. the best solution
// here is to have an array of strings.
// or we create a ToriValue struct with an optional child of
// ToriValue for the values inside of nodes.
struct ToriNode {
	/// The type of AST node the ToriNode is
	enum ToriNodeType type;

	/// An array of ToriNodeValue objects that contains all
	/// of the node's values
	struct ToriNodeValue **values;

	/// The amount of values the ToriNode have.
	int value_count;

	/// An array of child nodes (if the node has children).
	/// Length is equivalent to ->child_count;
	struct ToriNode **children;

	/// The amount of child nodes the ToriNode has. Can be 0.
	int child_count;
};

#endif
