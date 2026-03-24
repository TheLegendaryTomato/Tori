// Definitions for structs and enums required by the parser / AST

#include <stdbool.h>

#include "tstring.h"

#ifndef TAST_H
#define TAST_H

// Every type a Tori variable can possibly be.
typedef enum {
	TVARTYPE_INT,
	TVARTYPE_FLOAT,
	TVARTYPE_BOOL,
	TVARTYPE_STRING
} TVarType;

// Each kind of `end` statement
typedef enum {
	TASTENDNODETYPE_IF,
	TASTENDNODETYPE_FUNC,
	TASTENDNODETYPE_LOOP
} TAstEndNodeType;

// Every type of AST node that the parser can generate.
typedef enum {
	// A variable declaration that gives the variable's type, but not the value.
	TASTNODETYPE_VAR_DECL,

	// Basically a `TASTNODETYPE_VAR_DECL`, but instead of giving the type, the user gives the value, and the parser infers the type.
	TASTNODETYPE_VAR_INIT,

	// The first line of an "if" statement (the actual "if" part).
	TASTNODETYPE_IF_INIT,
	// The end of an "if" statement, signified by the `endif` keyword.
	TASTNODETYPE_IF_END,

	// Just an `int` literal.
	TASTNODETYPE_INT_LITERAL,
	// Just a `float` literal.
	TASTNODETYPE_FLOAT_LITERAL,
	// Just a `boolean` literal.
	TASTNODETYPE_BOOL_LITERAL,
	// Just a `string` literal.
	TASTNODETYPE_STRING_LITERAL
} TAstNodeType;

// An enum describing what kind of comparison an expression is making.
typedef enum {
	// The expression is checking if two values are equal.
	TASTCOMPARISONTYPE_EQUATE,

	// The expression is checking if the left value is less than the right one.
	TASTCOMPARISONTYPE_LESS,
	// The expression is checking if the left value is greater than the right one.
	TASTCOMPARISONTYPE_GREATER,

	// The expression is checking if the left value is less than or equal to the right one.
	TASTCOMPARISONTYPE_LESS_EQUAL,
	// The expression is checking if the left value is greater than or equal to the right one.
	TASTCOMPARISONTYPE_GREATER_EQUAL
} TAstComparisonType;

// A struct representing a binary expression (i.e. `x == 10`).
typedef struct {
	// What kind of node this is.
	TAstNodeType node_type;

	TAstComparisonType type;
} TAstBinaryExpr;

// We are going to define a different struct for each `TAstNodeType` value.
// Things like `end` or literal node types can be combined into one struct, with an auxillary member for the type (e.g. literals have types for int, float, bool, and string)

// An AST node used for casting when processing the ast.
// As C cannot tell what type a void pointer is, we need to use this to differentiate between nodes in the array.
typedef struct {
	// What kind of node this is.
	TAstNodeType node_type;
} TAstBaseNode;

// An AST node representing a variable definition.
// This can either be a variable declaration, where the input stream provides the variable's type, or a variable initilization, where a value was given, but no type.
typedef struct {
	// What kind of node this is.
	TAstNodeType node_type;

	// Whether or not the input stream provided a value for the variable. If `true`, the variable was initialized instead of declared, and the parser needs to infer the type of the variable.
	bool initialized;

	// The type of the variable.
	TVarType var_type;

	// The value of the variable. This union defines a C value with a type corresponding to the type of the Tori variable. If the `null` value is `true`, it means that the variable has no value.
	union {
		int i;
		float f;
		bool b;
		TString s;

		bool null;
	} value;

	// The line the node was found on.
	int line;
	// The column the node was found on.
	int col;
} TAstVarDefNode;

// An AST node representing an `end` statement.
typedef struct {
	// What kind of node this is.
	TAstNodeType node_type;

	// What kind of `end` node the node is.
	TAstEndNodeType type;

	// The line the node was found on.
	int line;
	// The column the node was found on.
	int col;
} TAstEndNode;

// An AST node representing an `if` statement.
typedef struct {
	// What kind of node this is.
	TAstNodeType node_type;

	// The line the node was found on.
	int line;
	// The column the node was found on.
	int col;
} TAstIfNode;

// An AST node representing an integer, float, bool, or string literal.
typedef struct {
	// What kind of node this is.
	TAstNodeType node_type;

	// The value of the literal. This union defines a C value with a type corresponding to the Tori type of the literal.
	union {
		int i;
		float f;
		bool b;
		TString s;
	} value;

	// The line the node was found on.
	int line;
	// The column the node was found on.
	int col;
} TAstLiteralNode;

#endif